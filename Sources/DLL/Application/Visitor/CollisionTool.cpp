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
#include "../../Application/Debug.h"

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
	const glm::dvec3 scale = glm::dvec3(0.6, 0.5, 1.0);
	auto hitbox = utilitaire::calculerBoiteEnglobante(*_robot->getModele());

	_p3 = hitbox.coinMin * scale + _robot->obtenirPositionRelative();
	_p4 = glm::dvec3(hitbox.coinMin.x, hitbox.coinMax.y, hitbox.coinMin.z) * scale + _robot->obtenirPositionRelative();
	_p1 = hitbox.coinMax * scale + _robot->obtenirPositionRelative();
	_p2 = glm::dvec3(hitbox.coinMax.x, hitbox.coinMin.y, hitbox.coinMin.z) * scale + _robot->obtenirPositionRelative();

	rotate(_p1, static_cast<float>(utilitaire::PI + utilitaire::DEG_TO_RAD(_robot->obtenirAngle())), _robot->obtenirPositionRelative());
	rotate(_p2, static_cast<float>(utilitaire::PI + utilitaire::DEG_TO_RAD(_robot->obtenirAngle())), _robot->obtenirPositionRelative());
	rotate(_p3, static_cast<float>(utilitaire::PI + utilitaire::DEG_TO_RAD(_robot->obtenirAngle())), _robot->obtenirPositionRelative());
	rotate(_p4, static_cast<float>(utilitaire::PI + utilitaire::DEG_TO_RAD(_robot->obtenirAngle())), _robot->obtenirPositionRelative());

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
		const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x;
		// Intersection dans le segment = collision possible
		if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
			&& length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
		{
			glm::dvec3 impactVect = intersection - node->obtenirPositionRelative();
			// Intersection dans le poteau = collision
			if (length(impactVect) <= radius)
			{
				Debug::getInstance()->printMessage(Debug::TEST, "Collision frontale!");
				doCollision(atan2(static_cast<float>(impactVect.y), static_cast<float>(impactVect.x)));
				return;
			}
		}
		else
		{
			// Coin dans le poteau = collision
			glm::dvec3 impactVect = node->obtenirPositionRelative() - segment.p1;
			if (length(impactVect) <= radius)
			{
				Debug::getInstance()->printMessage(Debug::TEST, "Collision en coin!");
				doCollision(atan2(static_cast<float>(impactVect.y), static_cast<float>(impactVect.x)));
			}
		}
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
	for (auto& segment : segments)
	{
		auto robotLine = math::Droite3D(segment.p1, segment.p2);
		const glm::dvec3 wallVect(cos(utilitaire::DEG_TO_RAD(-node->obtenirAngle())), sin(utilitaire::DEG_TO_RAD(-node->obtenirAngle())), 0);
		auto wallLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + wallVect);
		
		const auto robotAngle = atan2(robotLine.lireVecteur().y, robotLine.lireVecteur().x);
		auto wallAngle = atan2(wallLine.lireVecteur().y, wallLine.lireVecteur().x) + utilitaire::PI / 2;
		
		double m1;
		if (robotLine.lireVecteur().x != 0.0)
			m1 = robotLine.lireVecteur().y / robotLine.lireVecteur().x;
		else
			m1 = std::numeric_limits<double>::max();

		double m2;
		if (wallLine.lireVecteur().y != 0.0)
			m2 = wallLine.lireVecteur().x / wallLine.lireVecteur().y;
		else
			m2 = std::numeric_limits<double>::max();

		auto intersection = robotLine.intersectionDroiteInv(wallLine);
		if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
		 && length(intersection - segment.p2) <= length(segment.p2 - segment.p1)
		 && (abs(m1) <= abs(m2) + 0.0001
		 ||  abs(m1) >= abs(m2) - 0.0001))
		{
			Debug::getInstance()->printMessage(Debug::TEST, "Collision frontale!");
			if (wallAngle >= 0.0 && wallAngle <= utilitaire::PI)
			{
				// V1
				doCollision(_robot->obtenirAngle() - 90.0f);
				return;
			}
			else
			{
				// V1
				doCollision(_robot->obtenirAngle() - 90.0f);
				return;
			}
		}
	}
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

////////////////////////////////////////////////////////////////////////
///
/// @fn const double CollisionTool::length(glm::dvec3 vect)
///
/// Calcule la longueur d'un vecteur
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const double CollisionTool::length(glm::dvec3 vect)
{
	return sqrt(pow(vect.x, 2.0) + pow(vect.y, 2.0) + pow(vect.z, 2.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTool::rotate(glm::dvec3& point, float angle, const glm::dvec3& center)
///
/// Pivote un point autour d'un autre
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::rotate(glm::dvec3& point, float angle, const glm::dvec3& center)
{
	// X0  = Centre de rotation
	// X1  = Point domaine
	// X1' = Point image
	// R   = Matrice de rotation
	//
	// X1' = R * (X1 - X0) + X0
	const auto ref = point;
	point.x = cos(angle) * (ref.x - center.x) - sin(angle) * (ref.y - center.y) + center.x;
	point.y = sin(angle) * (ref.x - center.x) + cos(angle) * (ref.y - center.y) + center.y;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
