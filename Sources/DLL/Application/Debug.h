//////////////////////////////////////////////////////////////////////////////
/// @file Debug.h
/// @author INF2990-A15-01
/// @date 2015-09-09
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <memory>


///////////////////////////////////////////////////////////////////////////
/// @class Debug
/// @brief Classe gérant l'affichage d'informations à la console et les
///        informations de déboguage à afficher ou non.
///
/// @author INF2990-A15-01
/// @date 2015-09-09
///////////////////////////////////////////////////////////////////////////
class Debug
{
public:
	/// Obtient l'instance unique de la classe.
	static Debug* getInstance();
	/// Libère l'instance unique de la classe.
	static void resetInstance();

	/// Déclencheurs possibles pour les messages et activation de debug
	static const enum Declencheur {
		CONSOLE,
		TEST,
		CAPTEUR_GAUCHE_SAFE,
		CAPTEUR_GAUCHE_DANGER,
		CAPTEUR_CENTRE_SAFE,
		CAPTEUR_CENTRE_DANGER,
		CAPTEUR_DROIT_SAFE,
		CAPTEUR_DROIT_DANGER,
		BALAYAGE,
		LUM_AMBIANTE,
		LUM_DIRECTIONNELLE,
		LUM_SPOT,
		COLLISION
	};

	/// Affiche un message à la console
	void printMessage(Declencheur declencheur, std::string message);
	/// Affiche une erreur à la console
	void printError(Declencheur declencheur, std::string message);

	/// Retourne le temps actuel sous le format HH:MM:SS:mmm
	std::string getCurrentTime_precise() const;
	/// Retourne le temps actuel sous le format AAAA-MM-JJ-hhmm
	std::string getCurrentTime_generic() const;

	/// Active la sortie journal
	void enableLog();
	/// Désactive la sortie journal
	void disableLog();
	/// Assigne la sortie journal
	void setLog(bool enabled);
	/// Retourne l'état d'utilsation du journal
	bool isLogEnabled() const;

	/// Active les informations de déboguage d'un déclencheur
	void enableType(Declencheur declencheur);
	/// Désactive les informations de déboguage d'un déclencheur
	void disableType(Declencheur declencheur);
	/// Assigne l'activation des informations de déboguage d'un déclencheur
	void setType(Declencheur declencheur, bool enabled);
	/// Retourne l'état d'activation d'un déclencheur
	bool isEnabled(Declencheur declencheur);


private:
	/// Constructeur par défaut.
	Debug();
	/// Destructeur.
	~Debug();
	friend std::unique_ptr<Debug>::deleter_type;
	/// Constructeur copie désactivé.
	Debug(const Debug&) = delete;
	/// Opérateur d'assignation désactivé.
	Debug& operator=(const Debug&) = delete;

	/// Initialise les maps des déclencheurs
	void initialiseDeclencheur(Declencheur declencheur, 
		std::string nom, bool etat);

	/// Inscrit un événement au journal
	void appendLog(std::string message);

	/// Pointeur vers l'instance unique de la classe.
	static std::unique_ptr<Debug> _instance;

	/// Map contenant les déclencheurs de messages (classes/événements) et
	/// leur état
	std::map<Declencheur, bool> _active;

	/// Map de description des déclencheurs
	std::map<Declencheur, std::string> _declencheur;

	/// Fichier journal
	std::ofstream _log;
	bool _outputLog;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
