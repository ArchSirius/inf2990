//////////////////////////////////////////////////////////////////////////////
/// @file Tool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../../Arbre/Noeuds/NoeudTypes.h"


///////////////////////////////////////////////////////////////////////////
/// @class Tool
/// @brief Classe abstraite implémentant le patron de conception "Visitor",
///		   tel que montré dans le livre "Design Patterns" (Gamma,
///		   Helm, Johnson & Vlissides) et dont les enfants concrets implémentent
///		   les fonctions des outils.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class Tool
{
public:
	virtual ~Tool() = 0;

	virtual void visitNoeudCylindre(NoeudCylindre* node) = 0;
	virtual void visitNoeudDepart(NoeudDepart* node) = 0;
	virtual void visitNoeudLigne(NoeudLigne* node) = 0;
	virtual void visitNoeudMur(NoeudMur* node) = 0;

protected:
	Tool() = default;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
