//////////////////////////////////////////////////////////////////////////////
/// @file FollowLine.cpp
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
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void FollowLine::doAction()
///
/// Cette fonction effectue le comportement de l'état actuel.
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
	
	//std::cout << "\n\n\n\n\n\n\n\n\n\n" << farLeft << " " << nearLeft << " " << centre << " " << nearRight << " " << farRight << "\n\n\n\n\n\n\n\n\n";

	if (nearLeft || farLeft)
	{

		context_->getRobot()->turnLeft();
		context_->changeBehavior(std::make_unique<FL_SteadyLeft>(context_));
	}

	else if (nearRight || farRight)
	{
		context_->getRobot()->turnRight();
		context_->changeBehavior(std::make_unique<FL_SteadyRight>(context_));
	}

	else if (centre)
	{
		context_->getRobot()->forward();
		context_->changeBehavior(std::make_unique<FL_SteadyFwd>(context_));
	}

	// Aucun suiveur activé
	if ((!farLeft && !nearLeft && !centre && !nearRight && !farRight))
	{
		context_->changeBehavior(std::make_unique<SearchLine>(context_)); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////