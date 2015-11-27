////////////////////////////////////////////////////////////////////////////
/// @file NoeudDepart.cpp
/// @author INF2990-A15-01
/// @date 2015-09-29
/// @version 1.1
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudDEpart.h"

#include "GL/glew.h"
#include <cmath>
#include <algorithm>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "../../Application/Visitor/Tool.h"
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::NoeudDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::NoeudDepart(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	assignerEstSelectionnable(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	glRotatef(90, 1, 0, 0); 
	glTranslatef(0.0f, -1.0f, 0.0f);
	// Affichage du modèle.
	if (FacadeModele::obtenirInstance()->isSelecting()) {
		GLubyte color[3] = { selectionColor_[0], selectionColor_[1], selectionColor_[2] };
		vbo_->dessinerSelection(color);
	}
	else if (selectionne_) {
		GLubyte color[3] = { 0, 255, 0 };
		vbo_->dessinerSelection(color);
	}
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::accept(Tool& visitor)
///
/// Cette fonction accepte un visiteur, et le bon visiteur.
///
/// @param[in] visitor : Le visiteur qui intervenient sur le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudDepart::clickHit(glm::dvec3 point)
{

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	return (
			point.x >= (hitbox.coinMin.x + positionRelative_.x - 1.0)*scale_.x && point.x <= (hitbox.coinMax.x + positionRelative_.x + 1.0)*scale_.x 
		 && point.y >= (hitbox.coinMin.y + positionRelative_.y - 1.0)*scale_.y && point.y <= (hitbox.coinMax.y + positionRelative_.y + 1.0)*scale_.y 
		 && point.z >= (hitbox.coinMin.z + positionRelative_.z - 1.0)*scale_.z && point.z <= (hitbox.coinMax.z + positionRelative_.z + 1.0)*scale_.z
	);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(glm::ivec2 debut, glm::ivec2 fin)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudDepart::clickHit(glm::ivec2 debut, glm::ivec2 fin)
{
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	int xMax = std::max(debut.x, fin.x);
	int yMax = std::max(debut.y, fin.y);
	int xMin = std::min(debut.x, fin.x);
	int yMin = std::min(debut.y, fin.y);

	return (
		      (hitbox.coinMax.x + positionRelative_.x + 1.0)*scale_.x >= xMin && (hitbox.coinMax.x + positionRelative_.x - 1.0)*scale_.x <= xMax
		   && (hitbox.coinMax.y + positionRelative_.y + 1.0)*scale_.y <= yMax && (hitbox.coinMax.y + positionRelative_.y - 1.0)*scale_.y >= yMin
		   && (hitbox.coinMin.x + positionRelative_.x + 1.0)*scale_.x >= xMin && (hitbox.coinMin.x + positionRelative_.x - 1.0)*scale_.x <= xMax
		   && (hitbox.coinMin.y + positionRelative_.y + 1.0)*scale_.y <= yMax && (hitbox.coinMin.y + positionRelative_.y - 1.0)*scale_.y >= yMin
		);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
