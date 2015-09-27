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
/// @fn virtual void InvalidTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Implémentation du visiteur Invalide pour un noeud de type
/// NoeudCylindre.
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
/// @fn virtual void InvalidTool::visitNoeudDepart(NoeudDepart* node)
///
/// Implémentation du visiteur Invalide pour un noeud de type
/// NoeudDepart.
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
/// @fn virtual void InvalidTool::visitNoeudLigne(NoeudLigne* node)
///
/// Implémentation du visiteur Invalide pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void InvalidTool::visit(NoeudLigne* node)
{
	defaultInvalid(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void InvalidTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Invalide pour un noeud de type
/// visitNoeudMur.
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
/// @fn void InvalidTool::defaultTranslate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Invalide par défaut.
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
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
