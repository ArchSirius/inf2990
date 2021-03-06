//////////////////////////////////////////////////////////////////////////////
/// @file SearchLineSecond.cpp
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
/// @fn void SearchLineSecond::SearchLineSecond(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
SearchLineSecond::SearchLineSecond(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::TEST, "Comportement actif : SearchLineSecond");
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SearchLineSecond::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SearchLineSecond::doAction()
{
	Behavior::doAction();
	
	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 180)
	{
		context_->getRobot()->turnRight();
		context_->getRobot()->pauseSon(8, false);
	}

	else
	{
		context_->changeBehavior(std::make_unique<SearchLineFinal>(context_)); // Prochain �tat (hardcoded)
		// Le prochain �tat de SearchLine tel que sp�cifi� dans le profil change en fait celui de SearchLineFinal
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////