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

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override;

	/// Si le click est sur le spawn
	bool clickHit(GLdouble x, GLdouble y, GLdouble z) override;
	/// Si le click est sur le spawn
	bool clickHit(glm::ivec2 debut, glm::ivec2 fin) override;

	/// On ne peux pas changer le scale du spawn
	inline void setScale(const glm::fvec3 scale) override {};
	/// On ne peux pas changer le scale du spawn
	inline void setScaleInitial(const glm::fvec3 scale) override {};
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
