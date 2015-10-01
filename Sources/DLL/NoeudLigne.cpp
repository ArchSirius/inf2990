////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Sabrina Barouche
/// @date 2015-09-29
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudLigne.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "../../Application/Visitor/Tool.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::NoeudLigne(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud, float posX, 
///							float posY, float posZ)
///
/// Ce constructeur appele la version de la classe de base
/// et donne des valeurs  aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
/// @param[in] posX,Y,Z : Positions en 3d du noeud.
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
/*
NoeudMur::NoeudMur(const std::string& typeNoeud, float posX, float posY, float posZ)
: NoeudAbstrait{ typeNoeud }
{
posX_ = posX;
posY_ = posY;
posZ_ = posZ;
}*/

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::~NoeudLigne()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Translation.
/*	glTranslatef(positionRelative_[0], positionRelative_[1], positionRelative_[2]);
	// Rotation autour de l'axe des X.
	glRotatef(angleX_, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	glRotatef(angleY_, 0, 1, 0);
	*/
	/*glMatrixMode( GL_PROJECTION );
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(/*mouseDown*/);
		glVertex3f(/*mousePosition*/);
		glEnd(); 
*/
	

	//FacadeModele::Con

	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	// Restauration de la matrice. */
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

// Visitor
void NoeudLigne::accept(Tool& visitor)
{
	visitor.visit(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////