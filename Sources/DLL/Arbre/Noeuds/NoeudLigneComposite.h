///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
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
/// @Modified by : INF2990-A15-01
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
	~NoeudLigneComposite() = default;

	/// Affiche la ligne.
	virtual void afficherConcret() const;
	/// Si le click est sur la ligne
	bool clickHit(glm::dvec3 point) override;
};


#endif // __ARBRE_NOEUDS_NoeudLigneComposite_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
