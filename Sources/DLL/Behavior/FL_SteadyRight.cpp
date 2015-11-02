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
	context_->getRobot()->setShouldFollow(true);
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
	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 45) // Angle hardcoded
		context_->getRobot()->turnRight();
	else
		context_->changeBehavior(std::make_unique<SearchLine>(context_)); // Prochain état selon le profil
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////