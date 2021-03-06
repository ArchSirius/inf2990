///////////////////////////////////////////////////////////////////////////////
/// @file SetDataTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "SetDataTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SetDataTool::visit(NoeudCylindre* node)
///
/// Impl�mentation du visiteur SetDataTool pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SetDataTool::visit(NoeudCylindre* node)
{
	defaultSetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SetDataTool::visit(NoeudDepart* node)
///
/// Impl�mentation du visiteur SetDataTool pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SetDataTool::visit(NoeudDepart* node)
{
	defaultSetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SetDataTool::visit(NoeudSegmentConcret* node)
///
/// Impl�mentation du visiteur SetDataTool pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SetDataTool::visit(NoeudSegmentConcret* node)
{
	defaultSetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SetDataTool::visit(NoeudMur* node)
///
/// Impl�mentation du visiteur SetDataTool pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SetDataTool::visit(NoeudMur* node)
{
	defaultSetter(node);
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;
	node->updatePos();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SetDataTool::defaultGetter(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SetDataTool::defaultSetter(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	node->assignerPositionRelative(
		glm::dvec3(
			data_->pos_x,
			data_->pos_y,
			node->obtenirPositionRelative().z
		)
	);
	
	node->setScale(
		glm::fvec3(
			data_->scale_x,
			data_->scale_y,
			node->getScale().z
		)
	);

	node->assignerAngle(data_->angle);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
