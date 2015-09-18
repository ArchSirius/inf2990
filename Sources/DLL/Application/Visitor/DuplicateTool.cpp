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
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../Arbre/Noeuds/NoeudAbstrait.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::DuplicateTool(GLfloat x, GLfloat y, GLfloat z)
///
/// Constructeur par défaut ou par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::DuplicateTool(GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f)
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
void DuplicateTool::visit(NoeudCylindre* node)
{
	auto newNode = std::make_unique<NoeudCylindre>(*node);
	glm::dvec3 newPos;
	newPos[0] += _deltaX;
	newPos[1] += _deltaY;
	newPos[2] += _deltaZ;
	newNode->assignerPositionRelative(newPos);
	node->obtenirParent()->ajouter(std::move(newNode));
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
void DuplicateTool::visit(NoeudDepart* node)
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
void DuplicateTool::visit(NoeudLigne* node)
{
	auto newNode = std::make_unique<NoeudLigne>(*node);
	glm::dvec3 newPos;
	newPos[0] += _deltaX;
	newPos[1] += _deltaY;
	newPos[2] += _deltaZ;
	newNode->assignerPositionRelative(newPos);
	node->obtenirParent()->ajouter(std::move(newNode));
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
void DuplicateTool::visit(NoeudMur* node)
{
	auto newNode = std::make_unique<NoeudMur>(*node);
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
