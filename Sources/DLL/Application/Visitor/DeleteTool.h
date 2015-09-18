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
#include "../../Arbre/Noeuds/NoeudAbstrait.h"


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
	~DeleteTool() = default ;

	void visitNoeudCylindre(NoeudCylindre* node) override;
	void visitNoeudDepart(NoeudDepart* node) override;
	void visitNoeudLigne(NoeudLigne* node) override;
	void visitNoeudMur(NoeudMur* node) override;

protected:
	DeleteTool() = default;

	void defaultDelete(NoeudAbstrait* node);
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
