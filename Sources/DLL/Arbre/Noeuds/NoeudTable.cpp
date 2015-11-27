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
#include "NoeudTable.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "FacadeModele.h"

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
	assignerEstSelectionnable(false);
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
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(0, 0, -50);

	// Affichage du mod�le.
	if (FacadeModele::obtenirInstance()->isSelecting()) {
		GLubyte color[3] = { selectionColor_[0], selectionColor_[1], selectionColor_[2] };
		vbo_->dessinerSelection(color);
	}
	else if (selectionne_) {
		GLubyte color[3] = { 0, 255, 0 };
		vbo_->dessinerSelection(color);
	}
	else
		vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
	NoeudComposite::afficherConcret();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::clickHit(glm::dvec3 point)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] point : Les coordonn�es du clic
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
