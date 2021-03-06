//////////////////////////////////////////////////////////////////////////////
/// @file SearchLine.cpp
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
/// @fn void SearchLine::SearchLine(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
SearchLine::SearchLine(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::COMPORTEMENT_DEBUT, "BALAYAGE");
	context_->getRobot()->setShouldFollow(true);
	context_->getRobot()->setSpeed(0.0f);
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
	context_->getRobot()->resetWaitTime();
	//context_->getRobot()->pauseSon(7, true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SearchLine::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SearchLine::doAction()
{
	Behavior::doAction();
	
	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 90)
	{
		context_->getRobot()->pauseSon(8, false);
		context_->getRobot()->turnLeft();
	}

	else
	{
		context_->getRobot()->pauseSon(8, true);
		Debug::getInstance()->printMessage(Debug::COMPORTEMENT_FIN, "BALAYAGE");
		context_->changeBehavior(std::make_unique<SearchLineSecond>(context_)); // Prochain �tat (hardcoded)
		// Le prochain �tat de SearchLine tel que sp�cifi� dans le profil change en fait celui de SearchLineFinal
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////