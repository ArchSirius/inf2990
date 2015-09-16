//////////////////////////////////////////////////////////////////////////////
/// @file DuplicateTool.h
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

///////////////////////////////////////////////////////////////////////////
/// @class DuplicateTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration de
///		   duplication sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class DuplicateTool : public Tool
{
public:
	DuplicateTool(GLfloat x, GLfloat y, GLfloat z);
	virtual void visit(NoeudAbstrait* node);
private:
	// Coordonn�es du nouvel objet
	GLfloat _x;
	GLfloat _y;
	GLfloat _z;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
