//////////////////////////////////////////////////////////////////////////////
/// @file SelectTool.h
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
/// @class SelectTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue une v�rification
///        des noeuds s�lectionn�s comme le compte
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class SelectTool : public Tool
{
public:
	SelectTool();
	~SelectTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	/// Algorithme par d�faut
	void defaultSelect(NoeudAbstrait* node);

	/// Dis combien de noeud sont s�lectionn�s
	int getNbSelected() const;

private:
	int _nbSelected;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
