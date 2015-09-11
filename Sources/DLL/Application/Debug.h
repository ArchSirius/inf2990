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
/// @brief Classe g�rant l'affichage d'informations � la console et les
///        informations de d�boguage � afficher ou non.
///
/// @author INF2990-A15-01
/// @date 2015-09-09
///////////////////////////////////////////////////////////////////////////
class Debug
{
public:
	/// Obtient l'instance unique de la classe.
	static Debug* getInstance();
	/// Lib�re l'instance unique de la classe.
	static void resetInstance();

	/// D�clencheurs possibles pour les messages et activation de debug
	static enum Declencheur {CONSOLE} const;

	/// Affiche un message � la console
	void printMessage(Declencheur declencheur, std::string message) const;
	/// Affiche une erreur � la console
	void printError(Declencheur declencheur, std::string message) const;

	/// Retourne le temps actuel sous le format HH:MM:SS:mmm
	std::string getCurrentTime() const;

	/// Active les informations de d�boguage d'un d�clencheur
	void enableType(Declencheur declencheur);
	/// D�sactive les informations de d�boguage d'un d�clencheur
	void disableType(Declencheur declencheur);
	/// Retourne l'�tat d'activation d'un d�clencheur
	bool isEnabled(Declencheur declencheur) const;


private:
	/// Constructeur par d�faut.
	Debug();
	/// Destructeur.
	~Debug();
	/// Constructeur copie d�sactiv�.
	Debug(const Debug&) = delete;
	/// Op�rateur d'assignation d�sactiv�.
	Debug& operator=(const Debug&) = delete;

	/// Initialise les maps des d�clencheurs
	void initialiseDeclencheur(Declencheur declencheur, 
		std::string nom, bool etat);

	/// Pointeur vers l'instance unique de la classe.
	static Debug* _instance;

	/// Map contenant les d�clencheurs de messages (classes/�v�nements) et
	/// leur �tat
	std::map<Declencheur, bool> _active;

	/// Map de description des d�clencheurs
	std::map<Declencheur, std::string> _declencheur;
};

#endif // __DEBUG_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
