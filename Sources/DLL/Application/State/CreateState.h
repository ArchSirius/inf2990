//////////////////////////////////////////////////////////////////////////////
/// @file CreateState.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_STATE_CREATESTATE_H__
#define __APPLICATION_STATE_CREATESTATE_H__

#include <memory>
#include "ToolState.h"

///////////////////////////////////////////////////////////////////////////
/// @class CreateState
/// @brief Classe concrète implémentant qui traite des entrées souris et
///		   clavier lorsque le programme est dans l'état de création.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class CreateState : public ToolState
{
	// TODO : Les classes CreateWallState, CreateLineState et CreateCylinder.
	// TODO : Une manière de pouvoir facilement faire un mur fantôme.

public:
	static std::unique_ptr<ToolState> getInstance();

	// Clics
	virtual void mouseClicked(int x, int y);
	virtual void mouseDragging(int x, int y);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////