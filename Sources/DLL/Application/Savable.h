//////////////////////////////////////////////////////////////////////////////
/// @file Savable.h
/// @author INF2990-A15-01
/// @date 2015-09-28
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <map>
#include <vector>


///////////////////////////////////////////////////////////////////////////
/// @class Savable
/// @brief Classe servant à représenter les attribus d'un entité qui serons
///        sauvegardés
///
/// @author INF2990-A15-01
/// @date 2015-09-28
///////////////////////////////////////////////////////////////////////////
class Savable
{
	std::map<std::string, std::string> attributes;
	std::vector<Savable> children;

public:
	Savable() = default;
	~Savable() = default;
	std::map<std::string, std::string> getData() const { return attributes; }
	std::vector<Savable> getChildren() const { return children; }
	void setAttribute(std::string attr, std::string value) { attributes[attr] = value; }
	void addChild(Savable child) { children.push_back(child); }
	std::string serializeJson() const;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
