//////////////////////////////////////////////////////////////////////////////
/// @file SelectBrothersTool.h
/// @author INF2990-A15-01
/// @date 2015-10-07
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class SelectBrothersTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue une s�lection
///        des noeuds fr�res d'un noeud
/// @author INF2990-A15-01
/// @date 2015-10-07
///////////////////////////////////////////////////////////////////////////
class SelectBrothersTool : public Tool
{
public:
	SelectBrothersTool(NoeudAbstrait* parent, bool selectionne);
	~SelectBrothersTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	/// Algorithme par d�faut
	void defaultSelect(NoeudAbstrait* node);

private:
	NoeudAbstrait* _parent;
	bool _selectionne;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
