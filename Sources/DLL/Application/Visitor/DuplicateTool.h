//////////////////////////////////////////////////////////////////////////////
/// @file DuplicateTool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
#include "GL/glew.h"
class NoeudAbstrait;
#include <stack>


///////////////////////////////////////////////////////////////////////////
/// @class DuplicateTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   duplication sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class DuplicateTool : public Tool
{
public:
	DuplicateTool() = default;
	~DuplicateTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

	void defaultDuplicate(NoeudAbstrait* node);

private:
	void duplicate();

	std::stack<NoeudAbstrait*> buffer;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
