//////////////////////////////////////////////////////////////////////////////
/// @file InvalidTool.h
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
/// @brief Classe concr�te h�ritant de Tool, qui repositionne les objets
///        � leur position initiale suite � une modification invalide
/// @author INF2990-A15-01
/// @date 2015-09-26
///////////////////////////////////////////////////////////////////////////
class InvalidTool : public Tool
{
public:
	InvalidTool() = default;
	~InvalidTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

protected:
	void defaultInvalid(NoeudAbstrait* node);
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
