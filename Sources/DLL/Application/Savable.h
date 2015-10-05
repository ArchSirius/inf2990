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
/// @brief Classe servant � repr�senter les attribus d'un entit� qui serons
///        sauvegard�s
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

	/// Retourne les donn�es � sauvegarder
	std::map<std::string, std::string> getData() const { return attributes; }
	/// Assigne la valeur d'un attribut sauvgardable
	void setAttribute(std::string attr, std::string value) { attributes[attr] = value; }
	/// Ajout en noeud enfant
	void addChild(Savable child) { children.push_back(child); }
	/// Retourne les noeuds enfants
	std::vector<Savable> getChildren() const { return children; }
	/// Retourne les attributs et les enfants s�rializ�s en JSON
	std::string serializeJson() const;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
