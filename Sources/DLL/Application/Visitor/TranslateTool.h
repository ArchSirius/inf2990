//////////////////////////////////////////////////////////////////////////////
/// @file TranslateTool.h
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
/// @class TranslateTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   translation sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class TranslateTool : public Tool
{
public:
	TranslateTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ);
	~TranslateTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

protected:
	void defaultTranslate(NoeudAbstrait* node);

private:
	GLfloat _deltaX;
	GLfloat _deltaY;
	GLfloat _deltaZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
