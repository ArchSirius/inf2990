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

class NoeudCylindre;
class NoeudDepart;
class NoeudLigne;
class NoeudMur;


///////////////////////////////////////////////////////////////////////////
/// @class Tool
/// @brief Classe abstraite impl�mentant le patron de conception "Visitor",
///		   tel que montr� dans le livre "Design Patterns" (Gamma,
///		   Helm, Johnson & Vlissides) et dont les enfants concrets impl�mentent
///		   les fonctions des outils.
/// @author INF2990-A15-01
/// @date 2015-09-14
///////////////////////////////////////////////////////////////////////////
class Tool
{
public:
	virtual ~Tool() = default;

	virtual void visit(NoeudCylindre* node) = 0;
	virtual void visit(NoeudDepart* node) = 0;
	virtual void visit(NoeudLigne* node) = 0;
	virtual void visit(NoeudMur* node) = 0;

protected:
	Tool() = default;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
