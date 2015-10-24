//////////////////////////////////////////////////////////////////////////////
/// @file SearchLineFinal.h
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
/// @class SearchLineFinal
/// @brief Classe Etat du comportement "Balayage sur 180 degr�s", ETAPE 3.
///
///////////////////////////////////////////////////////////////////////////
class SearchLineFinal : public Behavior
{
public:
	/// Constructeur
	SearchLineFinal(BehaviorContext* context);
	~SearchLineFinal() = default;

	/// Effectue une etape de son comportement
	void doAction() override;
};