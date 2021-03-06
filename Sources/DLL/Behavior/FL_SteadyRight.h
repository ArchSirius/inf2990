//////////////////////////////////////////////////////////////////////////////
/// @file FL_SteadyRight.h
/// @author �quipe 1
/// @date 2015-10-30
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Behavior.h"
#include "BehaviorContext.h"

///////////////////////////////////////////////////////////////////////////
/// @class FL_SteadyRight
/// @brief Classe sous-etat pour l'etat "FollowLine".
///
///////////////////////////////////////////////////////////////////////////
class FL_SteadyRight : public Behavior
{
public:
	/// Constructeur
	FL_SteadyRight(BehaviorContext* context);
	~FL_SteadyRight() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////