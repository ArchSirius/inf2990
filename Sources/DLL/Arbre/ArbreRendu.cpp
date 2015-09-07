////////////////////////////////////////////////
/// @file   ArbreRendu.cpp
/// @author Martin Bisson
/// @date   2007-01-28
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "ArbreRendu.h"
#include "UsineNoeud.h"
#include "NoeudAbstrait.h"

#include "GL/glew.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::ArbreRendu()
///
/// Ne fait qu'assigner que ce noeud n'est pas sélectionnable.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::ArbreRendu()
: NoeudComposite{ "racine" }
{
	// On ne veut pas que ce noeud soit sélectionnable.
	assignerEstSelectionnable(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::~ArbreRendu()
///
/// Détruit les usines des noeuds de l'arbre.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::~ArbreRendu()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
///
/// Cette fonction permet de créer un nouveau noeud, sans l'ajouter
/// directement à l'arbre de rendu.
///
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRendu::creerNoeud(
	const std::string& typeNouveauNoeud
	) const
{
	if (usines_.find(typeNouveauNoeud) == usines_.end()) {
		// Incapable de trouver l'usine
		return nullptr;
	}

	// Pour une raison que je ne comprends pas, la ligne suivante ne
	// compile pas:
	//
	// const UsineNoeud* usine = usines_[typeNouveauNoeud];
	//
	// On utilisera donc:
	const UsineAbstraite* usine{ (*(usines_.find(typeNouveauNoeud))).second };

	return usine->creerNoeud();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent, const std::string& typeNouveauNoeud)
///
/// Cette fonction permet d'ajouter un nouveau noeud dans l'arbre de
/// rendu.
///
/// @param[in] typeParent       : Le type du parent du nouveau noeud.
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRendu::ajouterNouveauNoeud(
	const std::string& typeParent,
	const std::string& typeNouveauNoeud
	)
{
	NoeudAbstrait* parent{ chercher(typeParent) };
	if (parent == nullptr) {
		// Incapable de trouver le parent
		return nullptr;
	}

	NoeudAbstrait* nouveauNoeud{ creerNoeud(typeNouveauNoeud) };
	if (nouveauNoeud)
		parent->ajouter(nouveauNoeud);

	return nouveauNoeud;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int ArbreRendu::calculerProfondeurMaximale()
///
/// Cette fonction retourne la profondeur maximale possible de l'arbre.
/// Comme lors du rendu, on effectue un glPushMatrix() pour sauvegarder
/// les transformations, ainsi qu'un glPushName() pour ajouter un nom
/// sur la pile des noms pour la sélection, la profondeur maximale de
/// l'arbre est limitée par la taille de la pile des matrices ainsi que
/// par celle de la pile des noms pour la sélection.
///
/// Cette fonction vérifie donc ces deux valeurs et retourne la plus
/// petite, c'est-à-dire celle qui limite la profondeur de l'arbre.
///
/// @return La profondeur maximale possible de l'arbre de rendu.
///
////////////////////////////////////////////////////////////////////////
unsigned int ArbreRendu::calculerProfondeurMaximale()
{
	GLint profondeurPileMatrice, profondeurPileNoms;

	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &profondeurPileMatrice);
	glGetIntegerv(GL_MAX_NAME_STACK_DEPTH, &profondeurPileNoms);

	return (profondeurPileMatrice < profondeurPileNoms) ? profondeurPileMatrice : profondeurPileNoms;
}


////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
