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
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudDepart* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitNoeudLigne(NoeudLigne* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudLigne* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Rotation pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::visit(NoeudMur* node)
{
	defaultRotate2d(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void RotateTool::defaultTranslate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Rotation par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RotateTool::defaultRotate2d(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	//VERIF
	float theta = -1 * degrees2radians(_deltaY);
	makeValidAngle(theta);

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
	node->assignerPositionRelative(pos);

	float newAngle = node->obtenirAngleInitial() + theta;
	makeValidAngle(newAngle);
	
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
	return degrees * (float)utilitaire::PI / 180.0f;
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
	if (angle >= 2 * (float)utilitaire::PI)
		angle -= 2 * (float)utilitaire::PI;
	else if (angle < 0)
		angle += 2 * (float)utilitaire::PI;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
