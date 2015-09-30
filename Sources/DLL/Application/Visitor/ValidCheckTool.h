//////////////////////////////////////////////////////////////////////////////
/// @file ValidCheckTool.h
/// @author INF2990-A15-01
/// @date 2015-09-26
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tool.h"
#include "GL/glew.h"
class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class TranslateTool
/// @brief Classe concr�te h�ritant de Tool, qui v�rifie la validit� de la
///        position des objets s�lectionn�s suite � une modification
/// @author INF2990-A15-01
/// @date 2015-09-26
///////////////////////////////////////////////////////////////////////////
class ValidCheckTool : public Tool
{
public:
	ValidCheckTool();
	~ValidCheckTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

	bool isValid() const;

protected:
	void defaultValidCheck(NoeudAbstrait* node);

private:
	bool _valid;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
