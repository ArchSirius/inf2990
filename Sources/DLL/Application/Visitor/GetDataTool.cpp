///////////////////////////////////////////////////////////////////////////////
/// @file GetDataTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GetDataTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void GetDataTool::visit(NoeudCylindre* node)
///
/// Impl�mentation du visiteur GetDataTool pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GetDataTool::visit(NoeudCylindre* node)
{
	defaultGetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void GetDataTool::visit(NoeudDepart* node)
///
/// Impl�mentation du visiteur GetDataTool pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GetDataTool::visit(NoeudDepart* node)
{
	defaultGetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void GetDataTool::visit(NoeudSegmentConcret* node)
///
/// Impl�mentation du visiteur GetDataTool pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GetDataTool::visit(NoeudSegmentConcret* node)
{
	defaultGetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void GetDataTool::visit(NoeudMur* node)
///
/// Impl�mentation du visiteur GetDataTool pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GetDataTool::visit(NoeudMur* node)
{
	defaultGetter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GetDataTool::defaultGetter(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GetDataTool::defaultGetter(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	data_->pos_x = static_cast<float>(node->obtenirPositionRelative().x);
	data_->pos_y = static_cast<float>(node->obtenirPositionRelative().y);
	data_->scale_x = node->getScale().x;
	data_->scale_y = node->getScale().y;
	data_->angle = node->obtenirAngle();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
