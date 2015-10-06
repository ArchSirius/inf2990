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
/// et donner des valeurs par défaut aux variables membres.
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
/// @fn NoeudLigneComposite::~NoeudLigneComposite()
///
/// Ce destructeur désallouee la liste d'affichage du la ligne.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneComposite::~NoeudLigneComposite()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneComposite::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneComposite::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
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
/// @fn void NoeudLigneComposite::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudLigneComposite::clickHit(GLdouble x, GLdouble y, GLdouble z)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
