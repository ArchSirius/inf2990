//////////////////////////////////////////////////////////////////////////////
/// @file Debug.h
/// @author INF2990-A15-01
/// @date 2015-09-09
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>
#include <map>


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
	static enum Declencheur {CONSOLE} const;

	/// Affiche un message à la console
	void printMessage(Declencheur declencheur, std::string message) const;
	/// Affiche une erreur à la console
	void printError(Declencheur declencheur, std::string message) const;

	/// Retourne le temps actuel sous le format HH:MM:SS:mmm
	std::string getCurrentTime() const;

	/// Active les informations de déboguage d'un déclencheur
	void enableType(Declencheur declencheur);
	/// Désactive les informations de déboguage d'un déclencheur
	void disableType(Declencheur declencheur);
	/// Retourne l'état d'activation d'un déclencheur
	bool isEnabled(Declencheur declencheur) const;


private:
	/// Constructeur par défaut.
	Debug();
	/// Destructeur.
	~Debug();
	/// Constructeur copie désactivé.
	Debug(const Debug&) = delete;
	/// Opérateur d'assignation désactivé.
	Debug& operator=(const Debug&) = delete;

	/// Initialise les maps des déclencheurs
	void initialiseDeclencheur(Declencheur declencheur, 
		std::string nom, bool etat);

	/// Pointeur vers l'instance unique de la classe.
	static Debug* _instance;

	/// Map contenant les déclencheurs de messages (classes/événements) et
	/// leur état
	std::map<Declencheur, bool> _active;

	/// Map de description des déclencheurs
	std::map<Declencheur, std::string> _declencheur;
};

#endif // __DEBUG_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
