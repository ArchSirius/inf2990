//////////////////////////////////////////////////////////////////////////////
/// @file ScaleTool.h
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

///////////////////////////////////////////////////////////////////////////
/// @class ScaleTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   mise à l'échelle sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class ScaleTool : public Tool
{
public:
	ScaleTool(int x, int y, int z);
	~ScaleTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

protected:
	void defaultScale(NoeudAbstrait* node);

private:
	// Facteur de grossissement (pas clair encore)
	int _factorX;
	int _factorY;
	int _factorZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
