//////////////////////////////////////////////////////////////////////////////
/// @file DeviationLeft.cpp
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
/// @fn void DeviationLeft::DeviationLeft(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DeviationLeft::DeviationLeft(BehaviorContext* context) : Behavior(context) 
{
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DeviationLeft::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeviationLeft::doAction()
{
	Behavior::doAction();

	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 45) // Angle du profil
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->forward();
	}

	else
	{
		context_->changeBehavior(std::make_unique<DefaultBehavior>(context_)); // Prochain �tat selon le profil
	}
}