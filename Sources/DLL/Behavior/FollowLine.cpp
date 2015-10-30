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


	// Suiveur central activ�
	if ((farLeft && nearLeft && centre && nearRight && farRight) || (!farLeft && nearLeft && centre && nearRight && !farRight) || (!farLeft && !nearLeft && centre && !nearRight && !farRight))
	{
		context_->getRobot()->forward();
	}

	// Suiveurs gauche activ�
	else if ((farLeft && nearLeft && centre && !nearRight && !farRight) || (farLeft && nearLeft && !centre && !nearRight && !farRight))
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->forward();
	}

	// Suiveurs gauche activ�
	else if ((farLeft && !nearLeft && !centre && !nearRight && !farRight))
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->turnLeft();
	}

	// Suiveurs droit activ�
	else if ((!farLeft && !nearLeft && centre && nearRight && farRight) || (!farLeft && !nearLeft && !centre && nearRight && farRight))
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->forward();
	}

	// Suiveurs droit activ�
	else if ((!farLeft && !nearLeft && !centre && !nearRight && farRight))
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->turnRight();
	}

	// Aucun suiveur activ�
	if ((!farLeft && !nearLeft && !centre && !nearRight && !farRight))
	{
		context_->changeBehavior(std::make_unique<SearchLine>(context_)); // Prochain �tat selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////