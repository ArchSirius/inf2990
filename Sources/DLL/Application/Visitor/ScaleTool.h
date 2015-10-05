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
#include "GL/glew.h"
class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class ScaleTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration de
///		   mise � l'�chelle sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class ScaleTool : public Tool
{
public:
	ScaleTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ);
	~ScaleTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

private:
	GLfloat _deltaX;
	GLfloat _deltaY;
	GLfloat _deltaZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
