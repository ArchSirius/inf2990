///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once


#include "GL/glew.h"
#include <string>
#include <memory>
#include <iostream>

#include "glm\glm.hpp"
#include "../../Application/Savable.h"

class Tool;

/// Déclarations avancées pour contenir un pointeur vers un modèle3D et son storage
namespace modele{
	class Modele3D;
}
namespace opengl{
	class VBO;
}

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisée pour créer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant être présent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = { }
	);
	/// Constructeur par copie
	NoeudAbstrait(const NoeudAbstrait& n0);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);

	/// Obtient la position initiale du noeud.
	inline const glm::dvec3& obtenirPositionInitiale() const;

	/// Assigne la position initiale du noeud.
	inline void assignerPositionInitiale(const glm::dvec3& positionInitiale);

	/// Obtient l'angle du noeud.
	inline const float obtenirAngle() const;

	/// Assigne l'angle du noeud.
	inline void assignerAngle(const float angle);

	/// Obtient l'angle initial du noeud.
	inline const float obtenirAngleInitial() const;

	/// Assigne l'angle initial du noeud.
	inline void assignerAngleInitial(const float angleInitial);

	/// Obtient l'échelle du noeud
	inline glm::fvec3 getScale() const;

	/// Assigne l'échelle du noeud
	virtual inline void setScale(const glm::fvec3 scale);

	/// Obtient l'échelle initiale du noeud
	inline glm::fvec3 getScaleInitial() const;

	/// Assigne l'échelle initiale du noeud
	virtual inline void setScaleInitial(const glm::fvec3 scale);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// Écrit l'état de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// Vérifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// Écrit l'état de la sélection du noeud.
	inline void assignerSelection(bool selectionne);
	/// Vérifie si le noeud est sélectionné.
	inline bool estSelectionne() const;
	/// Écrit si le noeud peut être sélectionné ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// Vérifie si le noeud est sélectionnable.
	inline bool estSelectionnable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// Vérifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	/// Retourne le modèle 3D du coeud
	inline const modele::Modele3D* getModele();

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud passé en paramètre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(std::unique_ptr<NoeudAbstrait> enfant);
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Changer la sélection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants sélectionnés.
	virtual void effacerSelection();
	/// Sélectionne tous les enfants de même que le noeud.
	virtual void selectionnerTout();
	/// Désélectionne tous les enfants de même que le noeud.
	virtual void deselectionnerTout();
	/// Vérifier si le noeud ou un de ses enfants est sélectionné.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher() const;
	/// Affiche le noeud de manière concrète.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer(float dt);
	


	// Visitor
	virtual void accept(Tool& visitor) = 0;

	// Save
	virtual Savable getSavableData();

	// Pour la selection
	virtual bool clickHit(glm::dvec3 point);
	virtual bool clickHit(glm::ivec2 debut, glm::ivec2 fin);
	virtual bool assignerSelectionEnfants(glm::dvec3 point, bool keepOthers);
	virtual void assignerSelectionEnfants(glm::ivec2 debut, glm::ivec2 fin, bool keepOthers);
	virtual void afficherSelectionsConsole();

	// Creation en plusieurs clics
	virtual void updateCreation(glm::dvec3 cursor);

protected:
	/// Type du noeud.
	std::string      type_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Position relative du noeud.
	glm::dvec3         positionRelative_;

	/// Position initiale du noeud.
	glm::dvec3         positionInitiale_;

	/// Angle de rotation
	float angleRotation_{ 0.f };

	/// Angle de rotation initial
	float angleRotationInitial_{ 0.f };

	/// Échelle (scale)
	glm::fvec3 scale_;
	glm::fvec3 scaleInitial_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// Sélection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est sélectionnable.
	bool             selectionnable_{ true };

	/// Détermine si l'objet peut être sauvegardé en XML.
	bool             enregistrable_{ true };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D const* modele_;
	/// Storage pour le dessin du modèle
	opengl::VBO const* vbo_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionInitiale() const
///
/// Cette fonction retourne la position initiale du noeud par rapport
/// à son parent.
///
/// @return La position initiale.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionInitiale() const
{
	return positionInitiale_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionInitiale( const glm::dvec3& positionInitiale )
///
/// Cette fonction permet d'assigner la position initiale du noeud par
/// rapport à son parent.
///
/// @param positionInitiale : La position initiale.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionInitiale(
	const glm::dvec3& positionInitiale
	)
{
	positionInitiale_ = positionInitiale;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const float NoeudAbstrait::obtenirAngle() const
///
/// Cette fonction retourne l'angle de rotation du noeud.
///
/// @return L'angle.
///
////////////////////////////////////////////////////////////////////////
inline const float NoeudAbstrait::obtenirAngle() const
{
	return angleRotation_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAngle( const float angle )
///
/// Cette fonction permet d'assigner l'angle de rotation du noeud.
///
/// @param angle : L'angle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAngle(const float angle)
{
	angleRotation_ = angle;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const float NoeudAbstrait::obtenirAngleInitial() const
///
/// Cette fonction retourne l'angle initial de rotation du noeud.
///
/// @return L'angle initial.
///
////////////////////////////////////////////////////////////////////////
inline const float NoeudAbstrait::obtenirAngleInitial() const
{
	return angleRotationInitial_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAngleInitial( const float angleInitial )
///
/// Cette fonction permet d'assigner l'angle initial de rotation du noeud.
///
/// @param angleInitial : L'angle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAngleInitial(const float angleInitial)
{
	angleRotationInitial_ = angleInitial;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec3 NoeudAbstrait::getScale() const
///
/// Cette fonction retourne l'échelle du noeud
///
/// @return L'échelle
///
////////////////////////////////////////////////////////////////////////
inline glm::fvec3 NoeudAbstrait::getScale() const
{
	return scale_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::setScale( const glm::fvec3 scale )
///
/// Cette fonction permet d'assigner l'échelle du noeud.
///
/// @param angleInitial : L'échelle.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::setScale(const glm::fvec3 scale)
{
	scale_ = scale;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec3 NoeudAbstrait::getScaleInitial() const
///
/// Cette fonction retourne l'échelle initiale du noeud
///
/// @return L'échelle initiale
///
////////////////////////////////////////////////////////////////////////
inline glm::fvec3 NoeudAbstrait::getScaleInitial() const
{
	return scaleInitial_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::setScaleInitial( const glm::fvec3 scale )
///
/// Cette fonction permet d'assigner l'échelle initiale du noeud.
///
/// @param angleInitial : L'échelle initiale.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::setScaleInitial(const glm::fvec3 scaleInitial)
{
	scaleInitial_ = scaleInitial;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaîne représentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'état affiché ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'état que le noeud se fait afficher ou non.
///
/// @return L'état affiché ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'état d'être sélectionné ou non du noeud.
///
/// @return L'état sélectionné ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'état d'être sélectionnable ou non du noeud.
///
/// @param selectionnable : L'état sélectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'état d'être sélectionnable ou non du noeud.
///
/// @return L'état sélectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'état d'être enregistrable en XML ou non du
/// noeud.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au modèle, c'est-à-dire son
/// modèle 3D et sa liste d'affichage
///
/// @param modele : le modèle 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	modele_ = modele;
	vbo_ = liste;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const modele::Modele3D* getModele()
///
/// Cette fonction retourne le modèle 3D du noeud
///
/// @return Le modèle 3D
///
////////////////////////////////////////////////////////////////////////
inline const modele::Modele3D* NoeudAbstrait::getModele()
{
	return modele_;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
