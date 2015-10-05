///////////////////////////////////////////////////////////////////////////////
/// @file InvalidTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "InvalidTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void InvalidTool::visit(NoeudCylindre* node)
///
/// Impl�mentation du visiteur Invalide pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::visit(NoeudCylindre* node)
{
	defaultInvalid(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void InvalidTool::visit(NoeudDepart* node)
///
/// Impl�mentation du visiteur Invalide pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::visit(NoeudDepart* node)
{
	defaultInvalid(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void InvalidTool::visit(NoeudSegmentConcret* node)
///
/// Impl�mentation du visiteur Invalide pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::visit(NoeudSegmentConcret* node)
{
	defaultInvalid(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void InvalidTool::visit(NoeudMur* node)
///
/// Impl�mentation du visiteur Invalide pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::visit(NoeudMur* node)
{
	defaultInvalid(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void InvalidTool::defaultInvalid(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur Invalide par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::defaultInvalid(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	node->assignerPositionRelative(node->obtenirPositionInitiale());
	node->assignerAngle(node->obtenirAngleInitial());
	node->setScale(node->getScaleInitial());
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
