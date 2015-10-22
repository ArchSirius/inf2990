//////////////////////////////////////////////////////////////////////////////
/// @file CollisionTool.h
/// @author INF2990-A15-01
/// @date 2015-10-21
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
/// @class CollisionTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération
///		   d'enregistrement de l'angle sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-10-21
///////////////////////////////////////////////////////////////////////////
class CollisionTool : public Tool
{
public:
	CollisionTool(NoeudRobot* robot);
	~CollisionTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override {}
	void visit(NoeudSegmentConcret* node) override {}
	void visit(NoeudMur* node) override;

private:
	void doCollision(float angle);

	// Robot
	NoeudRobot* _robot;
	// Points
	glm::dvec3 _p1, _p2, _p3, _p4;
	// Droites
	glm::dvec3 _d1, _d2;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
