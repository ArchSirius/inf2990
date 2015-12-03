///////////////////////////////////////////////////////////////////////////////
/// @file RotateTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "RotateTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include <math.h>
#include "../../../../Commun/Utilitaire/Utilitaire.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn RotateTool::RotateTool(GLfloat centerX, GLfloat centerY, GLfloat centerZ,
///     GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
///
/// Constructeur par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
RotateTool::RotateTool(GLfloat centerX, GLfloat centerY, GLfloat centerZ,
	GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
	: _centerX(centerX), _centerY(centerY), _centerZ(centerZ),
	  _deltaX(deltaX), _deltaY(deltaY), _deltaZ(deltaZ)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudCylindre* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitNoeudDepart(NoeudDepart* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudDepart* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitNoeudLigne(NoeudSegmentConcret* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudSegmentConcret* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudMur* node)
{
	defaultRotate2d(node);
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;
	node->updatePos();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::defaultTranslate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Rotation par défaut.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::defaultRotate2d(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	float theta = -1 * degrees2radians(_deltaY);
	//makeValidAngle(theta);

	glm::dvec3 initPos = node->obtenirPositionInitiale();
	glm::dvec3 pos;

	// X0  = Centre de rotation
	// X1  = Point domaine
	// X1' = Point image
	// R   = Matrice de rotation
	//
	// X1' = R * (X1 - X0) + X0
	pos[0] = cos(theta) * (initPos[0] - _centerX) - sin(theta) * (initPos[1] - _centerY) + _centerX;
	pos[1] = sin(theta) * (initPos[0] - _centerX) + cos(theta) * (initPos[1] - _centerY) + _centerY;
    pos[2] = node->obtenirPositionRelative().z;
	node->assignerPositionRelative(pos);

	float newAngle = node->obtenirAngleInitial() + radians2degrees(theta);
	//makeValidAngle(newAngle);
	
	node->assignerAngle(newAngle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RotateTool::degrees2radians(const float degrees) const
///
/// Conversion d'un angle de degrés en radians
///
/// @param[in] degrees : Angle en degrés.
///
/// @return Angle en radians.
///
////////////////////////////////////////////////////////////////////////
float RotateTool::degrees2radians(const float degrees) const
{
	return degrees * static_cast<float>(utilitaire::PI) / 180.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RotateTool::radians2degrees(const float degrees) const
///
/// Conversion d'un angle de radians en degrés
///
/// @param[in] degrees : Angle en radians.
///
/// @return Angle en degrés.
///
////////////////////////////////////////////////////////////////////////
float RotateTool::radians2degrees(const float radians) const
{
	return radians * 180.0f / static_cast<float>(utilitaire::PI);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RotateTool::makeValidAngle(const float angle) const
///
/// Ramène un angle entre 0 et 2PI radians
///
/// @param[in out] angle : Angle en radians.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::makeValidAngle(float& angle) const
{
	if (angle >= 2 * static_cast<float>(utilitaire::PI))
		angle -= 2 * static_cast<float>(utilitaire::PI);
	else if (angle < 0)
		angle += 2 * static_cast<float>(utilitaire::PI);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
