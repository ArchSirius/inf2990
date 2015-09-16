//////////////////////////////////////////////////////////////////////////////
/// @file Controller.h
/// @author INF2990-A15-01
/// @date 2005-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
/*
#ifndef __APPLICATION_CONTROLLER_H__
#define __APPLICATION_CONTROLLER_H__

#include <memory>

class ArbreRenduINF2990;
class FacadeModele;
class ToolState;

namespace vue {
	class Vue;
}

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class Controller
{
public:
	static Controller* getInstance();
	static void resetInstance();

	void changeState(ToolState* state);
	void animer(float temps);
private:
	Controller() = default;
	~Controller();

	static Controller* _instance;
	ToolState* _state;
};


#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////