//////////////////////////////////////////////////////////////////////////////
/// @file behavior.h
/// @author �quipe 1
/// @date 2015-10-23
/// @version 1.0 
///
/// @Pojet 2 Automne 2015
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

class BehaviorContext;

///////////////////////////////////////////////////////////////////////////
/// @class behavior
/// @brief Classe Etats contenant les comportements du robot.
///
///////////////////////////////////////////////////////////////////////////
class Behavior
{
protected:
	BehaviorContext* context_;

public:
	/// Constructeur
	Behavior(BehaviorContext* context) : context_(context) {}
	~Behavior() = default;

	/// Effectue une etape de son comportement
	virtual void doAction();			
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////