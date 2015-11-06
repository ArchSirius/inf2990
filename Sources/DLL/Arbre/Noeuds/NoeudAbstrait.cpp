////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "AideGL.h"
#include "GL/glew.h"
#include "FacadeModele.h"
#include "Modele3D.h"

#include "scene.h"
#include "utilitaire.h"
#include "Materiau.h"

#include <iostream>
#include <algorithm>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	type_( type )
{
	// X
	scale_[0] = 1.f;
	scaleInitial_[0] = 1.f;
	// Y
	scale_[1] = 1.f;
	scaleInitial_[1] = 1.f;
	// Z
	scale_[2] = 1.f;
	scaleInitial_[2] = 1.f;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const NoeudAbstrait& n0)
///
/// Construit une copie d'un noeud
///
/// @param[in] n0                 : Le noeud � copier
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(const NoeudAbstrait& n0) :
	type_(n0.type_),
	modePolygones_(n0.modePolygones_),
	positionRelative_(n0.positionRelative_),
	affiche_(n0.affiche_),
	selectionne_(n0.selectionne_),
	selectionnable_(n0.selectionnable_),
	enregistrable_(n0.enregistrable_),
	parent_(n0.parent_),
	modele_(n0.modele_),
	vbo_(n0.vbo_)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide d�clar� virtuel pour les classes d�riv�es.  La
/// lib�ration des afficheurs n'est pas la responsabilit� de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @param[in] noeud : Le noeud � effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant � ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud � ajouter.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(std::unique_ptr<NoeudAbstrait> enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'�tat de s�lection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	assignerSelection(!selectionne_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont s�lectionn�s parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction d�s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que d�s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction v�rifie si le noeud ou un de ses enfants est
/// s�lectionn�.
///
/// Elle ne fait que regarder si le noeud est s�lectionn�, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud s�lectionn�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est s�lectionn� ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode m�me si le
///                      noeud n'est pas s�lectionn�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par d�faut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// g�n�ralement � faire pour l'affichage, c'est-�-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit � sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'�tat.
///
/// L'affichage comme tel est confi� � la fonction afficherConcret(),
/// appel�e par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
			);

		// Rotation selon le vecteur k
		glRotatef(angleRotation_, 0, 0, 1);

		// �chelle
		glScalef(scale_[0], scale_[1], scale_[2]);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);		
		
		// Affichage concret
		afficherConcret();

		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.  Elle est
/// appel�e par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise � �tre surcharger par
/// les classes d�riv�es.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(GLdouble x, GLdouble y, GLdouble z)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return bool : Vrai si on click sur l'objet.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::clickHit(glm::dvec3 point)
{
	
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	glm::dvec3 matriceScale({ 1 / scale_.x, 1 / scale_.y, 1 / scale_.z });   
	glm::dmat3 matriceRotation({ glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), -glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), 0 }, { glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), 0 }, { 0, 0, 1 });
	glm::dvec3 matriceTranslation({ positionRelative_.x, positionRelative_.y, positionRelative_.z });   

	glm::dvec3 click = point;   
	
	//On applique la matrice de rotation et le scale
	click = matriceRotation * (click - matriceTranslation);
	click *= matriceScale;

	return (
		   click.x >= hitbox.coinMin.x && click.x <= hitbox.coinMax.x 
		&& click.y >= hitbox.coinMin.y && click.y <= hitbox.coinMax.y 
		&& click.z >= hitbox.coinMin.z && click.z <= hitbox.coinMax.z
		);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::clickHit(glm::ivec2 debut, glm::ivec2 fin)
