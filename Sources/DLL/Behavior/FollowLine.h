//////////////////////////////////////////////////////////////////////////////
/// @file FollowLine.h
/// @author �quipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Behavior.h"
#include "BehaviorContext.h"
#include "Debug.h"
#include "NoeudRobot.h"

///////////////////////////////////////////////////////////////////////////
/// @class FollowLine
/// @brief Classe Etat du comportement "Suivi de ligne".
///
///////////////////////////////////////////////////////////////////////////
class FollowLine : public Behavior
{
public:
	/// Constructeur
	FollowLine(BehaviorContext* context) : Behavior(context) {
		Debug::getInstance()->printMessage(Debug::BALAYAGE, "SUIVI DE LIGNE");
		context_->getRobot()->resetWaitTime();
		context_->getRobot()->pauseSon(7, true);
		context_->getRobot()->pauseSon(8, true);
	}
	~FollowLine() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////