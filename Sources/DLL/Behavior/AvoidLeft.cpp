//////////////////////////////////////////////////////////////////////////////
/// @file AvoidLeft.cpp
/// @author �quipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////


#include "BehaviorList.h"
#include "../Arbre/Noeuds/NoeudRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void AvoidLeft::AvoidLeft(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
AvoidLeft::AvoidLeft(BehaviorContext* context) : Behavior(context)
{
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->setStartTime(time(0));
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
void AvoidLeft::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->getSpeed() > 0)
	{
		context_->getRobot()->setStartTime(time(0));
		context_->getRobot()->reverse();
	}

	else if (difftime(time(0), context_->getRobot()->getStartTime()) < 4) //Duree du profil
	{
		context_->getRobot()->reverse();
	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 45)
	{
		context_->getRobot()->turnLeft();
	}

	else
	{
		context_->getRobot()->setSpeed(0.0f);
		context_->changeBehavior(std::make_unique<DefaultBehavior>(context_));
	}
}

