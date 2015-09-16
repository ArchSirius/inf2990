//////////////////////////////////////////////////////////////////////////////
/// @file DuplicateTool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
/*
#ifndef __APPLICATION_VISITOR_DUPLICATETOOL_H__
#define __APPLICATION_VISITOR_DUPLICATETOOL_H__

#include "Tool.h"

///////////////////////////////////////////////////////////////////////////
/// @class DuplicateTool
/// @brief Classe concr�te h�ritant de Tool, qui effectue l'op�ration de
///		   duplication sur un noeud de l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class DuplicateTool : public Tool
{
public:
	DuplicateTool(int x, int y, int z);
	virtual void visitNode(std::unique_ptr<NoeudAbstrait> node);
private:
	// Coordonn�es du nouvel objet
	int _x;
	int _y;
	int _z;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////