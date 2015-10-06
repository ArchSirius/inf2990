////////////////////////////////////////////////
/// @file   NoeudComposite.cpp
/// @author DGI-2990
/// @date   2007-01-25
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudComposite.h"
#include "../../Application/Visitor/Tool.h"

#include <cassert>
#include <algorithm>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::NoeudComposite(const std::string& type)
///
/// Ne fait qu'appeler la version de la classe de base.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudComposite::NoeudComposite(std::string type /*= {} */) :
	NoeudAbstrait{std::move(type)}
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 de plus que la profondeur de son
/// enfants le plus profond.
///
/// @return La profondeur de l'arbre sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::calculerProfondeur() const
{
	unsigned int profondeurEnfantMax{ 0 };

	for (auto& enfant : enfants_)
	{
		const unsigned int profondeurEnfant{ enfant->calculerProfondeur() };
		if (profondeurEnfantMax < profondeurEnfant)
			profondeurEnfantMax = profondeurEnfant;
	}

	return profondeurEnfantMax + 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.  Elle effectue une
/// itération prudente sur les enfants afin d'être assez robuste pour
/// supporter la possibilité qu'un enfant en efface un autre dans son
/// destructeur, par exemple si deux objets ne peuvent pas exister l'un
/// sans l'autre.  Elle peut toutefois entrer en boucle infinie si un
/// enfant ajoute un nouveau noeud lorsqu'il se fait effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::vider()
{
	// L'itération doit être faite ainsi pour éviter les problèmes lorsque
	// le desctructeur d'un noeud modifie l'arbre, par exemple en retirant
	// d'autres noeuds.  Il pourrait y avoir une boucle infinie si la
	// desctruction d'un enfant entraînerait l'ajout d'un autre.
	enfants_.clear();
	enfants_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacer( const NoeudAbstrait* noeud )
///
/// Efface un noeud qui est un enfant ou qui est contenu dans un des
/// enfants.
///
/// @param[in] noeud : Le noeud à effacer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacer(const NoeudAbstrait* noeud)
{
	auto it = std::find_if(enfants_.begin(), enfants_.end(), [noeud] (const std::unique_ptr<NoeudAbstrait>& n) {
		if (n.get() == noeud) {
			return true;
		}
		else {
			n->effacer(noeud);
		}

		return false;
	});

	if (it != enfants_.end()) {
		// Erase it !
		enfants_.erase(it);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud ) const
///
/// Recherche un noeud d'un type donné parmi le noeud courant et ses
/// enfants.  Version constante de la fonction.
///
/// @param[in] typeNoeud : Le type du noeud cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(
	const std::string& typeNoeud
	) const
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (auto& enfant : enfants_)
		{
			auto noeud = enfant->chercher(typeNoeud);
			if (noeud) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud )
///
/// Recherche un noeud d'un type donné parmi le noeud courant et ses
/// enfants.
///
/// @param[in] typeNoeud : Le type du noeud cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (auto& enfant : enfants_)
		{
			auto noeud = enfant->chercher(typeNoeud);
			if (noeud) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( unsigned int indice ) const
///
/// Retourne le i-ème enfant, où i est l'indice passé à la fonction.
/// Version constante de la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(unsigned int indice) const
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice].get();
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( unsigned int indice )
///
/// Retourne le i-ème enfant, où i est l'indice passé à la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(unsigned int indice)
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice].get();
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::ajouter( NoeudAbstrait* enfant )
///
/// Ajoute un noeud enfant au noeud courant.
///
/// @param[in] enfant: Noeud à ajouter.
///
/// @return Vrai si l'ajout a réussi, donc en tout temps pour cette classe.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::ajouter(std::unique_ptr<NoeudAbstrait> enfant)
{
	enfant->assignerParent(this);
	enfants_.push_back(std::move(enfant));

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::obtenirNombreEnfants() const
///
/// Retourne le nombre d'enfants directement sous ce noeud.  Elle ne
/// donne pas le nombre total de descendants, mais bien le nombre de
/// ceux qui sont directement sous ce noeud.
///
/// @return Le nombre d'enfants directement sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::obtenirNombreEnfants() const
{
	// La taille ne doit jamais être négative, sinon le cast plus bas
	// donnera un résultat erroné.
	assert(enfants_.size() >= 0);

	return static_cast<unsigned int> (enfants_.size());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacerSelection()
///
/// Efface tous les noeuds sélectionnés situés sous ce noeud.  Elle
/// s'appelle donc récursivement sur tous les enfants, avant de retirer
/// les enfants sélectionnés.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacerSelection()
{
	// On efface tous les noeuds sélectionnés descendants des enfants.
	for (auto& enfant : enfants_){
		enfant->effacerSelection();
	}

	std::remove_if(enfants_.begin(), enfants_.end(), [](const std::unique_ptr<NoeudAbstrait>& enfant) {
		return enfant->estSelectionne();
	});
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::selectionnerTout()
///
/// Sélectionne tous les noeuds qui sont sélectionnés parmis les
/// les descendants de ce noeud, lui-même étant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::selectionnerTout()
{
	NoeudAbstrait::selectionnerTout();

	for (auto& enfant : enfants_) {
		enfant->selectionnerTout();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::deselectionnerTout()
///
/// Désélectionne tous les noeuds qui sont sélectionnés parmis les
/// les descendants de ce noeud, lui-même étant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::deselectionnerTout()
{
	selectionne_ = false;

	for (auto& enfant : enfants_){
		enfant->deselectionnerTout();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::selectionExiste() const
///
/// Vérifie si le noeud ou un de ses descendants est sélectionné en
/// s'appelant de manière récursive sur les enfants du noeud.
///
/// @return Vrai s'il existe un noeud sélectionné, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::selectionExiste() const
{
	if (selectionne_) {
		return true;
	}

	for (auto& enfant : enfants_){
		if (enfant->selectionExiste())
			return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::changerModePolygones( bool estForce )
///
/// Change le mode d'affichage des polygones pour ce noeud et ses
/// enfants.
///
/// @param[in] estForce : Si vrai, le mode est changé pour ce noeud et
///                       tous ses descendants.  Sinon, seuls les noeuds
///                       sélectionnés verront leur mode changer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::changerModePolygones(bool estForce)
{
	NoeudAbstrait::changerModePolygones(estForce);
	const bool forceEnfant = ((estForce) || (estSelectionne()));

	// Applique le changement récursivement aux enfants.
	for (auto& enfant : enfants_) {
		enfant->changerModePolygones(forceEnfant);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud et
/// de ses enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::assignerModePolygones(GLenum modePolygones)
{
	// Appel à la version de la classe de base.
	NoeudAbstrait::assignerModePolygones(modePolygones);

	// Applique le changement récursivement aux enfants.
	for (auto& enfant : enfants_){
		enfant->assignerModePolygones(modePolygones);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.  Elle est
/// appelée par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// Pour cette classe, elle affiche chacun des enfants du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::afficherConcret() const
{
	NoeudAbstrait::afficherConcret();

	for (auto& enfant : enfants_){
		enfant->afficher();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::animer( float dt )
///
/// Anime tous les enfants de ce noeud.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::animer(float dt)
{
	for (auto& enfant : enfants_) {
		enfant->animer(dt);
	}
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::assignerSelectionEnfants(GLdouble x, GLdouble y, GLdouble z)
///
/// Assigne la sélection pour chacun des enfants du noeud
///
/// @param[in] x, y, z : Les coordonées du clic
///
/// @return Vrai s'il devient sélectionné, non s'il ne l'est pas ou s'il l'était déjà.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::assignerSelectionEnfants(glm::dvec3 point, bool keepOthers)
{
	for (auto& enfant : enfants_) {
		if (enfant->assignerSelectionEnfants(point, keepOthers)) {
			assignerSelection(true);
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::assignerSelectionEnfants(GLdouble x, GLdouble y, GLdouble z)
///
/// Assigne la sélection pour chacun des enfants du noeud
///
/// @param[in] x, y, z : Les coordonées du clic
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::assignerSelectionEnfants(glm::ivec2 debut, glm::ivec2 fin, bool keepOthers)
{
	for (auto& enfant : enfants_) {
		enfant->assignerSelectionEnfants(debut, fin, keepOthers);
		if (enfant->estSelectionne())
			assignerSelection(true);
	}
}

void NoeudComposite::accept(Tool& visitor)
{
	for (auto& enfant : enfants_)
		enfant->accept(visitor);
}

Savable NoeudComposite::getSavableData()
{
	auto data = NoeudAbstrait::getSavableData();

	for (auto& child : enfants_) {
		if (child->estEnregistrable()) {
			data.addChild(child->getSavableData());
		}
	}

	return data;
}

void NoeudComposite::afficherSelectionsConsole()
{
	for (auto& enfant : enfants_) {
		enfant->afficherSelectionsConsole();
	}
	std::cout << type_ << " " << selectionne_ << std::endl;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
