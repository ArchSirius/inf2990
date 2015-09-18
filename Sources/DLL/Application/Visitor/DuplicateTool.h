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
#include "../../Arbre/Noeuds/NoeudAbstrait.h"
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
	~DuplicateTool() = default;

	void visitNoeudCylindre(NoeudCylindre* node) override;
	void visitNoeudDepart(NoeudDepart* node) override;
	void visitNoeudLigne(NoeudLigne* node) override;
	void visitNoeudMur(NoeudMur* node) override;

protected:
	DuplicateTool(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);

	void defaultDuplicate(NoeudAbstrait* node);

private:
	// Coordonn�es relatives du nouvel objet selon l'objet original
	GLfloat _deltaX;
	GLfloat _deltaY;
	GLfloat _deltaZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
