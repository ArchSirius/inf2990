//////////////////////////////////////////////////////////////////////////////
/// @file MiniSearch.cpp
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
/// @fn void MiniSearch::MiniSearch(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
MiniSearch::MiniSearch(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::TEST, "Comportement actif : MINI_SEARCH_LINE");
	context_->getRobot()->setShouldFollow(true);
	context_->getRobot()->setSpeed(0.0f);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void MiniSearch::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void MiniSearch::doAction()
{
	Behavior::doAction();

	if (context_->getRobot()->isLastRightDetected())
	{
		if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
		{
			context_->getRobot()->pauseSon(8, false);
			context_->getRobot()->turnRight();
			context_->getRobot()->turnRight();
		}
			
	}
		
	else if (context_->getRobot()->isLastLeftDetected())
	{
		if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
		{
			context_->getRobot()->pauseSon(8, false);
			context_->getRobot()->turnLeft();
			context_->getRobot()->turnLeft();
		}
			
	}

	else if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 10)
	{
		context_->getRobot()->pauseSon(8, false);
		context_->getRobot()->turnLeft();
		//context_->getRobot()->forward();
	}

	else
	{
		context_->getRobot()->pauseSon(8, true);
		context_->changeBehavior(std::make_unique<MiniSearchSecond>(context_)); // Prochain �tat (hardcoded)
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////