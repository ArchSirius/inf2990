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

	/* TODO: Tester les capteur, avancer selon les r�sultats. */
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(context_->getRobot()->getCenterLineFollower()))
	{
		context_->getRobot()->forward();
		// Rendu l� dans le code
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////