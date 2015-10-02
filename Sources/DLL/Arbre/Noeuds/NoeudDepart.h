///////////////////////////////////////////////////////////////////////////
/// @file NoeudDepart.h
/// @author INF2990-A15-01
/// @date 2015-09-18
/// @version 1.0
///	
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudDepart
/// @brief Classe qui représente le point de départ dans l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-18
///////////////////////////////////////////////////////////////////////////
class NoeudDepart : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudDepart(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudDepart() = default;

	/// Affiche la table.
	void afficherConcret() const override;

	// Visitor
	void accept(Tool& visitor) override;

	bool clickHit(GLdouble x, GLdouble y, GLdouble z) override;
	bool clickHit(glm::ivec2 debut, glm::ivec2 fin) override;

	// Particularités
	inline void setScale(const glm::fvec3 scale) override {};
	inline void setScaleInitial(const glm::fvec3 scale) override {};
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