///
/// V�rifie si le clic de souris touche le mod�le du noeud
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::clickHit(glm::ivec2 debut, glm::ivec2 fin)
{
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	int xMax = std::max(debut.x, fin.x);
	int yMax = std::max(debut.y, fin.y);
	int xMin = std::min(debut.x, fin.x);
	int yMin = std::min(debut.y, fin.y);

	glm::vec3 matriceScale({ scale_.x,scale_.y, scale_.z });
	glm::mat3 matriceRotation({ glm::cos(utilitaire::DEG_TO_RAD(-angleRotation_)), -glm::sin(utilitaire::DEG_TO_RAD(-angleRotation_)), 0 }, { glm::sin(utilitaire::DEG_TO_RAD(-angleRotation_)), glm::cos(utilitaire::DEG_TO_RAD(-angleRotation_)), 0 }, { 0, 0, 1 });
	glm::vec3 matriceTranslation({ positionRelative_.x, positionRelative_.y, positionRelative_.z });

	glm::vec3 hitboxMax({ hitbox.coinMax.x, hitbox.coinMax.y, 1 });
	glm::vec3 hitboxMin({ hitbox.coinMin.x, hitbox.coinMin.y, 1 });

	//On applique la matrice de rotation et le scale
	hitboxMax *= matriceScale;
	hitboxMax = matriceRotation * hitboxMax;
	hitboxMax += matriceTranslation;

	//On applique la matrice de rotation et le scale
	hitboxMin *= matriceScale;
	hitboxMin = matriceRotation * hitboxMin;
	hitboxMin += matriceTranslation;
	
	return (
		   hitboxMax.x >= xMin && hitboxMax.x <= xMax
		&& hitboxMax.y <= yMax && hitboxMax.y >= yMin
		&& hitboxMin.x >= xMin && hitboxMin.x <= xMax 
		&& hitboxMin.y <= yMax && hitboxMin.y >= yMin
		);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerSelectionEnfants(GLdouble x, GLdouble y, GLdouble z) 
///
/// Assigne la s�lection du noeud selon s'il est cliqu� ou non
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Vrai s'il devient s�lectionn�, non s'il ne l'est pas ou s'il l'�tait d�j�.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::assignerSelectionEnfants(glm::dvec3 point, bool keepOthers)
{
	bool becameSelected = true;

	// S'il est d�j� s�lectionn�, on veut retourner faux
	if (estSelectionne())
		becameSelected = false;

	if (clickHit(point)) {
		if (keepOthers)
			inverserSelection();
		else
			assignerSelection(true);
	}

	return (becameSelected && estSelectionne());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerSelectionEnfants(glm::ivec2 debut, glm::ivec2 fin, bool keepOthers)
///
/// Assigne la s�lection du noeud selon s'il est cliqu� ou non
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerSelectionEnfants(glm::ivec2 debut, glm::ivec2 fin, bool keepOthers)
{
	if (clickHit(debut, fin)) {
		if (keepOthers)
			inverserSelection();
		else
			assignerSelection(true);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::getSavableData() 
///
/// Retourne un entit� de type "Savable" qui repr�sente les donn�es
/// de ce noeud qui doit �tre sauvegard�
///
/// @param[in] x, y, z : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Savable NoeudAbstrait::getSavableData()
{
	Savable data{};

	data.setAttribute("type", obtenirType());
	data.setAttribute("parent_type", "");

	if (parent_ != nullptr) {
		data.setAttribute("parent_type", parent_->obtenirType());
	}

	data.setAttribute("scale_x", std::to_string(getScale().x));
	data.setAttribute("scale_y", std::to_string(getScale().y));
	data.setAttribute("scale_z", std::to_string(getScale().z));
	data.setAttribute("position_x", std::to_string(obtenirPositionRelative().x));
	data.setAttribute("position_y", std::to_string(obtenirPositionRelative().y));
	data.setAttribute("position_z", std::to_string(obtenirPositionRelative().z));

	data.setAttribute("angle_rotation", std::to_string(angleRotation_));

	return data;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherSelectionsConsole() 
///
/// Affiche � la console son niveau de s�lection (0,1)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
/*
void NoeudAbstrait::afficherSelectionsConsole()
{
	std::cout << type_ << " " << selectionne_ << std::endl;
}
*/


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::updateCreation(glm::dvec3 cursor) 
///
/// Dit au noeud de mettre � jour son affichage par rapport au curseur.
/// Utilis� lors de la cr�ation d'un noeud en deux �tapes (mur, ligne).
///
/// @param[in] cursor : Les coordonn�es du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::updateCreation(glm::dvec3 cursor)
{
	// Impl�mentation concr�te dans NoeudMur et NoeudLigne

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::lineHit(glm::dvec3 point) 
///
/// V�rifie si le point touche le noeud pr�sent, s'il est une ligne.
///
/// @param[in] cursor : Les coordonn�es du clic
///
/// @return Vrai si le point touche la ligne, faux sinon (ou si ce n'est pas une ligne).
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::lineHit(glm::dvec3 point)
{
	return false;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
