//////////////////////////////////////////////////////////////////////////////
/// @file MoveState.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_STATE_MOVESTATE_H__
#define __APPLICATION_STATE_MOVESTATE_H__

#include <memory>
#include "ToolState.h"

///////////////////////////////////////////////////////////////////////////
/// @class MoveState
/// @brief Classe concr�te impl�mentant qui traite des entr�es souris et
///		   clavier lorsque le programme est dans l'�tat de d�placement.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class MoveState : public ToolState
{
public:
	static std::unique_ptr<ToolState> getInstance();

	// Clics
	virtual void mouseDragging(int x, int y);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////