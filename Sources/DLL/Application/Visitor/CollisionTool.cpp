///////////////////////////////////////////////////////////////////////////////
/// @file CollisionTool.cpp
/// @author INF2990-A15-01
/// @date 2015-10-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "CollisionTool.h"
#include "../../Arbre/Noeuds/NoeudTypes.h"
#include "../../../../Commun/Utilitaire/Utilitaire.h"
#include "../../../../Commun/Utilitaire/Droite3D.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn CollisionTool::CollisionTool(NoeudRobot* robot)
///
/// Constructeur par paramètres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
CollisionTool::CollisionTool(NoeudRobot* robot)
	: _robot(robot)
{
	auto hitbox = utilitaire::calculerBoiteEnglobante(*_robot->getModele());
	_p1 = hitbox.coinMin;
	_p2 = glm::dvec3(hitbox.coinMin.x, hitbox.coinMax.y, hitbox.coinMin.z);
	_p3 = hitbox.coinMax;
	_p4 = glm::dvec3(hitbox.coinMax.x, hitbox.coinMin.y, hitbox.coinMin.z);

	_d1 = glm::dvec3(_p2 - _p1);
	_d2 = glm::dvec3(-_d1.y, _d1.x, _d1.z);

	segments[0] = segment(_p1, _p2, _d1, _d2);
	segments[1] = segment(_p2, _p3, _d2, _d1);
	segments[2] = segment(_p3, _p4, _d1, _d2);
	segments[3] = segment(_p4, _p1, _d2, _d1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::visit(NoeudCylindre* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::visit(NoeudCylindre* node)
{
	for (auto& segment : segments)
	{
		auto robotLine = math::Droite3D(segment.p1, segment.p2);
		const auto intersection = robotLine.perpendiculaireDroite(node->obtenirPositionRelative());
		// Intersection dans le segment = collision possible
		if ((intersection - segment.p1).length() > (segment.p2 - segment.p1).length()
			|| (intersection - segment.p2).length() > (segment.p2 - segment.p1).length())
			return;
		const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x;
		glm::dvec3 impactVect = intersection - node->obtenirPositionRelative();
		// Intersection dans le poteau = collision
		if (impactVect.length() <= radius)
		{
			doCollision(atan2(impactVect.y, impactVect.x));
			return;
		}
		// Coin dans le poteau = collision
		impactVect = node->obtenirPositionRelative() - segment.p1;
		if (impactVect.length() <= radius)
			doCollision(atan2(impactVect.y, impactVect.x));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::visit(NoeudMur* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::visit(NoeudMur* node)
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::doCollision(float angle)
///
/// Applique le rebond au robot suite à une collision
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::doCollision(float angle)
{
	/*
	1. Calculer l'angle de collision entre x et la droite perpendiculaire
	2. Déterminer le vecteur de rebond:
		x: cos(theta)
		y: sin(theta)
	3. Modifier le vecteur vitesse du robot
	*/
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
