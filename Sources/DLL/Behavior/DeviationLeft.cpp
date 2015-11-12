//////////////////////////////////////////////////////////////////////////////
/// @file DeviationLeft.cpp
/// @author Équipe 1
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
/// @fn void DeviationLeft::DeviationLeft(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DeviationLeft::DeviationLeft(BehaviorContext* context) : Behavior(context) 
{
	Debug::getInstance()->printMessage(Debug::COMPORTEMENT_DEBUT, "DEVIATION VERS LA GAUCHE");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->resetWaitTime();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DeviationLeft::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeviationLeft::doAction()
{
	Behavior::doAction();
	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) 
		< context_->getRobot()->getProfile().deviationLeftAngle) // Angle du profil
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->forward();
	}

	else if (!context_->getRobot()->shouldWait())
	{
		Debug::getInstance()->printMessage(Debug::COMPORTEMENT_FIN, "DEVIATION VERS LA GAUCHE");
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().deviationLeftNextState)
			); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////