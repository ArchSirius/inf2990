///////////////////////////////////////////////////////////////////////////////
/// @file PositionTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "PositionTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void PositionTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Position pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionTool::visit(NoeudCylindre* node)
{
	defaultPosition(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void PositionTool::visit(NoeudDepart* node)
///
/// Implémentation du visiteur Position pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionTool::visit(NoeudDepart* node)
{
	defaultPosition(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void PositionTool::visit(NoeudLigne* node)
///
/// Implémentation du visiteur Position pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionTool::visit(NoeudLigne* node)
{
	defaultPosition(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void PositionTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur Position pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionTool::visit(NoeudMur* node)
{
	defaultPosition(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PositionTool::defaultPosition(NoeudAbstrait* node)
///
/// Implémentation du visiteur Position par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionTool::defaultPosition(NoeudAbstrait* node)
{
	node->assignerPositionInitiale(node->obtenirPositionRelative());
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
