//////////////////////////////////////////////////////////////////////////////
/// @file FL_SteadyFwd.cpp
/// @author Équipe 1
/// @date 2015-10-30
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
/// @fn void FL_SteadyFwd::FL_SteadyFwd(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
FL_SteadyFwd::FL_SteadyFwd(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::TEST, "Comportement actif : FL_STEADYFWD");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->setStartTime(time(0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FL_SteadyFwd::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FL_SteadyFwd::doAction()
{
	/*
	if ((context_->getRobot()->isNearLeftDetected() || context_->getRobot()->isFarLeftDetected()) && !context_->getRobot()->isCenterDetected())
	{
		context_->changeBehavior(std::make_unique<FollowLine>(context_)); // Prochain état selon le profil
	}
	else if ((context_->getRobot()->isNearRightDetected() || context_->getRobot()->isFarRightDetected()) && !context_->getRobot()->isCenterDetected())
	{
		context_->changeBehavior(std::make_unique<FollowLine>(context_)); // Prochain état selon le profil
	}*/

	if (difftime(time(0), context_->getRobot()->getStartTime()) < 1)
		context_->getRobot()->forward();
	else
		context_->changeBehavior(std::make_unique<MiniSearch>(context_)); // Prochain état (hardcoded)
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////