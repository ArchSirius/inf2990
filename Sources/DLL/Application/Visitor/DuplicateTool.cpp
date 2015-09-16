///////////////////////////////////////////////////////////////////////////////
/// @file DuplicateTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "DuplicateTool.h"
#include "NoeudAbstrait.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::DuplicateTool(GLfloat x, GLfloat y, GLfloat z)
///
/// Constructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::DuplicateTool(GLfloat x, GLfloat y, GLfloat z)
{
	_x = x;
	_y = y;
	_z = z;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudAbstrait* node)
///
/// Implémentation du visiteur Copier pour un noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudAbstrait* node)
{
	NoeudAbstrait* newNode = new NoeudAbstrait(*node);
	glm::dvec3 newPos;
	newPos[0] += _x;
	newPos[1] += _y;
	newPos[2] += _z;
	newNode->assignerPositionRelative(newPos);
	node->obtenirParent()->ajouter(newNode);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
