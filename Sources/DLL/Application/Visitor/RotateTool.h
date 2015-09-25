//////////////////////////////////////////////////////////////////////////////
/// @file RotateTool.h
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
/// @class RotateTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration de
///		   rotation sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class RotateTool : public Tool
{
public:
	RotateTool(/* Axe/centre de rotation, Angle */);
	~RotateTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;

protected:
	void defaultRotate(NoeudAbstrait* node);

private:
	// Centre de rotation
	GLfloat _centreX;
	GLfloat _centreY;
	GLfloat _centreZ;
	// Vecteur souris
	GLfloat _deltaX;
	GLfloat _deltaY;
	GLfloat _deltaZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
