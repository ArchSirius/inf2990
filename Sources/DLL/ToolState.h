//////////////////////////////////////////////////////////////////////////////
/// @file ToolState.h
/// @author INF2990-A15-01
/// @date 2015-09-09
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_TOOLSTATE_H__
#define __APPLICATION_TOOLSTATE_H__

///////////////////////////////////////////////////////////////////////////
/// @class ToolState
/// @brief Classe abstraite impl�mentant le patron de conception "State",
///		   tel que montr� dans le livre "Design Patterns" (Gamma,
///		   Helm, Johnson & Vlissides) et dont les enfants concrets d�crivent
///		   le r�sultats des entr�es.
/// @author INF2990-A15-01
/// @date 2015-09-09
///////////////////////////////////////////////////////////////////////////
class ToolState
{
public:
	// Clics
	virtual void MouseClicked(int x, int y);
	virtual void MouseDragging(int x, int y);
	
	//
	virtual void MANGER_LA_BEDAINE();
protected:
};


#endif // __APPLICATION_TOOLSTATE_H__
