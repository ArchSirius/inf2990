///////////////////////////////////////////////////////////////////////////////
/// @file ScaleTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "SaveTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "glm/ext.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SaveTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Save pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SaveTool::visit(NoeudCylindre* node)
{
	defaultSave(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SaveTool::visit(NoeudDepart* node)
///
/// Implémentation du visiteur Save pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SaveTool::visit(NoeudDepart* node)
{
	defaultSave(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SaveTool::visit(NoeudLigne* node)
///
/// Implémentation du visiteur Save pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SaveTool::visit(NoeudLigne* node)
{
	defaultSave(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SaveTool::visit(visitNoeudMur* node)
///
/// Implémentation du visiteur Save pour un noeud de type
/// visitNoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SaveTool::visit(NoeudMur* node)
{
	defaultSave(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void SaveTool::defaultSave(NoeudAbstrait* node)
///
/// Implémentation du visiteur Save par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SaveTool::defaultSave(NoeudAbstrait* node)
{
	if (!node->estEnregistrable())
		return;

	std::string comma = ",";
	std::string nodeStr = "";
	//nodeStr += "\"id\":" + ((int)node) + comma;
	nodeStr += "\"position_x\":" + glm::to_string(node->obtenirPositionRelative().x) + comma;
	nodeStr += "\"position_y\":" + glm::to_string(node->obtenirPositionRelative().y) + comma;
	nodeStr += "\"position_z\":" + glm::to_string(node->obtenirPositionRelative().z) + comma;
	//nodeStr += "\"parent\":" + ((int)node->obtenirParent()) + comma;

	data.push_back("{" + nodeStr + "}");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual std::shared_ptr<std::vector<std::string>> SaveTool::getData()
///
/// Accesseur de data
///
/// @return std::shared_ptr<std::vector<std::string>>.
///
////////////////////////////////////////////////////////////////////////
std::vector<std::string> SaveTool::getData()
{
	return data;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
