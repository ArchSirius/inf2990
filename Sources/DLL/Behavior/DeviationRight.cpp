//////////////////////////////////////////////////////////////////////////////
/// @file DeviationRight.cpp
/// @author Équipe 1
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
/// @fn void DeviationRight::DeviationRight(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DeviationRight::DeviationRight(BehaviorContext* context) : Behavior(context)
{
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DeviationRight::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeviationRight::doAction()
{
	Behavior::doAction();

	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 45) // Angle du profil
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->forward();
	}

	else
	{
		context_->changeBehavior(std::make_unique<DefaultBehavior>(context_)); // Prochain état selon le profil
	}
}