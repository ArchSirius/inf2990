////////////////////////////////////////////////////////////////////////////
/// @file NoeudSegmentConcret.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
/// @date 2015-09-29
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudSegmentConcret.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>
#include <math.h>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <algorithm>

#include "../../Application/Visitor/Tool.h"
#include "../../Application/Visitor/SelectBrothersTool.h"
#include "../../Application/FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegmentConcret::NoeudSegmentConcret(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegmentConcret::NoeudSegmentConcret(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	assignerEstSelectionnable(true);
	scaleInitial_.x = 2.0f;
	scale_.x = scaleInitial_.x;
	scalable_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegmentConcret::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegmentConcret::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(0.0, 0.0, - 2.0);
	//glScalef(2.0f, 1.0f, 1.0f);

	// Affichage du modèle.
	if (FacadeModele::obtenirInstance()->isSelecting()) {
		GLubyte color[3] = { selectionColor_[0], selectionColor_[1], selectionColor_[2] };
		vbo_->dessinerSelection(color);
	}
	else if (selectionne_) {
		vbo_->dessinerSelected();
	}
	else
		vbo_->dessiner();
	// Restauration de la matrice. */
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegmentConcret::accept(Tool& visitor)
///
/// Cette fonction accepte un visiteur, et le bon visiteur.
///
/// @param[in] visitor : Le visiteur qui intervenient sur le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegmentConcret::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegmentConcret::updateCreation(glm::dvec3 cursor) 
///
/// Dit au noeud de mettre à jour son affichage par rapport au curseur.
/// Utilisé lors de la création d'un noeud en deux étapes (mur, ligne).
///
/// @param[in] cursor : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegmentConcret::updateCreation(glm::dvec3 cursor)
{
	// Calculer l'angle de rotation
	glm::dvec3 delta = cursor - positionInitiale_;
	angleRotation_ = static_cast<float>((atan2(delta.y, delta.x) * (180.0 / utilitaire::PI)) - 90.0);
	angleRotationInitial_ = angleRotation_;

	// Calculer le scale nécessaire
	double vecLength = sqrt(pow(delta.x, 2.0) + pow(delta.y, 2.0));
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);
	double unitLength = hitbox.coinMax.y - hitbox.coinMin.y;

	scale_.y = static_cast<float>(vecLength / unitLength);
	scaleInitial_.y = scale_.y;


	// Calculer le centre
	positionRelative_[0] = positionInitiale_[0] + delta[0] / 2.0;
	positionRelative_[1] = positionInitiale_[1] + delta[1] / 2.0;
	positionRelative_[2] = positionInitiale_[2] + delta[2] / 2.0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudSegmentConcret::setScale( const glm::fvec3 scale )
///
/// Cette fonction permet d'assigner l'échelle du noeud.
///
/// @param scale : L'échelle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudSegmentConcret::setScale(const glm::fvec3 scale)
{
	if (scalable_)
		scale_.y = scale.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudSegmentConcret::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudSegmentConcret::assignerSelection(bool selectionne)
{
	auto visitor = SelectBrothersTool(parent_, selectionne);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudSegmentConcret::assignerSelectionFromVisitor( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudSegmentConcret::assignerSelectionFromVisitor(bool selectionne)
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegmentConcret::lineHit(glm::dvec3 point) 
///
/// Vérifie si le point touche le noeud présent, s'il est une ligne.
///
/// @param[in] cursor : Les coordonnées du clic
///
/// @return Vrai si le point touche la ligne, faux sinon (ou si ce n'est pas une ligne).
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegmentConcret::lineHit(glm::dvec3 point)
{
	return clickHit(point);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
