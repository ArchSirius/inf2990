//////////////////////////////////////////////////////////////////////////////
/// @file DefaultBehavior.cpp
/// @author �quipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////


#include "BehaviorList.h"
#include "../Arbre/Noeuds/NoeudRobot.h"
#include "Debug.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void DefaultBehavior::DefaultBehavior(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DefaultBehavior::DefaultBehavior(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::COMPORTEMENT_DEBUT, "PAR DEFAUT");
	context_->getRobot()->setShouldFollow(true);
	context_->getRobot()->resetWaitTime();
	context_->getRobot()->pauseSon(7, true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DefaultBehavior::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DefaultBehavior::doAction()
{
	Behavior::doAction();

	context_->getRobot()->forward(); 
	// Aucun prochain �tat naturel ; n'est chang� que par un capteur
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////