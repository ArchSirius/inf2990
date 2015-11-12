//////////////////////////////////////////////////////////////////////////////
/// @file AvoidLeft.cpp
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
/// @fn void AvoidLeft::AvoidLeft(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
AvoidLeft::AvoidLeft(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::BALAYAGE, "Comportement actif : EVITEMENT PAR LA GAUCHE");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->setStartTime(time(0));
	context_->getRobot()->resetWaitTime();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AvoidLeft::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AvoidLeft::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->getSpeed() > 0)
	{
		//context_->getRobot()->setStartTime(time(0));
		context_->getRobot()->reverse();
	}

	else if ((difftime(time(0), context_->getRobot()->getStartTime())) * 1000
		< context_->getRobot()->getProfile().avoidLeftTime) // Duree du profil
	{
		context_->getRobot()->reverse();
	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) 
		< context_->getRobot()->getProfile().avoidLeftAngle) // Angle du profil
	{
		context_->getRobot()->turnLeft();
	}

	else if (!context_->getRobot()->shouldWait())
	{
		context_->getRobot()->setSpeed(0.0f);
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().avoidLeftNextState)
			); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

