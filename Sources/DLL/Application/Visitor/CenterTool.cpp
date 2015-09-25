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
	: _minX(DBL_MAX), _maxX(DBL_MIN),
	  _minY(DBL_MAX), _maxY(DBL_MIN),
	  _minZ(DBL_MAX), _maxZ(DBL_MIN)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::visitNoeudCylindre(NoeudCylindre* node)
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
/// @fn virtual void CenterTool::visitNoeudDepart(NoeudDepart* node)
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
/// @fn virtual void CenterTool::visitNoeudLigne(NoeudLigne* node)
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
/// @fn virtual void CenterTool::visitvisitNoeudMur(visitNoeudMur* node)
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
/// @fn virtual void CenterTool::defaultTranslate(NoeudAbstrait* node)
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

	if (pos[0] < _minX)
		_minX = pos[0];
	if (pos[0] > _maxX)
		_maxX = pos[0];

	if (pos[1] < _minY)
		_minY = pos[1];
	if (pos[1] > _maxY)
		_maxY = pos[1];

	if (pos[2] < _minZ)
		_minZ = pos[2];
	if (pos[2] > _maxZ)
		_maxZ = pos[2];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CenterTool::getCenter()
///
/// Retourne le centre des objets visités
///
/// @return le centre en glm::dvec3
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 CenterTool::getCenter() const
{
	glm::dvec3 center;

	if (_minX == DBL_MAX ||
		_maxX == DBL_MIN ||
		_minY == DBL_MAX ||
		_maxY == DBL_MIN ||
		_minZ == DBL_MAX ||
		_maxZ == DBL_MIN)
	{
		center[0] = 0;
		center[1] = 0;
		center[2] = 0;
	}
	else
	{
		center[0] = (_minX + _maxX) / 2.;
		center[1] = (_minY + _maxY) / 2.;
		center[2] = (_minZ + _maxZ) / 2.;
	}

	return center;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
