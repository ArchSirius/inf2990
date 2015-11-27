///////////////////////////////////////////////////////////////////////////////
/// @file TranslateTool.cpp
/// @author INF2990-A15-01
/// @date 2015-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "TranslateTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../Application/FacadeModele.h"
#include "../../../../Commun/Utilitaire/Vue/ProjectionOrtho.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn TranslateTool::TranslateTool
///     (GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
///
/// Constructeur par paramètres.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
TranslateTool::TranslateTool(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ)
	: _deltaX(deltaX), _deltaY(deltaY), _deltaZ(deltaZ)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudCylindre(NoeudCylindre* node)
///
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudCylindre* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudDepart(NoeudDepart* node)
///
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudDepart.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudDepart* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitNoeudLigne(NoeudSegmentConcret* node)
///
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudSegmentConcret.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudSegmentConcret* node)
{
	defaultTranslate(node);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void TranslateTool::visitvisitNoeudMur(NoeudMur* node)
///
/// Implémentation du visiteur Translation pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::visit(NoeudMur* node)
{
	defaultTranslate(node);
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;
	node->updatePos();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TranslateTool::defaultTranslate(NoeudAbstrait* node)
///
/// Implémentation du visiteur Translation par défaut.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TranslateTool::defaultTranslate(NoeudAbstrait* node)
{
	if (!node->estSelectionne() || !node->estSelectionnable())
		return;

	// TENTATIVE DESESPEREE # 1
	/*
	glm::dvec3 initPos = utilitaire::xyzToSph(node->obtenirPositionInitiale());
	auto delta = utilitaire::xyzToSph(glm::dvec3{ _deltaX, _deltaY, _deltaZ });
	glm::dvec3 pos;
	auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();
	pos[0] = initPos[0] + delta[0] * zoom; // Rho
	pos[1] = initPos[1] + delta[1]; // Phi
	pos[2] = initPos[2] + delta[2]; // Tht

	node->assignerPositionRelative(utilitaire::sphToXyz(pos));*/

	// TENTATIVE DESESPEREE # 2, PARTIE 1
	/*vue::PolarView savedCam;
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getIsPolar()) {
		savedCam = FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getPolarView();
		FacadeModele::obtenirInstance()->changeToOrbitView();
	}*/

	// ANCIENNE IMPLEMENTATION (ORTHO)
	/*
	glm::dvec3 initPos = node->obtenirPositionInitiale();
	glm::dvec3 pos;
	auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();
	pos.x = initPos.x + _deltaX * zoom;
    pos.y = initPos.y + _deltaY * zoom;
    pos.z = initPos.z + _deltaZ * zoom;

	node->assignerPositionRelative(pos);
	*/

	// TENTATIVE DESESPEREE # 2, PARTIE 2
	/*if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getIsPolar()) {
	FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().setPolarView(savedCam);
	}*/

	// TENTATIVE DESESPEREE # 3
	/*
	auto cursor = FacadeModele::obtenirInstance()->getCoordinates();
	auto vect = cursor - node->obtenirPositionRelative();
	auto initPos = node->obtenirPositionInitiale();
	auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();

	int direction = 10;
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getIsPolar())
		direction = -10;

	glm::dvec3 pos;
	pos.x = initPos.x + vect.x * direction * zoom;
	pos.y = initPos.y + vect.y * direction * zoom;
	pos.z = initPos.z + vect.z * direction * zoom;

	node->assignerPositionRelative(pos);
	*/	

	// TENTATIVE DESESPEREE # 4
	glm::dvec3 initPos = node->obtenirPositionInitiale();
	glm::dvec3 pos;
	auto zoom = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().getZoom();
	auto azimuth = FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().getPolarView().Azimuth;
	auto distance = sqrt(_deltaX*_deltaX + _deltaY*_deltaY);

	std::cout << azimuth << std::endl;

	pos.x = initPos.x + distance * sin(utilitaire::DEG_TO_RAD(azimuth));
	pos.y = initPos.y + distance * cos(utilitaire::DEG_TO_RAD(azimuth));
	pos.z = initPos.z;

	node->assignerPositionRelative(pos);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
