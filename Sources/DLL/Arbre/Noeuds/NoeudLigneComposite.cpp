////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudLigneComposite.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneComposite::NoeudLigneComposite(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneComposite::NoeudLigneComposite(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerEstSelectionnable(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneComposite::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneComposite::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
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
/// @fn void NoeudLigneComposite::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudLigneComposite::clickHit(glm::dvec3 point)
{
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneComposite::lineHit(glm::dvec3 point) 
///
/// V�rifie si le point touche le noeud pr�sent, s'il est une ligne.
///
/// @param[in] cursor : Les coordonn�es du clic
///
/// @return Vrai si le point touche la ligne, faux sinon (ou si ce n'est pas une ligne).
///
////////////////////////////////////////////////////////////////////////
bool NoeudLigneComposite::lineHit(glm::dvec3 point)
{
	std::cout << "Ligne concrete : " << point.x << ", " << point.y << ", " << point.z << " : " << clickHit(point) << std::endl;
	return clickHit(point);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
