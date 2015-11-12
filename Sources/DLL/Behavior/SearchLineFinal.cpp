//////////////////////////////////////////////////////////////////////////////
/// @file SearchLineFinal.cpp
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
/// @fn void SearchLineFinal::SearchLineFinal(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant accéder au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
SearchLineFinal::SearchLineFinal(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::TEST, "Comportement actif : SearchLineFinal");
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SearchLineFinal::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SearchLineFinal::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->isLastRightDetected())
	{
		if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
		{
			context_->getRobot()->turnRight();
			context_->getRobot()->turnRight();
		}

	}

	else if (context_->getRobot()->isLastLeftDetected())
	{
		if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
		{
			context_->getRobot()->turnLeft();
			context_->getRobot()->turnLeft();
		}

	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 5)
	{
		context_->getRobot()->turnLeft();
		//context_->getRobot()->forward();
	}

	else
	{
		context_->changeBehavior(
			context_->getRobot()->getBehavior(context_->getRobot()->getProfile().searchLineNextState)
			); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////