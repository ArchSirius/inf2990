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
/// et donner des valeurs par d�faut aux variables membres.
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
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(0, 0, -50);

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
/// @fn void NoeudAbstrait::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::clickHit(glm::dvec3 point)
{

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	return (
			point.x >= hitbox.coinMin.x + positionRelative_.x && point.x <= hitbox.coinMax.x + positionRelative_.x 
		 && point.y >= hitbox.coinMin.y + positionRelative_.y && point.y <= hitbox.coinMax.y + positionRelative_.y
		//&& z >= hitbox.coinMin.z && z <= hitbox.coinMax.z			// Table concave == �a foire
		);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
