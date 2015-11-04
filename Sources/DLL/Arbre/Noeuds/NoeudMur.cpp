////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"

#include "GL/glew.h"
#include <cmath>
#include <math.h>

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
NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	scale_ = { 1.0f, 1.0f, 1.0f };
	scaleInitial_ = scale_;
	assignerEstSelectionnable(true);
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
void NoeudMur::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	// Bonne orientation de base;
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

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
/// @fn inline void NoeudMur::setScale( const glm::fvec3 scale )
///
/// Cette fonction permet d'assigner l'échelle du noeud.
///
/// @param angleInitial : L'échelle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudMur::setScale(const glm::fvec3 scale)
{
	scale_.y = scale.y;
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
void NoeudMur::accept(Tool& visitor)
{
	visitor.visit(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::updateCreation(glm::dvec3 cursor) 
///
/// Dit au noeud de mettre à jour son affichage par rapport au curseur.
/// Utilisé lors de la création d'un noeud en deux étapes (mur, ligne).
///
/// @param[in] cursor : Les coordonnées du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::updateCreation(glm::dvec3 cursor)
{
	// Calculer l'angle de rotation
	glm::dvec3 delta = cursor - positionInitiale_;
	angleRotation_ = static_cast<float>( (atan2(delta.y, delta.x) * (180.0 / utilitaire::PI)) - 90.0 );
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

	// Mettre à jour les points
	_start = positionInitiale_;
	_end = cursor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::updatePos()
///
/// Cette fonction met à jour l'ensemble des deux points de début et de fin du mur
///
/// @return L'ensemble de points
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::updatePos()
{
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);
	const auto unitLength = hitbox.coinMax.y - hitbox.coinMin.y;

	glm::dvec3 base_start(0.0, unitLength / 2.0, hitbox.coinMin.z);
	glm::dvec3 base_end(0.0, -unitLength / 2.0, hitbox.coinMin.z);

	base_start.y *= scale_.y;
	base_end.y *= scale_.y;

	base_start.x *= scale_.y;
	base_end.x *= scale_.y;

	const double angle = utilitaire::DEG_TO_RAD(angleRotation_);

	_start.x = cos(angle) * (base_start.x) - sin(angle) * (base_start.y) + positionRelative_.x;
	_start.y = sin(angle) * (base_start.x) + cos(angle) * (base_start.y) + positionRelative_.y;

	_end.x = cos(angle) * (base_end.x) - sin(angle) * (base_end.y) + positionRelative_.x;
	_end.y = sin(angle) * (base_end.x) + cos(angle) * (base_end.y) + positionRelative_.y;

	std::cout << "updatePos\n";
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
