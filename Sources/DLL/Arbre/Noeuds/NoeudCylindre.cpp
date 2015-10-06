////////////////////////////////////////////////////////////////////////////
/// @file NoeudCylindre.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudCylindre.h"

#include "GL/glew.h"
#include <cmath>
#include <algorithm>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "../../Application/Visitor/Tool.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCylindre::NoeudCylindre(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCylindre::NoeudCylindre(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCylindre::~NoeudCylindre()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCylindre::~NoeudCylindre()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCylindre::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCylindre::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	/*
	// Révolution autour du centre.
	glRotatef(angleRotation_, 0, 0, 1);
	// Translation.
	glTranslatef(10, 0, 0);
	// Rotation autour de l'axe des X.
	glRotatef(angleX_, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	glRotatef(angleY_, 0, 1, 0);
	// Recentrage du cube.
	glTranslatef(0, 0, -10);
	*/
	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(10.0f, 10.0f, 10.0f);
	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

// Visitor
void NoeudCylindre::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudCylindre::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudCylindre::clickHit(glm::dvec3 point)
{

	utilitaire::CylindreEnglobant hitbox = utilitaire::calculerCylindreEnglobant(*modele_);
	
	// (x^2 + y^2)^1/2 <= rayon, bas <= z <= haut (LE Z MARCHE PAS)
	return (
		sqrt(pow(point.x - positionRelative_.x, 2) + pow(point.y - positionRelative_.y, 2)) <= (hitbox.rayon + 0.4)*scale_.x
		//&& z <= positionRelative_.z - hitbox.bas 
		//&& z >= positionRelative_.z + hitbox.haut
		);
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudCylindre::clickHit((glm::ivec2 debut, glm::ivec2 fin)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudCylindre::clickHit(glm::ivec2 debut, glm::ivec2 fin)
{

	utilitaire::CylindreEnglobant hitbox = utilitaire::calculerCylindreEnglobant(*modele_);

	int xMax = std::max(debut.x, fin.x);
	int yMax = std::max(debut.y, fin.y);
	int xMin = std::min(debut.x, fin.x);
	int yMin = std::min(debut.y, fin.y);

	return(positionRelative_.x + (hitbox.rayon + 0.4)*scale_.x <= xMax && positionRelative_.x + (hitbox.rayon + 0.4)*scale_.x >= xMin
		&& positionRelative_.x - (hitbox.rayon + 0.4)*scale_.x <= xMax && positionRelative_.x - (hitbox.rayon + 0.4)*scale_.x >= xMin
		&& positionRelative_.y + (hitbox.rayon + 0.4)*scale_.y <= yMax && positionRelative_.y + (hitbox.rayon + 0.4)*scale_.y >= yMin
		&& positionRelative_.y - (hitbox.rayon + 0.4)*scale_.y <= yMax && positionRelative_.y - (hitbox.rayon + 0.4)*scale_.y >= yMin);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudCylindre::setScale( const glm::fvec3 scale )
///
/// Cette fonction permet d'assigner l'échelle du noeud.
///
/// @param angleInitial : L'échelle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudCylindre::setScale(const glm::fvec3 scale)
{
	scale_.x = scale.x;
	scale_.y = scale.x;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
