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
	const auto scale = glm::dvec3(0.6, 0.5, 1.0);
	const auto initAngle = utilitaire::PI;
	if (_robot->getHitbox() == nullptr)
		_robot->makeHitbox();

	auto hitbox = _robot->getHitbox();
	
	auto p1 = glm::dvec3(hitbox->coinMax.x, hitbox->coinMax.y, hitbox->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2 = glm::dvec3(hitbox->coinMax.x, hitbox->coinMin.y, hitbox->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3 = glm::dvec3(hitbox->coinMin.x, hitbox->coinMin.y, hitbox->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4 = glm::dvec3(hitbox->coinMin.x, hitbox->coinMax.y, hitbox->coinMin.z) * scale + _robot->obtenirPositionRelative();

	rotate(p1, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p2, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p3, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p4, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());

	auto d1 = p2 - p1;
	auto d2 = glm::dvec3(-d1.y, d1.x, d1.z);

	segments[3] = segment(p1, p2, d1, d2); // gauche
	segments[0] = segment(p2, p3, d2, d1); // avant
	segments[1] = segment(p3, p4, d1, d2); // droite
	segments[2] = segment(p4, p1, d2, d1); // arrière
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
	int i = 0;
	for (const auto& segment : segments)
	{
		const auto robotLine = math::Droite3D(segment.p1, segment.p2);
		if (node->obtenirAngle() == 0.0f)  // ajout pour un angle egal a zero
			node->assignerAngle(0.00001f);

		const auto impactLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + segment.norm);
		const auto intersection = robotLine.intersectionDroite(impactLine);
		const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x; // 0.4 obtenu par tests

		// Intersection dans le segment = collision possible
		if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
		 && length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
		{
			const auto impactVect = intersection - node->obtenirPositionRelative();
			// Intersection dans le poteau = collision
			if (length(impactVect) <= radius)
			{
				// DEBUG start
				switch (i)
				{
				case 0:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Avant du robot");
					break;
				case 1:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Droite du robot");
					break;
				case 2:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Arriere du robot");
					break;
				case 3:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Gauche du robot");
					break;
				default:
					Debug::getInstance()->printMessage(Debug::CONSOLE, "Collision (erreur)");
					break;
				} // DEBUG end
				doCollision(atan2(impactVect.y, impactVect.x));
				return;
			}
		}
		else
		{
			// Coin dans le poteau = collision
			const auto impactVect = node->obtenirPositionRelative() - segment.p1;
			if (length(impactVect) <= radius)
			{
				// DEBUG start
				switch (i)
				{
				case 0:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Coin avant-gauche du robot");
					break;
				case 1:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Coin avant-droit du robot");
					break;
				case 2:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Coin arriere-droit du robot");
					break;
				case 3:
					Debug::getInstance()->printMessage(Debug::COLLISION, "Poteau / Coin arriere-gauche du robot");
					break;
				default:
					Debug::getInstance()->printMessage(Debug::CONSOLE, "Collision (erreur)");
					break;
				} // DEBUG end
				doCollision(atan2(impactVect.y, impactVect.x));
			}
		}

		++i;
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
	int i = 0;
	for ( const auto& segment : segments)
	{
		const auto robotLine = math::Droite3D(segment.p1, segment.p2);
		const glm::dvec3 wallVect(cos(utilitaire::DEG_TO_RAD(-node->obtenirAngle())), sin(utilitaire::DEG_TO_RAD(-node->obtenirAngle())), 0);
		const auto wallLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + wallVect);
		
		const auto robotAngle = atan2(robotLine.lireVecteur().y, robotLine.lireVecteur().x);
		const auto wallAngle = atan2(wallLine.lireVecteur().y, wallLine.lireVecteur().x) + utilitaire::PI / 2;
		
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
		 && length(intersection - node->getPoints().start) <= length(node->getPoints().end - node->getPoints().start)
		 && length(intersection - node->getPoints().end) <= length(node->getPoints().end - node->getPoints().start)
		 && (abs(m1) <= abs(m2) + 0.0001
 		 ||  abs(m1) >= abs(m2) - 0.0001))
		{
			// DEBUG start
			switch (i)
			{
			case 0:
				Debug::getInstance()->printMessage(Debug::COLLISION, "Mur / Avant du robot"); 
				break;
			case 1:
				Debug::getInstance()->printMessage(Debug::COLLISION, "Mur / Droite du robot");
				break;
			case 2:
				Debug::getInstance()->printMessage(Debug::COLLISION, "Mur / Arriere du robot");
				break;
			case 3:
				Debug::getInstance()->printMessage(Debug::COLLISION, "Mur / Gauche du robot");
				break;
			default:
				Debug::getInstance()->printMessage(Debug::CONSOLE, "Collision (erreur)");
				break;
			} 

			// DEBUG end
			if (wallAngle >= 0.0 && wallAngle <= utilitaire::PI)
			{
				// V1
				doCollision(_robot->obtenirAngle() - 90.0);
				return;
			}
			else
			{
				// V1
				doCollision(_robot->obtenirAngle() - 90.0);
				return;
			}
		}

		++i;
	}
	//Debug::getInstance()->printMessage(Debug::COLLISION, "Fin Traitement Mur");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::doCollision(double angle)
///
/// Applique le rebond au robot suite à une collision
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::doCollision(double angle)
{
	std::cout << "Speed: " << _robot->getSpeed() << std::endl;
	if (abs(_robot->getSpeed()) < 0.3f)
	{
		if (_robot->isTurnLeft())
			_robot->collisionRight();
		else if (_robot->isTurnRight())
			_robot->collisionLeft();
		
		//_robot->setSpeed(utilitaire::EPSILON);
	}
	
	_robot->setSpeed(-_robot->getMaxSpeed() * 1.5f * (_robot->getSpeed() / abs(_robot->getSpeed())));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double CollisionTool::length(glm::dvec3 vect) const
///
/// Calcule la longueur d'un vecteur
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
double CollisionTool::length(glm::dvec3 vect)
{
	return sqrt(pow(vect.x, 2.0) + pow(vect.y, 2.0) + pow(vect.z, 2.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTool::rotate(glm::dvec3& point, double angle, const glm::dvec3& center)
///
/// Pivote un point autour d'un autre
///
/// @param[] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::rotate(glm::dvec3& point, double angle, const glm::dvec3& center)
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
