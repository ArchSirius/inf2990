//////////////////////////////////////////////////////////////////////////////
/// @file FollowLine.cpp
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
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void FollowLine::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FollowLine::doAction()
{
	Behavior::doAction();
	bool centre = context_->getRobot()->isCenterDetected();
	bool nearLeft = context_->getRobot()->isNearLeftDetected();
	bool farLeft = context_->getRobot()->isFarLeftDetected();
	bool nearRight = context_->getRobot()->isNearRightDetected();
	bool farRight = context_->getRobot()->isFarRightDetected();
	
	
	if ((nearLeft || farLeft) && !centre)
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->pauseSon(8, false);
		context_->changeBehavior(std::make_unique<FL_SteadyLeft>(context_));
	}

	else if ((nearRight || farRight) && !centre )
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->pauseSon(8, false);
		context_->changeBehavior(std::make_unique<FL_SteadyRight>(context_));
	}
	else if (farLeft && !centre)
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->pauseSon(8, false);
		//context_->getRobot()->turnLeft();
		//context_->getRobot()->turnLeft();
		//context_->getRobot()->turnLeft();
	}
	else if (farRight && !centre)
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->pauseSon(8, false);
		//context_->getRobot()->turnRight();
		//context_->getRobot()->turnRight();
		//context_->getRobot()->turnRight();
	}
	else if (centre)
	{
		context_->getRobot()->forward();
		context_->getRobot()->pauseSon(8, true);
		context_->changeBehavior(std::make_unique<FL_SteadyFwd>(context_));
	}

	// Aucun suiveur activ�
	if ((!farLeft && !nearLeft && !centre && !nearRight && !farRight))
	{
		context_->getRobot()->pauseSon(8, true);
		context_->changeBehavior(std::make_unique<MiniSearch>(context_)); // Prochain �tat (hardcoded)
		// Le prochain �tat sp�cifi� par le profil change celui de MiniSearchLineFinal
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////