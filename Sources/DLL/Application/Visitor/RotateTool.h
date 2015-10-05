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
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   rotation sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class RotateTool : public Tool
{
public:
	RotateTool(GLfloat centerX, GLfloat centerY, GLfloat centerZ,
		GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ);
	~RotateTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

protected:
	void defaultRotate2d(NoeudAbstrait* node);

private:
	// Conversions d'angles
	float degrees2radians(const float degrees) const;
	float radians2degrees(const float radians) const;
	void makeValidAngle(float& angle) const;

	// Centre de rotation
	GLfloat _centerX;
	GLfloat _centerY;
	GLfloat _centerZ;
	// Vecteur souris
	GLfloat _deltaX;
	GLfloat _deltaY;
	GLfloat _deltaZ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
