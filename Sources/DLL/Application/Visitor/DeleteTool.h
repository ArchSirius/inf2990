//////////////////////////////////////////////////////////////////////////////
/// @file DeleteTool.h
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


///////////////////////////////////////////////////////////////////////////
/// @class DeleteTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   suppression sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class DeleteTool : public Tool
{
public:
	DeleteTool() = default;
	~DeleteTool();

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	void defaultDelete(NoeudAbstrait* node);

private:
	void deleteBuffer();

	std::stack<NoeudAbstrait*> buffer;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
