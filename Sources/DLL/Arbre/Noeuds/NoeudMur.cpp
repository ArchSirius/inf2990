////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
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
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
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

// Visitor
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
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
