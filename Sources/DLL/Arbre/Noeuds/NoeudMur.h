///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_MUR_H__
#define __ARBRE_NOEUDS_MUR_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"
#include "../../Commun/Utilitaire/Utilitaire.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMur
/// @brief Classe qui représente le noeud du mur dans l'arbre de rendu.
///
/// @Modified by : INF2990-A15-01
/// @date 2015-09-14
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMur(const std::string& typeNoeud);
	/// Deuxième étape de la construction
	void updateCreation(glm::dvec3 cursor) override;

	/// Destructeur.
	~NoeudMur() = default;

	/// Affiche le mur.
	virtual void afficherConcret() const;

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override;

	/// Assigne la position initiale du noeud.
	inline void assignerPositionInitiale(const glm::dvec3& positionInitiale) override;

	/// Assigne l'échelle du noeud
	inline void setScale(const glm::fvec3 scale) override;

	/// Points du mur
	struct dvec3_duo
	{
		glm::dvec3 start, end;
		dvec3_duo(){};
		dvec3_duo(const glm::dvec3& p1, const glm::dvec3& p2)
			: start(p1), end(p2) {};
	};
	inline dvec3_duo getPoints() const;

	//
	void updatePos() override;

private:
	glm::dvec3 _start, _end;
	glm::dvec3 _startInit, _endInit;
};

#endif // __ARBRE_NOEUDS_MUR_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudMur::assignerPositionInitiale( const glm::dvec3& positionInitiale )
///
/// Cette fonction permet d'assigner la position initiale du noeud par
/// rapport à son parent.
///
/// @param positionInitiale : La position initiale.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudMur::assignerPositionInitiale(
	const glm::dvec3& positionInitiale
	)
{
	positionInitiale_ = positionInitiale;
	_startInit = _start;
	_endInit = _end;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudMur::dvec3_duo NoeudMur::getPoints() const
///
/// Cette fonction retourne l'ensemble des deux points de début et de fin du mur
///
/// @return L'ensemble de points
///
////////////////////////////////////////////////////////////////////////
inline NoeudMur::dvec3_duo NoeudMur::getPoints() const
{
	return dvec3_duo(_start, _end);
}
