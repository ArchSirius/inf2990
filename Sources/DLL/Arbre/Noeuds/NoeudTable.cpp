////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret() const
{
	NoeudComposite::afficherConcret();
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
	glTranslatef(0, 0, -50);
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
/// @fn void NoeudTable::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::animer(float temps)
{
	NoeudComposite::animer(temps);
	/*
	// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	// Le cube effectue une révolution à toutes les 15 secondes.
	angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
	*/
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
bool NoeudTable::clickHit(GLdouble x, GLdouble y, GLdouble z)
{

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	return (x >= hitbox.coinMin.x*scale_[0] && x <= hitbox.coinMax.x*scale_[0] &&
			y >= hitbox.coinMin.y*scale_[1] && y <= hitbox.coinMax.y*scale_[1]
		//&& z >= hitbox.coinMin.z && z <= hitbox.coinMax.z			// Table concave == ça foire
		);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
