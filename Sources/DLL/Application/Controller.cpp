///////////////////////////////////////////////////////////////////////////////
/// @file Controller.cpp
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Controller.h"

#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "State/ToolState.h"
#include "State/SelectState.h"
#include "VueOrtho.h"

/// Pointeur vers l'instance unique de la classe.
Controller* Controller::_instance = nullptr;

////////////////////////////////////////////////////////////////////////
///
/// @fn Controller::Controller()
///
/// Constructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Controller::Controller()
{
	// State par défaut?
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Controller::~Controller()
///
/// Destructeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Controller::~Controller()
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn Controller* Controller::getInstance()
///
/// Retourne un pointeur vers l'instance unique de la classe singleton.
/// Si une instance n'existe pas déjà, elle sera créée puis retournée.
///
/// @return Pointeur vers l'instance unique de la classe singleton.
///
////////////////////////////////////////////////////////////////////////
Controller* Controller::getInstance()
{
	if (_instance == nullptr)
		_instance = new Controller;
	return _instance;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Controller::resetInstance()
///
/// Supprime l'instance unique de la classe
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Controller::resetInstance()
{
	delete _instance;
	_instance = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Controller::changeState()
///
/// Change l'état du controller.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Controller::changeState(ToolState* state)
{
	_state->changeState(std::unique_ptr<Controller>(this), state);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Controller::animer()
///
/// Remplace l'ancienne fonction animer() de FacadeModele (pour tests).
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Controller::animer(float temps)
{
	// Ne depend pas de l'état
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->animer(temps);
	FacadeModele::obtenirInstance()->obtenirVue()->animer(temps);
}
