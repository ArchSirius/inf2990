///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeud.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUD_H__
#define __ARBRE_USINES_USINENOEUD_H__

#include <type_traits>
#include <string>
#include <memory>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class UsineAbstraite
/// @brief Classe de base abstraite des usines qui seront utilisées pour
///        créer les différents noeuds de l'arbre de rendu.
///
/// @author Martin Bisson
/// @date 2001-01-28
///////////////////////////////////////////////////////////////////////////
class UsineAbstraite{
public:
	virtual std::unique_ptr<NoeudAbstrait> creerNoeud() const = 0;

protected:
	UsineAbstraite(std::string nom) : nom_(nom) {}
	virtual ~UsineAbstraite() = default;

	/// Retourne le nom associé à l'usine
	inline const std::string& obtenirNom() const;
private:
	/// Le nom associé à l'usine
	std::string nom_;
};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& UsineNoeud::obtenirNom() const
///
/// Cette fonction retourne une chaîne représentante le nom associé à
/// l'usine.
///
/// @return Le nom associé à l'usine.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& UsineAbstraite::obtenirNom() const
{
	return nom_;
}

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeud
/// @brief Class template permettant de créer un type de noeud concret pour
///		   l'arbre de rendu.
///
/// @author Martin Paradis
/// @date 2015-06-24
///////////////////////////////////////////////////////////////////////////
template <typename Noeud>
class UsineNoeud : public UsineAbstraite
{
public:
   /// Destructeur vide déclaré virtuel pour les classes dérivées.
   inline ~UsineNoeud() {
	   vbo_.liberer();
   }

   /// Fonction à surcharger pour la création d'un noeud.
   std::unique_ptr<NoeudAbstrait> creerNoeud() const override;

   /// Constructeur qui prend le nom associé à l'usine.
	UsineNoeud(const std::string& nomUsine, const std::string& nomModele) 
		: UsineAbstraite{ nomUsine }
	{
		modele_.charger(nomModele);
		vbo_ = opengl::VBO{ &modele_ };
		vbo_.charger();
	}

protected:
   /// Modèle 3D correspondant à ce noeud.
   modele::Modele3D modele_;
   /// Storage pour le dessin du modèle
   opengl::VBO vbo_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeud::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
template <typename Noeud>
std::unique_ptr<NoeudAbstrait> UsineNoeud<Noeud>::creerNoeud() const
{
	static_assert(std::is_base_of<NoeudAbstrait, Noeud>::value, R"(Une usine de noeuds ne peut creer que des types de noeuds dérivant de NoeudAbstrait.)");
	auto noeud = std::make_unique<Noeud>( obtenirNom() );
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return std::move(noeud);
}
#endif // __ARBRE_USINES_USINENOEUD_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
