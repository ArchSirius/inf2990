///////////////////////////////////////////////////////////////////////////
/// @file NoeudCylindre.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_Cylindre_H__
#define __ARBRE_NOEUDS_Cylindre_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudCylindre
/// @brief Classe qui représente le noeud du cylindre dans l'arbre de rendu.
///
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudCylindre : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudCylindre(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudCylindre();

	/// Affiche la table.
	virtual void afficherConcret() const;

	/// Si le click est sur le cylindre
	bool clickHit(GLdouble x, GLdouble y, GLdouble z) override;
	/// Si le click est sur le cylindre
	bool clickHit(glm::ivec2 debut, glm::ivec2 fin) override;

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override;


private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

};


#endif // __ARBRE_NOEUDS_Cylindre_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
