///////////////////////////////////////////////////////////////////////////////
/// @file Savable.cpp
/// @author INF2990-A15-01
/// @date 2015-09-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Savable.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string Savable::serializeJson() const
///
/// Cette fonction sert à sérializer la structure de donnée "Savable"
/// en JSON
///
/// @return std::string.
///
////////////////////////////////////////////////////////////////////////
std::string Savable::serializeJson() const
{
	std::string endl = "\n";
	std::string comma = ",";
	std::string nodeStr = "";

	for (auto attribute : attributes) {
		nodeStr += endl + "\"" + attribute.first + "\": \"" + attribute.second + "\"" + comma;
	}

	// remove last comma
	nodeStr.pop_back();

	if (children.size() > 0) {
		nodeStr += "," + endl + "\"children\": [";
		for (auto child : children)
		{
			nodeStr += endl + child.serializeJson() + comma;
		}

		// remove last comma
		nodeStr.pop_back();

		nodeStr += "]";
	}

	return "{" + nodeStr + endl + "}";
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
