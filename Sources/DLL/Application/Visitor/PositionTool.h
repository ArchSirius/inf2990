//////////////////////////////////////////////////////////////////////////////
/// @file PositionTool.h
/// @author INF2990-A15-01
/// @date 2015-09-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class PositionTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration
///		   d'enregistrement de position sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-24
///////////////////////////////////////////////////////////////////////////
class PositionTool : public Tool
{
public:
	PositionTool() = default;
	~PositionTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	/// Algorithme par d�faut
	void defaultPosition(NoeudAbstrait* node);
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
