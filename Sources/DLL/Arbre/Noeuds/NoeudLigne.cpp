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
#include <iostream>

#include "GL/glew.h"
#include <cmath>
#include <math.h>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <algorithm>

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
	//glTranslatef(positionRelative_[0], positionRelative_[1], positionRelative_[2]);
	// Rotation autour de l'axe des X.
	//glRotatef(90, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	//glRotatef(angleY_, 0, 1, 0);
	
	/*glMatrixMode( GL_PROJECTION );
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		//glVertex3f(/*mouseDown);*/
		//glVertex3f(/*mousePosition*/);
		//glEnd(); 

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(1.0, 1.0, 1.0 , 0.3);
	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(5.0f, 1.0f, 1.0f);
	//afficherFantome();

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


void NoeudLigne::afficherFantome(glm::ivec2 posOrigin, glm::ivec2 posActuel)
{
	const float rapportScale_ = 1.0f;
	std::cout << "----------afficherFantome---------\n";
	glPushMatrix();
		glTranslatef((posActuel.x - posOrigin.x)/2, (posActuel.y - posOrigin.y)/2, 0.0f);
		glRotatef(atan((posActuel.y - posOrigin.y)/(posActuel.x - posOrigin.x)), 0 , 0 , 1 );
		glScalef( rapportScale_ * (posActuel.x - posOrigin.x), 1.0f, 1.0f);
	glPopMatrix();

	/*
	glLineWidth(2.5);

	glColor4d(1.0, 1.0, 0.0, 0.5);
	glBegin(GL_LINE);
		glVertex3f(posOrigin.x, posOrigin.y, 200.0);
		glVertex3f(0.0, 0.0, 200.0);
	glEnd();
	*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudLigne::clickHit(GLdouble x, GLdouble y, GLdouble z)
{

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	return (x >= (hitbox.coinMin.x + positionRelative_[0]) && x <= (hitbox.coinMax.x + positionRelative_[0]) &&
		y >= (hitbox.coinMin.y + positionRelative_[1]) && y <= (hitbox.coinMax.y + positionRelative_[1])); /*&&
		z >= (hitbox.coinMin.z - 1.0)*scale_[2] && z <= (hitbox.coinMax.z + 1.0)*scale_[2]*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::clickHit(glm::ivec2 debut, glm::ivec2 fin)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudLigne::clickHit(glm::ivec2 debut, glm::ivec2 fin)
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