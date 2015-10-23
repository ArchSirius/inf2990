//////////////////////////////////////////////////////////////////////////////
/// @file BehaviorContext.h
/// @author �quipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <string>
#include "Behavior.h"

class NoeudRobot;

///////////////////////////////////////////////////////////////////////////
/// @class BehaviorContext
/// @brief Classe Etats contenant les comportements du robot.
///
///////////////////////////////////////////////////////////////////////////
class BehaviorContext
{
	std::unique_ptr<Behavior> state_;
	NoeudRobot* robot_;

public:
	/// Constructeur
	BehaviorContext(NoeudRobot* robot) : robot_(robot) { }
	~BehaviorContext() = default;

	/// Effectue une etape de son comportement
	void doAction();

	/// Change l'etat actuel du robot
	void changeBehavior(std::unique_ptr<Behavior> state);

	/// Envoi une reference observatrice vers le robot
	NoeudRobot* getRobot() const;
};

