////////////////////////////////////////////////////////////////////////////
/// @file NoeudCylindre.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
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
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCylindre::NoeudCylindre(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	assignerEstSelectionnable(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCylindre::~NoeudCylindre()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCylindre::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(10.0f, 10.0f, 10.0f);
	// Affichage du mod�le.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCylindre::accept(Tool& visitor)
///
/// Cette fonction accepte un visiteur, et le bon visiteur.
///
/// @param[in] visitor : Le visiteur qui intervenient sur le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCylindre::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudCylindre::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudCylindre::clickHit(glm::dvec3 point)
{
    auto hitbox = utilitaire::calculerCylindreEnglobant(*modele_);
    auto dist = Distance(point, this);
	
    return (
            dist.r <= hitbox.rayon
        &&  dist.z <= hitbox.haut * 10.0f
        &&  dist.z >= hitbox.bas * 10.0f
        );

	// (x^2 + y^2)^1/2 <= rayon
	/*return (
		sqrt(pow(point.x - positionRelative_.x, 2) + pow(point.y - positionRelative_.y, 2)) <= (hitbox.rayon + 0.4)//*scale_.x
		);*/
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudCylindre::clickHit((glm::ivec2 debut, glm::ivec2 fin)
///
/// V�rifie si le noeud est � l'interieur du rectangle
///
/// @param[in] x, y, z : Les coordonn�es du clic
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
/// Cette fonction permet d'assigner l'�chelle du noeud.
///
/// @param angleInitial : L'�chelle.
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
