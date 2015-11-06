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
#include "glm\glm.hpp"
class NoeudAbstrait;
class NoeudRobot;


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

	static void rotate(glm::dvec3& point, double angle, const glm::dvec3& center);
	static double length(glm::dvec3 vect);

private:
	void doCollision(double angle);

	// Robot
	NoeudRobot* _robot;

	struct segment
	{
		glm::dvec3 p1;
		glm::dvec3 p2;
		glm::dvec3 vect;
		glm::dvec3 norm;

		segment(){};
		segment(const glm::dvec3& _p1, const glm::dvec3& _p2, const glm::dvec3& _vect, const glm::dvec3& _norm)
			: p1(_p1), p2(_p2), vect(_vect), norm(_norm) {};
	};

	segment segments[4];
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
