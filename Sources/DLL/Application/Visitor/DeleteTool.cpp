///////////////////////////////////////////////////////////////////////////////
/// @file DeleteTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "DeleteTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn DeleteTool::~DeleteTool
///
/// Destructeur par d�faut.
/// Suite � la mise en tampon des objets � supprimer,
/// on supprime les objets avec le visiteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
DeleteTool::~DeleteTool()
{
	deleteBuffer();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DeleteTool::visit(NoeudCylindre* node)
///
/// Impl�mentation du visiteur Suppression pour un noeud de type
/// NoeudCylindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::visit(NoeudCylindre* node)
{
	defaultDelete(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DeleteTool::visit(NoeudDepart* node)
///
/// Impl�mentation du visiteur Suppression pour un noeud de type
/// NoeudDepart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::visit(NoeudDepart* node)
{
	// NoeudDepart ne peut pas �tre supprim�
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DeleteTool::visit(NoeudLigne* node)
///
/// Impl�mentation du visiteur Suppression pour un noeud de type
/// NoeudLigne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::visit(NoeudLigne* node)
{
	defaultDelete(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void DeleteTool::visit(NoeudMur* node)
///
/// Impl�mentation du visiteur Suppression pour un noeud de type
/// NoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::visit(NoeudMur* node)
{
	defaultDelete(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DeleteTool::defaultDelete(NoeudAbstrait* node)
///
/// Impl�mentation du visiteur Suppression par d�faut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::defaultDelete(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	buffer.push(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void DeleteTool::deleteBuffer()
///
/// Suppression des objets en tampon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void DeleteTool::deleteBuffer()
{
	while (!buffer.empty())
	{
		auto parent = buffer.top()->obtenirParent();
		parent->effacer(buffer.top());
		buffer.pop();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
