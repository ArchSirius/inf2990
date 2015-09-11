///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAraignee.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::~NoeudAraignee()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::~NoeudAraignee()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotatef(35, sqrtf(2), sqrtf(2), 0);
	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

// Test : Applique une translation a l'araignée.
void NoeudAraignee::translate(int x, int y, int z)
{
	positionRelative_[0] += x;
	positionRelative_[1] -= y;
	positionRelative_[2] += z;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
