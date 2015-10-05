///////////////////////////////////////////////////////////////////////////
/// @file NoeudSegmentConcret.h
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
#include "../../Application/Visitor/Tool.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudSegmentConcret
/// @brief Classe qui représente le noeud d'un segment de ligne dans l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-18
///////////////////////////////////////////////////////////////////////////
class NoeudSegmentConcret : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudSegmentConcret(const std::string& typeNoeud);
	/// Deuxième étape de la construction
	void updateCreation(glm::dvec3 cursor) override;

	/// Destructeur.
	~NoeudSegmentConcret();

	/// Affiche la segment.
	virtual void afficherConcret() const ;

	/// Effectue l'animation du segment.
	//bool clickHit(GLdouble x, GLdouble y, GLdouble z);
	//bool clickHit(glm::ivec2 debut, glm::ivec2 fin);

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override ;

private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
