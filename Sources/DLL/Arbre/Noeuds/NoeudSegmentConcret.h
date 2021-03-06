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
/// @brief Classe qui repr�sente le noeud d'un segment de ligne dans l'arbre de rendu.
/// @author INF2990-A15-01
/// @date 2015-09-18
///////////////////////////////////////////////////////////////////////////
class NoeudSegmentConcret : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudSegmentConcret(const std::string& typeNoeud);
	/// Deuxi�me �tape de la construction
	void updateCreation(glm::dvec3 cursor) override;

	/// Destructeur.
	~NoeudSegmentConcret() = default;

	/// Affiche la segment.
	virtual void afficherConcret() const ;

	/// Assigne l'�chelle du noeud
	inline void setScale(const glm::fvec3 scale) override;

	/// Effectue l'animation du segment.
	//bool clickHit(GLdouble x, GLdouble y, GLdouble z);
	//bool clickHit(glm::ivec2 debut, glm::ivec2 fin);

	/// �crit l'�tat de la s�lection du noeud.
	inline void assignerSelection(bool selectionne) override;
	void assignerSelectionFromVisitor(bool selectionne);

	bool lineHit(glm::dvec3 point) override;

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override ;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
