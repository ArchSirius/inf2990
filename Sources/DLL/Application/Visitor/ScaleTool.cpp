///////////////////////////////////////////////////////////////////////////////
/// @file ScaleTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ScaleTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ScaleTool::ScaleTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
///
/// Constructeur par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ScaleTool::ScaleTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
	: _deltaX(deltaX), _deltaY(deltaY), _deltaZ(deltaZ)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ScaleTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Implémentation du visiteur Mise à l'échelle pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ScaleTool::visit(NoeudCylindre* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	glm::fvec3 initScale = node->getScaleInitial();
	glm::fvec3 scale;

	// X
	scale[0] = initScale[0] + _deltaY / 10.f;
	if (scale[0] < 0.2)
		scale[0] = 0.2f;
	// Y
	scale[1] = initScale[1] + _deltaY / 10.f;
	if (scale[1] < 0.2)
		scale[1] = 0.2f;
	// Z
	scale[2] = initScale[2];

	node->setScale(scale);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ScaleTool::visitNoeudDepart(NoeudDepart* node)
///
/// Implémentation du visiteur Mise à l'échelle pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ScaleTool::visit(NoeudDepart* node)
{
	// NoeudDepart ne peut pas être mis à l'échelle
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ScaleTool::visitNoeudLigne(NoeudLigne* node)
///
/// Implémentation du visiteur Mise à l'échelle pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ScaleTool::visit(NoeudLigne* node)
{
	// NoeudLigne ne peut pas être mis à l'échelle
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ScaleTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Mise à l'échelle pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ScaleTool::visit(NoeudMur* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	glm::fvec3 initScale = node->getScaleInitial();
	glm::fvec3 scale;

	// X
	scale[0] = initScale[0];
	// Y
	scale[1] = initScale[1] + _deltaY / 10.f;
	if (scale[1] < 0.2)
		scale[1] = 0.2f;
	// Z
	scale[2] = initScale[2];

	node->setScale(scale);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
