///////////////////////////////////////////////////////////////////////////
/// @file NoeudCylindre.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @Modified by : INF2990-A15-01
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
#include "utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCylindre
/// @brief Classe qui représente le noeud du cylindre dans l'arbre de rendu.
///
/// @Modified by : INF2990-A15-01
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
	bool clickHit(glm::dvec3 point) override;
	/// Si le click est sur le cylindre
	bool clickHit(glm::ivec2 debut, glm::ivec2 fin) override;

	void setScale(const glm::fvec3 scale) override;

	/// Accepte un visiteur Outils
	void accept(Tool& visitor) override;

private:

    /// Utilisée pour déterminer les coordonnées cylindriques
    /// de la distance entre le point cliqué et le centre du cylindre
    struct Distance
    {
        Distance(glm::dvec3 point, NoeudCylindre* noeud) {
            // r = |sqrt(x2 + y2) - sqrt(pos.x2 + pos.y2)|
            r = std::abs(sqrt(point.x*point.x + point.y*point.y) - sqrt(noeud->obtenirPositionRelative().x*noeud->obtenirPositionRelative().x + noeud->obtenirPositionRelative().y*noeud->obtenirPositionRelative().y));
            z = point.z - noeud->obtenirPositionRelative().z;
        }

        double r;   // Rayon
        double z;   // Hauteur
    };
};


#endif // __ARBRE_NOEUDS_Cylindre_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
