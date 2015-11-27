///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.h
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup opengl
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __VBO_H__
#define __VBO_H__

#include "GL/glew.h"
#include "glm\glm.hpp"

#include <vector>
#include <type_traits>

namespace modele{
	class  Modele3D;
	class  Noeud;
	struct Materiau;
}

namespace opengl{
	///////////////////////////////////////////////////////////////////////////
	/// @class VBO
	/// @brief Classe permettant le dessin d'un modèle 3D par VBO.
	///
	/// @note Précondition : prends pour acquis que le pointeur vers le modèle
	/// 3D reste valide durant toute la durée de vie du storage.  Le modèle est
	/// considéré "constant", c'est-à-dire que ses meshes ne sont pas modifiés
	/// et qu'il n'est pas relâché lors de l'appel au dessin.
	/// Une modification à la géométrie du modèle nécessite de libérer le VBO 
	/// et le recréer.
	///
	/// @author Martin Paradis
	/// @date 2015-08-28
	///////////////////////////////////////////////////////////////////////////
	class VBO {
	public:
		VBO() = default;
		/// Constructeur à partir d'un modèle 3D
		VBO(modele::Modele3D const* modele);

		/// Destructeur
		virtual ~VBO();

		/// Permet de charger les données/commandes sur la carte graphique
		virtual void charger();
		/// Permet d'effectuer le dessin du modèle 3D
		virtual void dessiner() const;
		void dessinerSelected() const;
        void dessinerSelection(GLubyte* color) const;
		/// Permet de relâcher les données/commandes sur la crate graphique
		virtual void liberer();

	private:
		/// Méthode "helper" pour passer les données du mesh vers la carte graphique
		template <typename T>
		inline void enregistrerTampon(T const& data);

		/// Assigne le matériau/texture courante d'un mesh.
		void appliquerMateriau(modele::Materiau const& materiau) const;
		/// Création récursive des VBO
		void creerVBO(modele::Noeud const& noeud);
		/// Dessin récursif
        void dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const;
        void dessinerSelected(modele::Noeud const& noeud, unsigned int& bufferIndex) const;
        void dessinerSelection(modele::Noeud const& noeud, unsigned int& bufferIndex, GLubyte* color) const;

		/// Permet de vérifier si l'identifiant est valide
		inline bool identifiantEstValide() const;

		/// Modèle à dessiner
		modele::Modele3D const* modele_{ nullptr };
		/// Les identifiants OpenGL.
		std::vector<unsigned int> handles_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <typename T> inline void VBO::enregistrerTampon(T const& data)
	///
	/// Permet de charger les données d'un modèle (vertex, normales, texCoord, etc.)
	/// en mémoire de la carte graphique et de conserver un handle vers les données.
	///
	/// @param[in] data : le vecteur contenant les données.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline void VBO::enregistrerTampon(T const& data)
	{
		/// Le type contenu dans le std::vecteur (glm::vec3, glm::ivec3, etc.)
		using type = T::value_type;
		/// Le type contenu dans le glm::vec (float, int, etc.)
		using subType = type::value_type;
		/// Le tampon à envoyer à la carte graphique
		std::vector<subType> tampon;
		/// Récupérer la dimension du glm::vec
		int size = type{}.length();
		tampon.reserve(data.size() * size);

		/// Créer un tampon séquentiel.
		for (auto const& subData : data)
		{
			for (int i = 0; i < subData.length(); ++i)
			{
				tampon.push_back(subData[i]);
			}
		}

		/// On assume que les entiers sont utilisés pour les indices.
		auto bufferType = std::is_same<subType, int>::value ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;

		/// Transférer le tampon créé.
		unsigned int tamponSommet;
		glGenBuffers(1, &tamponSommet);
		glBindBuffer(bufferType, tamponSommet);
		glBufferData(bufferType, tampon.size() * sizeof(subType), data.data(), GL_STATIC_DRAW);
		/// Conserver le handle.
		handles_.push_back(tamponSommet);
	}
}
#endif /// __VBO_H__