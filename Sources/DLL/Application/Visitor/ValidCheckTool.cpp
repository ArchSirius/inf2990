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
/// Constructeur par défaut.
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
/// Implémentation du visiteur Validité pour un noeud de type
/// NoeudCylindre.
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
/// Implémentation du visiteur Validité pour un noeud de type
/// NoeudDepart.
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
/// @fn virtual void ValidCheckTool::visitNoeudLigne(NoeudLigne* node)
///
/// Implémentation du visiteur Validité pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::visit(NoeudLigne* node)
{
	defaultValidCheck(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void ValidCheckTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Validité pour un noeud de type
/// visitNoeudMur.
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
/// Implémentation du visiteur Validité par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ValidCheckTool::defaultValidCheck(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*node->getModele());
	if (!FacadeModele::obtenirInstance()->isOnTable(node->obtenirPositionRelative() + (hitbox.coinMin + 0.4)*(glm::dvec3)node->getScale()))
		_valid = false;
	else if (!FacadeModele::obtenirInstance()->isOnTable(node->obtenirPositionRelative() + (hitbox.coinMax + 0.4)*(glm::dvec3)node->getScale()))
		_valid = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ValidCheckTool::isValid()
///
/// Retourne la validité de la position des objets
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
