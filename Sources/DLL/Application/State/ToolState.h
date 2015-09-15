//////////////////////////////////////////////////////////////////////////////
/// @file ToolState.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_STATE_TOOLSTATE_H__
#define __APPLICATION_STATE_TOOLSTATE_H__

class Controller;

///////////////////////////////////////////////////////////////////////////
/// @class ToolState
/// @brief Classe abstraite impl�mentant le patron de conception "State",
///		   tel que montr� dans le livre "Design Patterns" (Gamma,
///		   Helm, Johnson & Vlissides) et dont les enfants concrets d�crivent
///		   le r�sultats des entr�es.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class ToolState
{
public:
	// Clics
	virtual void mouseClicked(int x, int y);
	virtual void mouseDragging(int x, int y);

	// Ctrl
	void ctrlKeyDown();
	void ctrlKeyUp();

	void changeState(std::unique_ptr<Controller> controller, ToolState* state);

protected:
	bool _isCtrlKeyDown;
};


#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
