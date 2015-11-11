//////////////////////////////////////////////////////////////////////////////
/// @file MiniSearchFinal.cpp
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
/// @fn void MiniSearchFinal::MiniSearchFinal(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
MiniSearchFinal::MiniSearchFinal(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::BALAYAGE, "Comportement actif : MINI_SEARCH_LINE_FINAL");
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void MiniSearchFinal::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void MiniSearchFinal::doAction()
{
	Behavior::doAction();

	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
	{
		if (context_->getRobot()->isLastRightDetected())
			context_->getRobot()->turnRight();
		else if (context_->getRobot()->isLastLeftDetected())
			context_->getRobot()->turnLeft();
		else
		{
			context_->changeBehavior(
				context_->getRobot()->getBehavior(context_->getRobot()->getProfile().followLineNextState)
				); // Prochain état DE FOLLOWLINE selon le profil
		}
	}

	else
	{
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().followLineNextState)
			); // Prochain état DE FOLLOWLINE selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////