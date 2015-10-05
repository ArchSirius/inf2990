//////////////////////////////////////////////////////////////////////////////
/// @file GetDataTool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
class NoeudAbstrait;
#include <stack>
#include "../../Interface/NodeProperties.h"


///////////////////////////////////////////////////////////////////////////
/// @class GetDataTool
/// @brief Classe concrète héritant de Tool, qui prend les données
///	du noeud sélectionné
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class GetDataTool : public Tool
{
public:
	GetDataTool(NodeProperties* data) : data_(data) {}
	~GetDataTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	/// Algorithme par défaut
	void defaultGetter(NoeudAbstrait* node);

private:
	NodeProperties* data_;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
