//////////////////////////////////////////////////////////////////////////////
/// @file AvoidRight.cpp
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
/// @fn void AvoidRight::AvoidRight(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
AvoidRight::AvoidRight(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::COMPORTEMENT_DEBUT, "EVITEMENT VERS LA DROITE");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->setStartTime(time(0));
	context_->getRobot()->resetWaitTime();
	context_->getRobot()->pauseSon(7, true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AvoidLeft::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AvoidRight::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->getSpeed() > 0)
	{
		//context_->getRobot()->setStartTime(time(0));
		context_->getRobot()->reverse();
		context_->getRobot()->pauseSon(8, true);
	}

	else if ((difftime(time(0), context_->getRobot()->getStartTime()))*1000 
		< context_->getRobot()->getProfile().avoidRightTime) //Duree du profil
	{
		context_->getRobot()->reverse();
		context_->getRobot()->pauseSon(8, true);
	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) 
		< context_->getRobot()->getProfile().avoidRightAngle) // Angle du profil
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->pauseSon(8, false);
	}

	else if (!context_->getRobot()->shouldWait())
	{
		context_->getRobot()->pauseSon(8, true);
		Debug::getInstance()->printMessage(Debug::COMPORTEMENT_FIN, "EVITEMENT VERS LA DROITE");
		context_->getRobot()->setSpeed(0.0f);
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().avoidRightNextState)
			); // Prochain �tat selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////