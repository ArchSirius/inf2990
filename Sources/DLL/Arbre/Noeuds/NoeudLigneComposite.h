///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : Sabrina Barouche
/// @date 2015-09-14
/// @version 1.1
///	Adaptation du modele du cadriciel (ConeCube) pour nos noeuds
/// 
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_LigneComposite_H__
#define __ARBRE_NOEUDS_LigneComposite_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigneComposite
/// @brief Classe qui représente le noeud de la table dans l'arbre de rendu.
///
/// @Modified by : Barouche Sabrina
/// @date 2015-09-14
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudLigneComposite : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudLigneComposite(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudLigneComposite();

	/// Affiche la ligne.
	virtual void afficherConcret() const;
	/// Si le click est sur la ligne
	bool clickHit(GLdouble x, GLdouble y, GLdouble z) override;


private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

};


#endif // __ARBRE_NOEUDS_NoeudLigneComposite_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
