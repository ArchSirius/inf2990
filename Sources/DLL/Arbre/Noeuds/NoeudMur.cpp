////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	/*
	// R�volution autour du centre.
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
	// Affichage du mod�le.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::animer(float temps)
{
	/*
	// Le cube effectue un tour � toutes les 7 secondes sur l'axe des X.
	angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	// Le cube effectue un tour � toutes les 3 secondes sur l'axe des Y.
	angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	// Le cube effectue une r�volution � toutes les 15 secondes.
	angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
	*/
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////