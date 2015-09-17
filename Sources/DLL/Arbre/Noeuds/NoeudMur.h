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
/// @brief Classe qui représente le noeud du mur dans l'arbre de rendu.
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
	/// Constructeur à partir du type du noeud.
	NoeudMur(const std::string& typeNoeud);
	//NoeudMur(const std::string& typeNoeud, float posX, float posY, float posZ);

	/// Destructeur.
	~NoeudMur();

	/// Affiche la table.
	virtual void afficherConcret() const;
	/// Effectue l'animation de la table.
	virtual void animer(float temps);


private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	/// Position de l'objet.
	float posX_{ 0.f };
	float posY_{ 0.f };
	float posZ_{ 0.f };

};


#endif // __ARBRE_NOEUDS_MUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
