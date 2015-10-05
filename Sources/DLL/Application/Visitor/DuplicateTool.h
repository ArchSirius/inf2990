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
class NoeudAbstrait;
#include <vector>
#include <stack>
#include "../../Arbre/ArbreRenduINF2990.h"


///////////////////////////////////////////////////////////////////////////
/// @class DuplicateTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   duplication sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class DuplicateTool : public Tool
{
public:
	DuplicateTool(glm::dvec3 center);
	~DuplicateTool();

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	void defaultDuplicate(NoeudAbstrait* node);

	void duplicate();
	void updateBuffer(glm::dvec3 cursor);
	void confirmBuffer();

private:
	std::stack<NoeudAbstrait*> _domain;
	std::vector<NoeudAbstrait*> _buffer;
	// Centre des objets d'origine
	glm::dvec3 _center;
	// Arbre
	ArbreRenduINF2990* _arbre;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
