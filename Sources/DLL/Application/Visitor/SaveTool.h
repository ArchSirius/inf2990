//////////////////////////////////////////////////////////////////////////////
/// @file SaveTool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <vector>
#include "Tool.h"
#include "GL/glew.h"
class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class SaveTool
/// @brief Classe concrète héritant de Tool, qui effectue l'opération de
///		   sauvegarde sur l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class SaveTool : public Tool
{
public:
	SaveTool() = default;
	~SaveTool() = default;

	void visit(NoeudCylindre* node) override;
	void visit(NoeudDepart* node) override;
	void visit(NoeudLigne* node) override;
	void visit(NoeudMur* node) override;
	std::vector<std::string> getData();

protected:
	void defaultSave(NoeudAbstrait* node);

private:
	std::vector<std::string> data;

};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
