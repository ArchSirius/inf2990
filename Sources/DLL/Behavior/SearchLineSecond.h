//////////////////////////////////////////////////////////////////////////////
/// @file SearchLineSecond.h
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
/// @class SearchLineSecond
/// @brief Classe Etat du comportement "Balayage sur 180 degr�s", ETAPE 2.
///
///////////////////////////////////////////////////////////////////////////
class SearchLineSecond : public Behavior
{
public:
	/// Constructeur
	SearchLineSecond(BehaviorContext* context);
	~SearchLineSecond() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};