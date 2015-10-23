//////////////////////////////////////////////////////////////////////////////
/// @file AvoidRight.h
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

///////////////////////////////////////////////////////////////////////////
/// @class AvoidRight
/// @brief Classe Etat du comportement "�vitement par la droite".
///
///////////////////////////////////////////////////////////////////////////
class AvoidRight : public Behavior
{
public:
	/// Constructeur
	AvoidRight(BehaviorContext* context);
	~AvoidRight() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};