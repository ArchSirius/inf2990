///////////////////////////////////////////////////////////////////////////////
/// @file ValidCheckTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ValidCheckTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../../../Commun/Utilitaire/Utilitaire.h"
#include "../../Application/FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ValidCheckTool::ValidCheckTool()
///
/// Constructeur par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ValidCheckTool::ValidCheckTool()
	: _valid(true)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ValidCheckTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Impl�mentation du visiteur Validit� pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::visit(NoeudCylindre* node)
{
	defaultValidCheck(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ValidCheckTool::visitNoeudDepart(NoeudDepart* node)
///
/// Impl�mentation du visiteur Validit� pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::visit(NoeudDepart* node)
{
	defaultValidCheck(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ValidCheckTool::visitNoeudLigne(NoeudSegmentConcret* node)
///
/// Impl�mentation du visiteur Validit� pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::visit(NoeudSegmentConcret* node)
{
	defaultValidCheck(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ValidCheckTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Impl�mentation du visiteur Validit� pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::visit(NoeudMur* node)
{
	defaultValidCheck(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ValidCheckTool::defaultTranslate(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur Validit� par d�faut.
///
/// @param[in] node : Le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::defaultValidCheck(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	if (!FacadeModele::obtenirInstance()->isOnTable(node))
		_valid = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ValidCheckTool::isValid()
///
/// Retourne la validit� de la position des objets
///
/// @param[in] node : Le noeud � visiter
///
/// @return True si valide; false sinon.
///
////////////////////////////////////////////////////////////////////////
bool ValidCheckTool::isValid() const
{
	return _valid;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
