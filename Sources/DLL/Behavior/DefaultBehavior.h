//////////////////////////////////////////////////////////////////////////////
/// @file DefaultBehavior.h
/// @author Équipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Behavior.h"
#include "BehaviorContext.h"

///////////////////////////////////////////////////////////////////////////
/// @class DefaultBehavior
/// @brief Classe Etat du comportement par defaut.
///
///////////////////////////////////////////////////////////////////////////
class DefaultBehavior : public Behavior
{
public:
	/// Constructeur
	DefaultBehavior(BehaviorContext* context) : Behavior(context) {}
	~DefaultBehavior() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};
