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
#ifndef __ARBRE_NOEUDS_TABLE_H__
#define __ARBRE_NOEUDS_TABLE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Classe qui représente le noeud de la table dans l'arbre de rendu.
///
/// @Modified by : INF2990-A15-01
/// @date 2015-09-14
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudTable(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTable() = default;

	/// Affiche la table.
	virtual void afficherConcret() const;
	
	

	/// Si le click touche le noeud
	bool clickHit(glm::dvec3 point) override;
private:
	int theta_ = 0;
};


#endif // __ARBRE_NOEUDS_TABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
