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

	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCylindre::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCylindre::animer(float temps)
{
	/*
	// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	// Le cube effectue une révolution à toutes les 15 secondes.
	angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
	*/
}

// Visitor
void NoeudCylindre::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudCylindre::clickHit(modele::Modele3D const& modele, 
/// GLdouble x, GLdouble y, GLdouble z)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] modele : Le modèle du noeud
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudCylindre::clickHit(modele::Modele3D const& modele, GLdouble x, GLdouble y, GLdouble z)
{

	utilitaire::CylindreEnglobant hitbox = utilitaire::calculerCylindreEnglobant(modele);

	// Ici ça fait une boite carrée
	/*return (x >= positionRelative_[0] - hitbox.rayon && x <= positionRelative_[0] + hitbox.rayon &&
			y >= positionRelative_[1] - hitbox.rayon && y <= positionRelative_[1] + hitbox.rayon);*/


	// (x^2 + y^2)^1/2 <= rayon, bas <= z <= haut (LE CYLINDRE PAS DE TOP SCRAP LA LECTURE DU Z)
	return (
		sqrt( pow(x - positionRelative_[0], 2) + pow(y - positionRelative_[1], 2) ) <= hitbox.rayon 
		//&& z <= positionRelative_[2] - hitbox.bas 
		//&& z >= positionRelative_[2] + hitbox.haut
		);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
