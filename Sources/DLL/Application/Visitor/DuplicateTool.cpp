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
#include "../FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::DuplicateTool(glm::dvec3 center,
///     GLfloat newCenterX, GLfloat newCenterY, GLfloat newCenterZ)
///
/// Constructeur par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::DuplicateTool(glm::dvec3 center,
	GLfloat newCenterX, GLfloat newCenterY, GLfloat newCenterZ)
	: _center(center),
	_newCenterX(newCenterX), _newCenterY(newCenterY), _newCenterZ(newCenterZ),
	_arbre(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990())
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::~DuplicateTool
///
/// Destructeur par défaut.
/// Suite à la mise en tampon des objets à dupliquer,
/// on duplique les objets avec le visiteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::~DuplicateTool()
{
	duplicate();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudCylindre* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudDepart* node)
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
/// @fn virtual void DuplicateTool::visit(NoeudLigne* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudLigne* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudMur* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::defaultDuplicate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Duplication par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::defaultDuplicate(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	buffer.push(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::duplicate()
///
/// Duplication des objets en tampon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::duplicate()
{
	while (!buffer.empty())
	{
		auto newNode = _arbre->ajouterNouveauNoeud(
			buffer.top()->obtenirParent()->obtenirType(),
			buffer.top()->obtenirType());
		auto vector = buffer.top()->obtenirPositionRelative() - _center;
		auto newPos = vector + glm::dvec3(_newCenterX, _newCenterY, _newCenterZ);
		newNode->assignerPositionRelative(newPos);
		newNode->assignerAngle(buffer.top()->obtenirAngle());
		buffer.pop();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
