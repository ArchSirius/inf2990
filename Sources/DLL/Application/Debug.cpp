///////////////////////////////////////////////////////////////////////////////
/// @file Debug.cpp
/// @author INF2990-A15-01
/// @date 2015-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Debug.h"
#include <iostream>
#include <sstream>
#include <windows.h>

/// Pointeur vers l'instance unique de la classe.
Debug* Debug::_instance = nullptr;


////////////////////////////////////////////////////////////////////////
///
/// @fn Debug::Debug()
///
/// Constructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Debug::Debug()
{
	initialiseDeclencheur(CONSOLE, "Console", true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Debug::~Debug()
///
/// Destructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Debug::~Debug()
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn Debug* Debug::getInstance()
///
/// Retourne un pointeur vers l'instance unique de la classe singleton.
/// Si une instance n'existe pas déjà, elle sera créée puis retournée.
///
/// @return Pointeur vers l'instance unique de la classe singleton.
///
////////////////////////////////////////////////////////////////////////
Debug* Debug::getInstance()
{
	if (_instance == nullptr)
		_instance = new Debug;
	return _instance;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::resetInstance()
///
/// Supprime l'instance unique de la classe
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::resetInstance()
{
	delete _instance;
	_instance = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::initialiseDeclencheur(Declencheur declencheur,
///     std::string nom, bool etat)
///
/// Initialise les maps des déclencheurs
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::initialiseDeclencheur(Declencheur declencheur,
	std::string nom, bool etat)
{
	_active[declencheur] = etat;
	_declencheur[declencheur] = nom;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::printMessage(Declencheur declencheur,
///     std::string message) const
///
/// Affiche un message à la console sous le format
/// HH:MM:SS:mmm – nom du déclencheur - nom du nouveau comportement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::printMessage(Declencheur declencheur, std::string message) const
{
	try
	{
		if (_active.at(declencheur))
			std::cout << getCurrentTime() << " - "
			<< _declencheur.at(declencheur) << " - " << message
			<< std::endl;
	}
	// Puisque declencheur est un enum, aucune exception
	// OOR ne devrait survenir
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range& oor)
	{
		printError(CONSOLE, oor.what());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::printError(Declencheur declencheur,
///     std::string message) const
///
/// Affiche un message d'erreur à la console sous le format
/// HH:MM:SS:mmm – nom du déclencheur - nom du nouveau comportement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::printError(Declencheur declencheur, std::string message) const
{
	try
	{
		if (_active.at(declencheur))
			std::cerr << getCurrentTime() << " - "
			<< _declencheur.at(declencheur) << " - " << message
			<< std::endl;
	}
	// Puisque declencheur est un enum, aucune exception
	// OOR ne devrait survenir
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range& oor) {
		printError(CONSOLE, oor.what());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string Debug::getCurrentTime() const
///
/// Retourne le temps actuel sous le format HH:MM:SS:mmm
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::string Debug::getCurrentTime() const
{
	// Tiré de https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx
	SYSTEMTIME currentTime;
	// Tiré de https://msdn.microsoft.com/en-us/library/windows/desktop/ms724338(v=vs.85).aspx
	GetLocalTime(&currentTime);

	WORD hour = currentTime.wHour;
	WORD minute = currentTime.wMinute;
	WORD second = currentTime.wSecond;
	WORD milliseconds = currentTime.wMilliseconds;
	std::string output = "";
	// Tiré de http://www.cplusplus.com/reference/sstream/ostringstream/
	std::ostringstream convert;

	// Tiré de http://www.cplusplus.com/reference/ios/ios/fill/
	convert.fill('0');

	// Tiré de http://www.cplusplus.com/reference/ios/ios_base/width/
	convert.width(2);
	convert << hour;
	output += convert.str();
	output += ":";
	convert.str("");

	convert.width(2);
	convert << minute;
	output += convert.str();
	output += ":";
	convert.str("");

	convert.width(2);
	convert << second;
	output += convert.str();
	output += ":";
	convert.str("");

	convert.width(3);
	convert << milliseconds;
	output += convert.str();

	return output;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::enableType(Declencheur declencheur)
///
/// Active les informations de déboguage d'un déclencheur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::enableType(Declencheur declencheur)
{
	try
	{
		_active.at(declencheur) = true;
	}
	// Puisque declencheur est un enum, aucune exception
	// OOR ne devrait survenir
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range& oor)
	{
		printError(CONSOLE, oor.what());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::disableType(Declencheur declencheur)
///
/// Désactive les informations de déboguage d'un déclencheur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::disableType(Declencheur declencheur)
{
	try
	{
		_active.at(declencheur) = false;
	}
	// Puisque declencheur est un enum, aucune exception
	// OOR ne devrait survenir
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range& oor)
	{
		printError(CONSOLE, oor.what());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::isEnabled(Declencheur declencheur) const
///
/// Retourne l'état d'activation d'un déclencheur
///
/// @return true si le déclencheur est activé; false sinon
///
////////////////////////////////////////////////////////////////////////
bool Debug::isEnabled(Declencheur declencheur) const
{
	try
	{
		return _active.at(declencheur);
	}
	// Puisque declencheur est un enum, aucune exception
	// OOR ne devrait survenir
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range& oor)
	{
		printError(CONSOLE, oor.what());
	}

	return false;
}
