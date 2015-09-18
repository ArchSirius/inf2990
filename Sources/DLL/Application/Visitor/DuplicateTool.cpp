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
/// Constructeur par défaut ou par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::DuplicateTool(GLfloat x, GLfloat y, GLfloat z)
	: _deltaX(x), _deltaY(y), _deltaZ(z)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visitNoeudCylindre(NoeudCylindre* node)
{
	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visitNoeudDepart(NoeudDepart* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visitNoeudDepart(NoeudDepart* node)
{
	// NoeudDepart ne peut pas être dupliqué
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visitNoeudLigne(NoeudLigne* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visitNoeudLigne(NoeudLigne* node)
{
	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visitvisitNoeudMur(visitNoeudMur* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visitNoeudMur(NoeudMur* node)
{
	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::defaultDelete(NoeudAbstrait* node)
///
/// Implémentation du visiteur Duplication par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::defaultDuplicate(NoeudAbstrait* node)
{
	auto newNode = std::make_unique<NoeudAbstrait>(*node);
	glm::dvec3 newPos;
	newPos[0] += _deltaX;
	newPos[1] += _deltaY;
	newPos[2] += _deltaZ;
	newNode->assignerPositionRelative(newPos);
	node->obtenirParent()->ajouter(std::move(newNode));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
