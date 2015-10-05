///////////////////////////////////////////////////////////////////////////////
/// @file NoeudComposite.h
/// @author DGI-INF2990
/// @date 2007-01-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__
#define __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


#include "NoeudAbstrait.h"

#include <vector>
#include <memory>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudComposite
/// @brief Implantation d'un noeud du patron composite qui peut posséder
///        des enfants.
///
///        Cette classe implante les différentes fonctions relatives aux
///        enfants, comme l'ajout, le retrait, la recherche, etc.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudComposite : public NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudComposite(std::string type = {});
   /// Destructeur.
   virtual ~NoeudComposite() = default;


   // Interface d'un noeud

   /// Calcule la profondeur de l'arbre sous le noeud courant.
   unsigned int calculerProfondeur() const override;

   /// Vide le noeud de ses enfants.
   void vider() override;
   /// Efface le noeud passé en paramètre.
   void effacer( const NoeudAbstrait* noeud ) override;

   /// Cherche un noeud par le type (sur un noeud constant).
   const NoeudAbstrait* chercher( const std::string& typeNoeud ) const override;
   /// Cherche un noeud par le type.
   NoeudAbstrait* chercher( const std::string& typeNoeud ) override;
   /// Cherche un noeud enfant selon l'indice (sur un noeud constant).
   const NoeudAbstrait* chercher( unsigned int indice ) const override;
   /// Cherche un noeud enfant selon l'indice.
   NoeudAbstrait* chercher( unsigned int indice ) override;

   /// Ajoute un noeud enfant.
   bool ajouter( std::unique_ptr<NoeudAbstrait> enfant ) override;
   /// Obtient le nombre d'enfants du noeud.
   unsigned int obtenirNombreEnfants() const override;

   // Changer la sélection du noeud: on prend la version de la classe de
   // base.
   // virtual void inverserSelection();
   /// Efface les enfants sélectionnés.
   void effacerSelection() override;
   /// Sélectionne tous les enfants de même que le noeud.
   void selectionnerTout() override;
   /// Désélectionne tous les enfants de même que le noeud.
   void deselectionnerTout() override;
   /// Vérifier si le noeud ou un de ses enfants est sélectionné.
   bool selectionExiste() const override;

   /// Change le mode d'affichage des polygones.
   void changerModePolygones( bool estForce ) override;
   /// Assigne le mode d'affichage des polygones.
   void assignerModePolygones( GLenum modePolygones ) override;
   // Affiche le noeud: on prend la version de la classe de base.
   // virtual void afficher() const;
   /// Affiche le noeud de manière concrète.
   void afficherConcret() const override;
   /// Anime le noeud.
   void animer( float dt ) override;

 

   // Selection par hitbox
   void assignerSelectionEnfants(GLdouble x, GLdouble y, GLdouble z, bool keepOthers) override;
   void assignerSelectionEnfants(glm::ivec2 debut, glm::ivec2 fin, bool keepOthers) override;
   virtual void afficherSelectionsConsole();

   void accept(Tool& visitor) override;

   // Save
   Savable getSavableData() override;

protected:
	/// Le choix du conteneur pour les enfants.
	using conteneur_enfants = std::vector<std::unique_ptr<NoeudAbstrait>>;
    /// La liste des enfants.
    conteneur_enfants enfants_;


private:
   /// Constructeur copie déclaré privé mais non défini pour éviter le
   /// constructeur copie généré par le compilateur.
   NoeudComposite(const NoeudComposite&);

};


#endif // __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
