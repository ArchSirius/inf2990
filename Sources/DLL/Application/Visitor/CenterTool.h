//////////////////////////////////////////////////////////////////////////////
/// @file CenterTool.h
/// @author INF2990-A15-01
/// @date 2015-09-25
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


///////////////////////////////////////////////////////////////////////////
/// @class CenterTool
/// @brief Classe concrète héritant de Tool, qui retourne le centre des
///        objets sélectionnés
/// @author INF2990-A15-01
/// @date 2015-09-25
///////////////////////////////////////////////////////////////////////////
class CenterTool : public Tool
{
public:
	CenterTool();
	~CenterTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudSegmentConcret* node) override;
	void visit(NoeudMur* node) override;

	glm::dvec3 getCenter() const;

protected:
	void defaultCenter(NoeudAbstrait* node);

private:
	unsigned int _nbObj;
	glm::dvec3 _sum;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
