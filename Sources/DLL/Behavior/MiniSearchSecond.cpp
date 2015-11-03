//////////////////////////////////////////////////////////////////////////////
/// @file MiniSearchSecond.cpp
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
/// @fn void MiniSearchSecond::MiniSearchSecond(BehaviorContext* context)
///
/// Constructeur
///
/// @param[in] context : La classe pouvant acc�der au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
MiniSearchSecond::MiniSearchSecond(BehaviorContext* context) : Behavior(context)
{
	Debug::getInstance()->printMessage(Debug::TEST, "Comportement actif : MINI_SEARCH_LINE_SECOND");
	context_->getRobot()->assignerAngleInitial(context_->getRobot()->obtenirAngle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void MiniSearchSecond::doAction()
///
/// Cette fonction effectue le comportement de l'�tat actuel.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void MiniSearchSecond::doAction()
{
	Behavior::doAction();

	if (std::abs(context_->getRobot()->obtenirAngleInitial() - context_->getRobot()->obtenirAngle()) < 30)
	{
		context_->getRobot()->turnRight();
	}

	else
	{
		context_->changeBehavior(std::make_unique<MiniSearchFinal>(context_)); // Prochain �tat (hardcoded)
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////