///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.h
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
/// @class NoeudLigne
/// @brief Classe qui repr�sente le noeud d'une ligne dans l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-18
///////////////////////////////////////////////////////////////////////////
class NoeudLigne : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudLigne(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudLigne();

	/// Affiche la segment.
	virtual void afficherConcret() const ;
	/// Effectue l'animation de la segment.
	bool clickHit(GLdouble x, GLdouble y, GLdouble z);
	bool clickHit(glm::ivec2 debut, glm::ivec2 fin);

	

	// Visitor
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
