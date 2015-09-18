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
#include "../../Arbre/Noeuds/NoeudAbstrait.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class HelloTool
/// @brief Classe test
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class HelloTool : public Tool
{
public:
	~HelloTool() = default;

	void visitNoeudCylindre(NoeudCylindre* node) override { defaultHello(node); };
	void visitNoeudDepart(NoeudDepart* node) override { defaultHello(node); };
	void visitNoeudLigne(NoeudLigne* node) override { defaultHello(node); };
	void visitNoeudMur(NoeudMur* node) override { defaultHello(node); };

protected:
	HelloTool() = default;

	void defaultHello(NoeudAbstrait* node) { std::cout << node->obtenirType() << std::endl; }
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
