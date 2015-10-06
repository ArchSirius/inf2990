///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Marc Lacharite-Laframboise
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


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMur
/// @brief Classe qui repr�sente le noeud du mur dans l'arbre de rendu.
///
/// @Modified by : Marc Lacharite-Laframboise
/// @date 2015-09-14
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudMur(const std::string& typeNoeud);
	/// Deuxi�me �tape de la construction
	void updateCreation(glm::dvec3 cursor) override;

	/// Destructeur.
	~NoeudMur();

	/// Affiche le mur.
	virtual void afficherConcret() const;

	void setScale(const glm::fvec3 scale) override;

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override;

private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
};

#endif // __ARBRE_NOEUDS_MUR_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
