///////////////////////////////////////////////////////////////////////////////
/// @file AngleTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AngleTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void AngleTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Angle pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AngleTool::visit(NoeudCylindre* node)
{
	defaultAngle(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void AngleTool::visit(NoeudDepart* node)
///
/// Implémentation du visiteur Angle pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AngleTool::visit(NoeudDepart* node)
{
	defaultAngle(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void AngleTool::visit(NoeudSegmentConcret* node)
///
/// Implémentation du visiteur Angle pour un noeud de type
/// NoeudSegmentConcret.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AngleTool::visit(NoeudSegmentConcret* node)
{
	defaultAngle(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void AngleTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur Angle pour un noeud de type
/// NoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AngleTool::visit(NoeudMur* node)
{
	defaultAngle(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AngleTool::defaultAngle(NoeudAbstrait* node)
///
/// Implémentation du visiteur Angle par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AngleTool::defaultAngle(NoeudAbstrait* node)
{
	node->assignerAngleInitial(node->obtenirAngle());
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
