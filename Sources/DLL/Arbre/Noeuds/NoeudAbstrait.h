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

/// D�clarations avanc�es pour contenir un pointeur vers un mod�le3D et son storage
namespace modele{
	class Modele3D;
}
namespace opengl{
	class VBO;
}

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilis�e pour cr�er l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant �tre pr�sent dans l'arbre de
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
	virtual inline void assignerPositionInitiale(const glm::dvec3& positionInitiale);

	/// Obtient l'angle du noeud.
	inline const float obtenirAngle() const;

	/// Assigne l'angle du noeud.
	inline void assignerAngle(const float angle);

	/// Obtient l'angle initial du noeud.
	inline const float obtenirAngleInitial() const;

	/// Assigne l'angle initial du noeud.
	inline void assignerAngleInitial(const float angleInitial);

	/// Obtient l'�chelle du noeud
	inline glm::fvec3 getScale() const;

	/// Assigne l'�chelle du noeud
	virtual inline void setScale(const glm::fvec3 scale);

	/// Obtient l'�chelle initiale du noeud
	inline glm::fvec3 getScaleInitial() const;

	/// Assigne l'�chelle initiale du noeud
	virtual inline void setScaleInitial(const glm::fvec3 scale);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// �crit l'�tat de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// V�rifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// �crit l'�tat de la s�lection du noeud.
	virtual inline void assignerSelection(bool selectionne);
	/// V�rifie si le noeud est s�lectionn�.
	inline bool estSelectionne() const;
	/// �crit si le noeud peut �tre s�lectionn� ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// V�rifie si le noeud est s�lectionnable.
	inline bool estSelectionnable() const;
	/// �crit si le noeud peut �tre enregistr� ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// V�rifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;

	/// Assigne le mod�le3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	/// Retourne le mod�le 3D du coeud
	inline const modele::Modele3D* getModele() const;

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud pass� en param�tre.
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

	/// Changer la s�lection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants s�lectionn�s.
	virtual void effacerSelection();
	/// S�lectionne tous les enfants de m�me que le noeud.
	virtual void selectionnerTout();
	/// D�s�lectionne tous les enfants de m�me que le noeud.
	virtual void deselectionnerTout();
	/// V�rifier si le noeud ou un de ses enfants est s�lectionn�.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher() const;
	/// Affiche le noeud de mani�re concr�te.
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

	// � des fins de debug
	//virtual void afficherSelectionsConsole();

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

	/// Angle de rotation en degr�
	float angleRotation_{ 0.f };

	/// Angle de rotation initial en degr�
	float angleRotationInitial_{ 0.f };

	/// �chelle (scale)
	glm::fvec3 scale_;
	glm::fvec3 scaleInitial_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// S�lection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est s�lectionnable.
	bool             selectionnable_{ true };

	/// D�termine si l'objet peut �tre sauvegard� en XML.
	bool             enregistrable_{ true };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D const* modele_;
	/// Storage pour le dessin du mod�le
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
/// � son parent.
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
/// rapport � son parent.
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
/// � son parent.
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
/// rapport � son parent.
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
/// Cette fonction retourne l'�chelle du noeud
///
/// @return L'�chelle
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
/// Cette fonction permet d'assigner l'�chelle du noeud.
///
/// @param angleInitial : L'�chelle.
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
/// Cette fonction retourne l'�chelle initiale du noeud
///
/// @return L'�chelle initiale
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
/// Cette fonction permet d'assigner l'�chelle initiale du noeud.
///
/// @param angleInitial : L'�chelle initiale.
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
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
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
/// @param affiche : L'�tat affich� ou non.
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
/// Cette fonction retourne l'�tat que le noeud se fait afficher ou non.
///
/// @return L'�tat affich� ou non.
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
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @param selectionne : L'�tat s�lectionn� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	selectionne_ = (selectionne && selectionnable_);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @return L'�tat s�lectionn� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @param selectionnable : L'�tat s�lectionnable ou non.
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
/// Cette fonction retourne l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @return L'�tat s�lectionnable ou non.
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
/// Cette fonction permet d'assigner l'�tat d'�tre entregistrable ou non du noeud.
///
/// @param enregistrable : L'�tat enregistrable ou non.
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
/// Cette fonction retourne l'�tat d'�tre enregistrable en XML ou non du
/// noeud.
///
/// @return L'�tat enregistrable ou non.
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
/// Cette fonction assigne l'objet de rendu au mod�le, c'est-�-dire son
/// mod�le 3D et sa liste d'affichage
///
/// @param modele : le mod�le 3D
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
/// Cette fonction retourne le mod�le 3D du noeud
///
/// @return Le mod�le 3D
///
////////////////////////////////////////////////////////////////////////
inline const modele::Modele3D* NoeudAbstrait::getModele() const
{
	return modele_;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
