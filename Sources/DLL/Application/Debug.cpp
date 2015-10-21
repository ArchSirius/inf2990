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

std::unique_ptr<Debug> Debug::_instance;

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
	: _outputLog(true)
{
	initialiseDeclencheur(CONSOLE, "Console", true);
	initialiseDeclencheur(TEST, "Test", true);
	initialiseDeclencheur(CAPTEUR_GAUCHE_SAFE, "Capteur de distance gauche, zone sécuritaire", true);
	initialiseDeclencheur(CAPTEUR_GAUCHE_DANGER, "Capteur de distance gauche, zone de danger", true);
	initialiseDeclencheur(CAPTEUR_CENTRE_SAFE, "Capteur de distance centre, zone sécuritaire", true);
	initialiseDeclencheur(CAPTEUR_CENTRE_DANGER, "Capteur de distance centre, zone de danger", true);
	initialiseDeclencheur(CAPTEUR_DROIT_SAFE, "Capteur de distance droit, zone sécuritaire", true);
	initialiseDeclencheur(CAPTEUR_DROIT_DANGER, "Capteur de distance droit, zone de danger", true);
	initialiseDeclencheur(BALAYAGE, "Balayage", true);
	initialiseDeclencheur(LUM_AMBIANTE, "Lumiere ambiante", true);
	initialiseDeclencheur(LUM_DIRECTIONNELLE, "Lumiere directionnelle", true);
	initialiseDeclencheur(LUM_SPOT, "Lumiere spot", true);
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
{
	if (_log.is_open())
		_log.close();
}

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
	if (!_instance)
		_instance = std::unique_ptr<Debug>(new Debug);
	return _instance.get();
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
	_instance.reset();
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
/// @fn void Debug::appendLog(Declencheur declencheur, std::string message)
///
/// Inscrit un événement au journal
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::appendLog(std::string message)
{
	if (_outputLog)
	{
		if (!_log.is_open())
		{
			// Obtention du répertoire tirée de https://msdn.microsoft.com/en-us/library/windows/desktop/aa364934(v=vs.85).aspx
			// Converson du WCHAR tirée de http://www.cplusplus.com/forum/general/39766/
			// et de https://msdn.microsoft.com/en-ca/library/windows/desktop/dd374130(v=vs.85).aspx

			TCHAR buffer[MAX_PATH];
			char path[MAX_PATH];
			// Obtenir le répertoire courant de l'exécutable
			GetCurrentDirectory(MAX_PATH, buffer);
			// et le convertir en format utilisble
			WideCharToMultiByte(CP_ACP, 0, buffer, -1, path, MAX_PATH, NULL, NULL);

			// Enregistrement dans logs sous la racine du projet, pas dans Exe
			_log.open(static_cast<std::string>(path) + "\\..\\logs\\" + getCurrentTime_generic() + ".log");
		}
		_log << message << std::endl;
	}
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
void Debug::printMessage(Declencheur declencheur, std::string message)
{
	try
	{
		if (_active.at(declencheur))
		{
			std::cout << getCurrentTime_precise() << " - "
				<< _declencheur.at(declencheur) << " - " << message
				<< std::endl;
			appendLog(getCurrentTime_precise() + " - "
				+ _declencheur.at(declencheur) + " - " + message);
		}
	}
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&)
	{
		printError(CONSOLE, "Erreur: declencheur non initialise");
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
void Debug::printError(Declencheur declencheur, std::string message)
{
	try
	{
		if (_active.at(declencheur))
			std::cerr << getCurrentTime_precise() << " - "
			<< _declencheur.at(declencheur) << " - " << message
			<< std::endl;
	}
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&) {
		printError(CONSOLE, "Erreur: declencheur non initialise");
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string Debug::getCurrentTime_precise() const
///
/// Retourne le temps actuel sous le format HH:MM:SS:mmm
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::string Debug::getCurrentTime_precise() const
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
/// @fn std::string Debug::getCurrentTime_generic() const
///
/// Retourne le temps actuel sous le format AAAA-MM-JJ-hhmm
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::string Debug::getCurrentTime_generic() const
{
	// Tiré de https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx
	SYSTEMTIME currentTime;
	// Tiré de https://msdn.microsoft.com/en-us/library/windows/desktop/ms724338(v=vs.85).aspx
	GetLocalTime(&currentTime);

	WORD year = currentTime.wYear;
	WORD month = currentTime.wMonth;
	WORD day = currentTime.wDay;
	WORD hour = currentTime.wHour;
	WORD minute = currentTime.wMinute;
	std::string output = "";
	// Tiré de http://www.cplusplus.com/reference/sstream/ostringstream/
	std::ostringstream convert;

	// Tiré de http://www.cplusplus.com/reference/ios/ios/fill/
	convert.fill('0');

	// Tiré de http://www.cplusplus.com/reference/ios/ios_base/width/
	convert << year;
	output += convert.str();
	output += "-";
	convert.str("");
	
	convert.width(2);
	convert << month;
	output += convert.str();
	output += "-";
	convert.str("");

	convert.width(2);
	convert << day;
	output += convert.str();
	output += "-";
	convert.str("");

	convert.width(2);
	convert << hour;
	output += convert.str();
	convert.str("");

	convert.width(2);
	convert << minute;
	output += convert.str();

	return output;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::enableLog()
///
/// Active la sortie journal
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::enableLog()
{
	_outputLog = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::disableLog()
///
/// Désactive la sortie journal
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::disableLog()
{
	_outputLog = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::setLog(bool enabled)
///
/// Assigne la sortie journal
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::setLog(bool enabled)
{
	_outputLog = enabled;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::isLogEnabled() const
///
/// Retourne l'état d'utilsation du journal
///
/// @return true si la sortie journal est activée; false sinon
///
////////////////////////////////////////////////////////////////////////
bool Debug::isLogEnabled() const
{
	return _outputLog;
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
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&)
	{
		printError(CONSOLE, "Erreur: declencheur non initialise");
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
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&)
	{
		printError(CONSOLE, "Erreur: declencheur non initialise");
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::setType(Declencheur declencheur, bool enabled)
///
/// Assigne l'activation des informations de déboguage d'un déclencheur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::setType(Declencheur declencheur, bool enabled)
{
	try
	{
		_active.at(declencheur) = enabled;
	}
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&)
	{
		printError(CONSOLE, "Erreur: declencheur non initialise");
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
bool Debug::isEnabled(Declencheur declencheur)
{
	try
	{
		return _active.at(declencheur);
	}
	// Tiré de http://www.cplusplus.com/reference/map/map/at/
	catch (const std::out_of_range&)
	{
		printError(CONSOLE, "Erreur: declencheur non initialise");
	}

	return false;
}
