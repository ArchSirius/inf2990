///////////////////////////////////////////////////////////////////////////////
/// @file DuplicateTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "DuplicateTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../Application/FacadeModele.h"
#include "../../../../Commun/Utilitaire/Vue/ProjectionOrtho.h"
#include "../../../../Commun/Utilitaire/Utilitaire.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::DuplicateTool(glm::dvec3 center)
///
/// Constructeur par paramètres.
///
/// @param[in] center : La position du centre des objets
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::DuplicateTool(glm::dvec3 center)
	: _center(center),
	_arbre(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990())
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn DuplicateTool::~DuplicateTool
///
/// Destructeur par défaut.
/// Suite à la mise en tampon des objets à dupliquer,
/// on duplique les objets avec le visiteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DuplicateTool::~DuplicateTool()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudCylindre* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudDepart* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudDepart* node)
{
	// NoeudDepart ne peut pas être dupliqué
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudSegmentConcret* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudSegmentConcret* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DuplicateTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur Duplication pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::visit(NoeudMur* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	defaultDuplicate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::defaultDuplicate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Duplication par défaut.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::defaultDuplicate(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;
	
	_domain.push(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::defaultDuplicate()
///
/// Clone les noeuds sources.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::duplicate()
{
	while (!_domain.empty())
	{
		// Cloner le noeud
		auto newNode = _arbre->ajouterNouveauNoeud(
			_domain.top()->obtenirParent()->obtenirType(),
			_domain.top()->obtenirType());
		newNode->assignerPositionRelative(_domain.top()->obtenirPositionRelative());
		newNode->assignerPositionInitiale(_domain.top()->obtenirPositionRelative());
		newNode->assignerAngle(_domain.top()->obtenirAngle());
		newNode->assignerAngleInitial(newNode->obtenirAngle());
		newNode->setScale(_domain.top()->getScale());
		newNode->setScaleInitial(newNode->getScale());

		// Ajouter le clone au tampon
		_buffer.push_back(newNode);
		_domain.pop();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::updateBuffer(glm::dvec3 cursor)
///
/// Met à jour les noeuds en tampon.
///
/// @param[in] cursor : La position du curseur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::updateBuffer(glm::dvec3 cursor)
{
	for (auto& node : _buffer)
	{
		glm::dvec3 vect = cursor - _center;
		glm::dvec3 initPos = node->obtenirPositionInitiale();
		glm::dvec3 pos;
		auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();
		pos[0] = initPos[0] + vect[0];
		pos[1] = initPos[1] + vect[1];
		pos[2] = initPos[2];
		node->assignerPositionRelative(pos);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DuplicateTool::confirmBuffer()
///
/// Clône "officiellement" les noeuds en tampon s'ils sont tous à une
/// position valide. Sinon, tous sont supprimés.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DuplicateTool::confirmBuffer()
{
	bool valid = true;
	for (auto& node : _buffer)
	{
		if (!FacadeModele::obtenirInstance()->isOnTable(node))

			valid = false;
	}

	if (!valid)
	{
		// Supprimer les noeuds dupliqués
		for (auto& node : _buffer)
		{
			auto parent = node->obtenirParent();
			parent->effacer(node);
		}
		_buffer.clear();
	}
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
