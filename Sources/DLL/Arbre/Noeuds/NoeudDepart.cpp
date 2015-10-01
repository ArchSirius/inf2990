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

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::NoeudDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::NoeudDepart(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	// Affichage du mod�le.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


// Visitor
void NoeudDepart::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudDepart::clickHit(GLdouble x, GLdouble y, GLdouble z)
{

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	return (x >= (hitbox.coinMin.x - 1.0)*scale_[0] && x <= (hitbox.coinMax.x + 1.0)*scale_[0] &&
		y >= (hitbox.coinMin.y - 1.0)*scale_[1] && y <= (hitbox.coinMax.y + 1.0)*scale_[1] &&
		z >= (hitbox.coinMin.z - 1.0)*scale_[2] && z <= (hitbox.coinMax.z + 1.0)*scale_[2]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(glm::ivec2 debut, glm::ivec2 fin)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
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

	// TODO : mettre +- 1.0 dans les verifications
	return (hitbox.coinMax.x*scale_[0] >= xMin && hitbox.coinMax.x*scale_[0] <= xMax
		&& hitbox.coinMax.y*scale_[1] <= yMax && hitbox.coinMax.y*scale_[1] >= yMin
		&& hitbox.coinMin.x*scale_[0] >= xMin && hitbox.coinMin.x*scale_[0] <= xMax
		&& hitbox.coinMin.y*scale_[1] <= yMax && hitbox.coinMin.y*scale_[1] >= yMin);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
