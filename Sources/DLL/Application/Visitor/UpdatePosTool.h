//////////////////////////////////////////////////////////////////////////////
/// @file UpdatePosTool.h
/// @author INF2990-A15-01
/// @date 2015-11-06
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class UpdatePosTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration
///		   de mise � jour de position sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-11-06
///////////////////////////////////////////////////////////////////////////
class UpdatePosTool : public Tool
{
public:
	UpdatePosTool() = default;
	~UpdatePosTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	/// Algorithme par d�faut
	void defaultUpdatePos(NoeudAbstrait* node);
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
