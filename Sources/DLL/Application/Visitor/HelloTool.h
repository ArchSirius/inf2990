//////////////////////////////////////////////////////////////////////////////
/// @file HelloTool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Tool.h"
#include <iostream>
class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class HelloTool
/// @brief Classe test
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class HelloTool : public Tool
{
public:
	HelloTool() = default;
	~HelloTool() = default;

	void visit(NoeudCylindre* node) override {/* defaultHello(node); */};
	void visit(NoeudDepart* node) override {/* defaultHello(node); */};
	void visit(NoeudLigne* node) override {/* defaultHello(node); */};
	void visit(NoeudMur* node) override {/* defaultHello(node); */};

protected:

	void defaultHello(NoeudAbstrait* node) { std::cout << node->obtenirType() << std::endl; }
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
