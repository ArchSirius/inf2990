#include "OpenGL_VBO.h"

///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.cpp
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Modele3D.h"
#include "AideGL.h"
#include "Utilitaire.h"

namespace opengl{
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::VBO(modele::Modele3D const* modele)
	///
	/// Assigne le modèle 3D.
	///
	/// @param[in] modele : le modele 3D à dessiner.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::VBO(modele::Modele3D const* modele)
		: modele_{ modele }
	{}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::~VBO()
	///
	/// Destructeur, relâche le VBO.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::~VBO()
	{
		liberer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::charger()
	///
	/// Charge les données du modèles 3D sur la mémoire de la carte graphique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::charger()
	{
		creerVBO(modele_->obtenirNoeudRacine());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::creerVBO(modele::Noeud const& noeud)
	///
	/// Création des VBO selon les données propres à chaque Mesh. L'ordre 
	/// des identifiants OpenGL se calque sur le modèle 3D, en prenant pour
	/// acquis que la hiérarchie interne des noeuds internes n'est pas 
	/// modifiée.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::creerVBO(modele::Noeud const& noeud)
	{
		for (auto const& mesh : noeud.obtenirMeshes())
		{
			enregistrerTampon(mesh.obtenirSommets());
			if (mesh.possedeNormales())
				enregistrerTampon(mesh.obtenirNormales());
			if (mesh.possedeTexCoords())
				enregistrerTampon(mesh.obtenirTexCoords());
			if (mesh.possedeFaces())
				enregistrerTampon(mesh.obtenirFaces());
		}
		/// Création récursive.
		for (auto const& n : noeud.obtenirEnfants())
		{
			creerVBO(n);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner() const
	///
	/// Appelle le dessin du modèle à partir des VBO.  Utilise le modèle 3D
	/// pour obtenir la matériau propre à chaque Mesh.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
    void VBO::dessiner() const
	{
		unsigned int bufferIndex = 0;
        dessiner(modele_->obtenirNoeudRacine(), bufferIndex);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessinerSelected() const
	///
	/// Appelle le dessin du modèle à partir des VBO.  Utilise le modèle 3D
	/// pour obtenir la matériau propre à chaque Mesh.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessinerSelected() const
	{
		unsigned int bufferIndex = 0;
		dessinerSelected(modele_->obtenirNoeudRacine(), bufferIndex);
	}

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VBO::dessinerSelection(glm::fvec3 color) const
    ///
    /// Appelle le dessin du modèle à partir des VBO.  Utilise le modèle 3D
    /// pour obtenir la matériau propre à chaque Mesh.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VBO::dessinerSelection(GLubyte* color) const
    {
        unsigned int bufferIndex = 0;
        dessinerSelection(modele_->obtenirNoeudRacine(), bufferIndex, color);
    }

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	///
	/// Dessin récursif du modèle 3D.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ noeud.obtenirTransformation() };

		/// Empiler la transformation courante
		glPushMatrix();
		glMultMatrixf(glm::value_ptr(m));

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le matériau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			possedeNormales ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
			possedeCouleurs ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, nullptr);
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}

			/// Pour une raison ou une autre, il faut la désactiver après le dessin 
			/// si le modèle possède des couleurs de vertex.
			if (possedeCouleurs)
				glDisable(GL_COLOR_MATERIAL);
			if (possedeNormales)
				glDisable(GL_LIGHTING);

			glMatrixMode(GL_TEXTURE);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		/// Dessin récursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
            dessiner(n, bufferIndex);
		}

		/// Pop de la transformation du noeud courant
		glPopMatrix();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessinerSelected(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	///
	/// Dessin récursif du modèle 3D.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessinerSelected(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ noeud.obtenirTransformation() };

		/// Empiler la transformation courante
		glPushMatrix();
		glMultMatrixf(glm::value_ptr(m));

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le matériau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());

			// Couleur verte pour la sélection
			GLfloat diffusion[3] = { 0.0f, 1.0f, 0.0f };
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusion);

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			possedeNormales ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
			possedeCouleurs ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, nullptr);
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}

			/// Pour une raison ou une autre, il faut la désactiver après le dessin 
			/// si le modèle possède des couleurs de vertex.
			if (possedeCouleurs)
				glDisable(GL_COLOR_MATERIAL);
			if (possedeNormales)
				glDisable(GL_LIGHTING);

			glMatrixMode(GL_TEXTURE);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		/// Dessin récursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
			dessinerSelected(n, bufferIndex);
		}

		/// Pop de la transformation du noeud courant
		glPopMatrix();
	}

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VBO::dessinerSelection(modele::Noeud const& noeud, unsigned int& bufferIndex, glm::fvec3 color) const
    ///
    /// Dessin récursif du modèle 3D.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VBO::dessinerSelection(modele::Noeud const& noeud, unsigned int& bufferIndex, GLubyte* color) const
    {
        // Matrice de transformation
        glm::mat4x4 const& m{ noeud.obtenirTransformation() };

        /// Empiler la transformation courante
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(m));

        for (auto const& mesh : noeud.obtenirMeshes())
        {
            // Appliquer le matériau pour le mesh courant
            appliquerMateriau(mesh.obtenirMateriau());

            // Couleur verte pour la sélection
            GLfloat diffusion[3] = { 0.0f, 1.0f, 0.0f };
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusion);

            bool possedeNormales{ mesh.possedeNormales() };
            bool possedeCouleurs{ mesh.possedeCouleurs() };
            bool possedeTexCoords{ mesh.possedeTexCoords() };
            bool possedeSommets{ mesh.possedeSommets() };
            bool possedeFaces{ mesh.possedeFaces() };

            possedeCouleurs = true;
			glColor3ub(color[0], color[1], color[2]);

            possedeNormales ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
            possedeCouleurs ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);

            if (possedeSommets)
            {
                glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, nullptr);
            }
            if (possedeNormales)
            {
                glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(GL_FLOAT, 0, nullptr);
            }
            if (possedeTexCoords)
            {
                glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
            }
            if (possedeFaces)
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
            }

            /// Pour une raison ou une autre, il faut la désactiver après le dessin 
            /// si le modèle possède des couleurs de vertex.
            if (possedeCouleurs)
                glDisable(GL_COLOR_MATERIAL);
            if (possedeNormales)
                glDisable(GL_LIGHTING);

            glMatrixMode(GL_TEXTURE);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        }
        /// Dessin récursif.
        for (auto const& n : noeud.obtenirEnfants())
        {
            dessinerSelection(n, bufferIndex, color);
        }

        /// Pop de la transformation du noeud courant
        glPopMatrix();
    }

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::liberer()
	///
	/// Relâche la mémoire sur la carte graphique.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::liberer()
	{
		for (auto const& handle : handles_)
		{
			glDeleteBuffers(static_cast<GLsizei>(handles_.size()), handles_.data());
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	///
	/// Assigne un matériau OpenGL selon la méthode dépréciée d'illumination
	/// d'OpenGL
	///
	/// @param[in] materiau : le materiau à assigner
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	{
		/// Assigner la texture
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();

		/// Vérifier si texture existe
		if (modele_->possedeTexture(materiau.nomTexture_)) {
			// Activer le texturage OpenGL et lier la texture appropriée
			glEnable(GL_TEXTURE_2D);
			glScalef(1.0, -1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, modele_->obtenirTextureHandle(materiau.nomTexture_));
		}
		else {
			// Désactiver le texturage OpenGL puisque cet objet n'a aucune texture
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		/// Assigner la matériau
		glMatrixMode(GL_MODELVIEW);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(materiau.diffuse_));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(materiau.speculaire_));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(materiau.ambiant_));
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(materiau.emission_));
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materiau.shininess_ * materiau.shininessStrength_);

		glPolygonMode(
			GL_FRONT_AND_BACK,
			materiau.filDeFer_ ? GL_LINE : GL_FILL);

		materiau.afficherDeuxCotes_ ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	}
}