///////////////////////////////////////////////////////////////////////////////
/// @file TranslateTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "TranslateTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../Application/FacadeModele.h"
#include "../../../../Commun/Utilitaire/Vue/ProjectionOrtho.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn TranslateTool::TranslateTool
///     (GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
///
/// Constructeur par param�tres.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
TranslateTool::TranslateTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
	: _deltaX(deltaX), _deltaY(deltaY), _deltaZ(deltaZ)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Impl�mentation du visiteur Translation pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudCylindre* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudDepart(NoeudDepart* node)
///
/// Impl�mentation du visiteur Translation pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudDepart* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudLigne(NoeudSegmentConcret* node)
///
/// Impl�mentation du visiteur Translation pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudSegmentConcret* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Impl�mentation du visiteur Translation pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudMur* node)
{
	defaultTranslate(node);
	node->updatePos();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TranslateTool::defaultTranslate(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur Translation par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::defaultTranslate(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	glm::dvec3 initPos = node->obtenirPositionInitiale();
	glm::dvec3 pos;
	auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();
	pos[0] = initPos[0] + _deltaX * zoom ;
	pos[1] = initPos[1] + _deltaY * zoom ;
	pos[2] = initPos[2] + _deltaZ * zoom ;
	node->assignerPositionRelative(pos);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
