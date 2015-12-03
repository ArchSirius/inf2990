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
#include <math.h>


////////////////////////////////////////////////////////////////////////
///
/// @fn TranslateTool::TranslateTool
///     (GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
///
/// Constructeur par paramètres.
///
/// @param[in] node : Le noeud à visiter
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
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
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
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud à visiter
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
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud à visiter
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
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudMur* node)
{
	defaultTranslate(node);
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;
	node->updatePos();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TranslateTool::defaultTranslate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Translation par défaut.
///
/// @param[in] node : Le noeud à visiter
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
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getIsPolar())
	{
		auto azimuth = -1.0 * utilitaire::DEG_TO_RAD(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getPolarView().Azimuth);
		auto elevation = utilitaire::DEG_TO_RAD(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getPolarView().Elevation);
		pos[0] = initPos[0] + _deltaX * (zoom + 0.2035) * 0.7;
		pos[1] = initPos[1] + _deltaY * (zoom + 0.2035) * 0.7 * (1.0 + elevation) * 1.1;
		pos[2] = initPos[2] + _deltaZ * zoom;

		const auto wrong = glm::dvec3(pos.x, pos.y, pos.z);
		pos.x = cos(azimuth) * (wrong.x - initPos.x) - sin(azimuth) * (wrong.y - initPos.y) + initPos.x;
		pos.y = sin(azimuth) * (wrong.x - initPos.x) + cos(azimuth) * (wrong.y - initPos.y) + initPos.y;
	}
	else
	{
		pos[0] = initPos[0] + _deltaX * zoom;
		pos[1] = initPos[1] + _deltaY * zoom;
		pos[2] = initPos[2] + _deltaZ * zoom;
	}
	node->assignerPositionRelative(pos);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
