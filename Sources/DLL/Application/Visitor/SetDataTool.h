//////////////////////////////////////////////////////////////////////////////
/// @file SetDataTool.h
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
/// @class SetDataTool
/// @brief Classe concr�te h�ritant de Tool, qui prend les donn�es
///	du noeud s�lectionn�
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class SetDataTool : public Tool
{
public:
	SetDataTool(NodeProperties* data) : data_(data) {}
	~SetDataTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

	void defaultSetter(NoeudAbstrait* node);

private:
	NodeProperties* data_;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
