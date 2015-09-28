///////////////////////////////////////////////////////////////////////////////
/// @file CenterTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "CenterTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn CenterTool::CenterTool
///
/// Constructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
CenterTool::CenterTool()
	: _nbObj(0)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Centre pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterTool::visit(NoeudCylindre* node)
{
	defaultCenter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::visit(NoeudDepart* node)
///
/// Implémentation du visiteur Centre pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterTool::visit(NoeudDepart* node)
{
	defaultCenter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::visit(NoeudLigne* node)
///
/// Implémentation du visiteur Centre pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterTool::visit(NoeudLigne* node)
{
	defaultCenter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur Centre pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterTool::visit(NoeudMur* node)
{
	defaultCenter(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CenterTool::defaultCenter(NoeudAbstrait* node)
///
/// Implémentation du visiteur Centre par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterTool::defaultCenter(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	auto pos = node->obtenirPositionInitiale();

	++_nbObj;
	_sum += pos;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CenterTool::getCenter()
///
/// Retourne le centre des objets visités
///
/// @return le centre en glm::dvec3
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 CenterTool::getCenter() const
{
	glm::dvec3 center;

	if (_nbObj == 0)
	{
		center[0] = 0;
		center[1] = 0;
		center[2] = 0;
	}
	else
	{
		center[0] = _sum[0] / _nbObj;
		center[1] = _sum[1] / _nbObj;
		center[2] = _sum[2] / _nbObj;
	}

	return center;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
