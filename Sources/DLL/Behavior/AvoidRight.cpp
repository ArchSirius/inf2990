//////////////////////////////////////////////////////////////////////////////
/// @file AvoidRight.cpp
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
/// @fn void AvoidRight::AvoidRight(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
AvoidRight::AvoidRight(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::BALAYAGE, "Comportement actif : EVITEMENT PAR LA DROITE");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->setStartTime(time(0));
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
void AvoidRight::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->getSpeed() > 0)
	{
		//context_->getRobot()->setStartTime(time(0));
		context_->getRobot()->reverse();
	}

	else if ((difftime(time(0), context_->getRobot()->getStartTime()))*1000 
		< context_->getRobot()->getProfile().avoidRightTime) //Duree du profil
	{
		context_->getRobot()->reverse();
	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) 
		< context_->getRobot()->getProfile().avoidRightAngle) // Angle du profil
	{
		context_->getRobot()->turnRight();
	}

	else
	{
		context_->getRobot()->setSpeed(0.0f);
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().avoidRightNextState)
			); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////