//////////////////////////////////////////////////////////////////////////////
/// @file Tool.h
/// @author INF2990-A15-01
/// @date 2015-09-14
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_VISITOR_TOOL_H__
#define __APPLICATION_VISITOR_TOOL_H__

#include <memory>

class NoeudAbstrait;

namespace vue {
	class Vue;
}

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
	virtual ~Tool();
	virtual void visitNode(std::unique_ptr<NoeudAbstrait> node);
	virtual void visitView(std::unique_ptr<vue::Vue> view);
protected:
	Tool();
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////