//////////////////////////////////////////////////////////////////////////////
/// @file FL_SteadyRight.cpp
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
/// @fn void FL_SteadyRight::FL_SteadyRight(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
FL_SteadyRight::FL_SteadyRight(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::Declencheur::TEST, "Comportement actif : FL_STEADYRIGHT");
	context_->getRobot()->setShouldFollow(false);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FL_SteadyRight::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FL_SteadyRight::doAction()
{
	if (!context_->getRobot()->isCenterDetected())
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->turnRight();
		context_->getRobot()->turnRight();
		context_->getRobot()->forward();
		//context_->getRobot()->forward();
		//context_->getRobot()->forward();
	}
	else
		context_->changeBehavior(std::make_unique<FollowLine>(context_)); // Prochain état (hardcoded)
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////