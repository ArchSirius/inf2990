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

	// Suiveur central activé
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getCenterLineFollower()))
	{
		context_->getRobot()->forward();
	}

	// Suiveur centre-gauche activé
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getInsideLeftLineFollower()))
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->forward();
	}

	// Suiveur centre-droite activé
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getInsideRightLineFollower()))
	{
		context_->getRobot()->turnLeft();
		context_->getRobot()->forward();
	}

	// Suiveur extérieur-gauche activé
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getOutsideLeftLineFollower()))
	{
		context_->getRobot()->turnRight();
	}

	// Suiveur extérieur-droit activé
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getOutsideRightLineFollower()))
	{
		context_->getRobot()->turnLeft();
	}

	// Aucun suiveur activé
	else
	{
		//context_->changeBehavior(std::make_unique<DefaultBehavior>(context_)); // Prochain état selon le profil
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////