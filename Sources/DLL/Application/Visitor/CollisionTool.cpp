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

	/// Vecteur du point 1 au point 2
	auto d1 = p2 - p1;
	/// Vecteur normal de ce vecteur.
	auto d2 = glm::dvec3(-d1.y, d1.x, d1.z);

	/// Enregistrement des segments
	segments[3] = segment(p1, p2, d1, d2); // gauche
	segments[0] = segment(p2, p3, d2, d1); // avant
	segments[1] = segment(p3, p4, d1, d2); // droite
	segments[2] = segment(p4, p1, d2, d1); // arrière


	/// Detection des capteurs.
	/// Capteur Centre
	auto hitboxMidSensorDanger = _robot->getMidSensorDanger();
	auto hitboxMidSensorSafe = _robot->getMidSensorSafe();
	/// Creation des points.
	auto p1MidDanger = glm::dvec3(hitboxMidSensorDanger->coinMax.x, hitboxMidSensorDanger->coinMax.y, hitboxMidSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2MidDanger = glm::dvec3(hitboxMidSensorDanger->coinMax.x, hitboxMidSensorDanger->coinMin.y, hitboxMidSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3MidDanger = glm::dvec3(hitboxMidSensorDanger->coinMin.x, hitboxMidSensorDanger->coinMin.y, hitboxMidSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4MidDanger = glm::dvec3(hitboxMidSensorDanger->coinMin.x, hitboxMidSensorDanger->coinMax.y, hitboxMidSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	
	auto p1MidSafe = glm::dvec3(hitboxMidSensorSafe->coinMax.x, hitboxMidSensorSafe->coinMax.y, hitboxMidSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2MidSafe = glm::dvec3(hitboxMidSensorSafe->coinMax.x, hitboxMidSensorSafe->coinMin.y, hitboxMidSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3MidSafe = glm::dvec3(hitboxMidSensorSafe->coinMin.x, hitboxMidSensorSafe->coinMin.y, hitboxMidSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4MidSafe = glm::dvec3(hitboxMidSensorSafe->coinMin.x, hitboxMidSensorSafe->coinMax.y, hitboxMidSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	
	rotate(p1MidDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p2MidDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p3MidDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p4MidDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());

	rotate(p1MidSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p2MidSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p3MidSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());
	rotate(p4MidSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle()), _robot->obtenirPositionRelative());

	/// Droite et normale
	auto midD1 = p2MidDanger - p1MidDanger;
	auto midD2 = glm::dvec3(-midD1.y, midD1.x, midD1.z);
	/// Enregistrement des segments.
	segCenter[0][0] = segment(p1MidDanger, p2MidDanger, midD1, midD2);
	segCenter[0][1] = segment(p2MidDanger, p3MidDanger, midD2, midD1);
	segCenter[0][2] = segment(p3MidDanger, p4MidDanger, midD1, midD2);
	segCenter[1][0] = segment(p1MidSafe, p2MidSafe, midD1, midD2);
	segCenter[1][1] = segment(p2MidSafe, p3MidSafe, midD2, midD1);
	segCenter[1][2] = segment(p3MidSafe, p4MidSafe, midD1, midD2);


	/// Capteur Gauche
	auto hitboxLeftSensorDanger = _robot->getLeftSensorDanger();
	auto hitboxLeftSensorSafe = _robot->getLeftSensorSafe();
	/// Creation des points.
	auto p1LeftDanger = glm::dvec3(hitboxLeftSensorDanger->coinMax.x, hitboxLeftSensorDanger->coinMax.y, hitboxLeftSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2LeftDanger = glm::dvec3(hitboxLeftSensorDanger->coinMax.x, hitboxLeftSensorDanger->coinMin.y, hitboxLeftSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3LeftDanger = glm::dvec3(hitboxLeftSensorDanger->coinMin.x, hitboxLeftSensorDanger->coinMin.y, hitboxLeftSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4LeftDanger = glm::dvec3(hitboxLeftSensorDanger->coinMin.x, hitboxLeftSensorDanger->coinMax.y, hitboxLeftSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();

	auto p1LeftSafe = glm::dvec3(hitboxLeftSensorSafe->coinMax.x, hitboxLeftSensorSafe->coinMax.y, hitboxLeftSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2LeftSafe = glm::dvec3(hitboxLeftSensorSafe->coinMax.x, hitboxLeftSensorSafe->coinMin.y, hitboxLeftSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3LeftSafe = glm::dvec3(hitboxLeftSensorSafe->coinMin.x, hitboxLeftSensorSafe->coinMin.y, hitboxLeftSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4LeftSafe = glm::dvec3(hitboxLeftSensorSafe->coinMin.x, hitboxLeftSensorSafe->coinMax.y, hitboxLeftSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();

	rotate(p1LeftDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p2LeftDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p3LeftDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p4LeftDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());

	rotate(p1LeftSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p2LeftSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p3LeftSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());
	rotate(p4LeftSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() + 45.0), _robot->obtenirPositionRelative());

	/// Droite et normale
	auto leftD1 = p2LeftDanger - p1LeftDanger;
	auto leftD2 = glm::dvec3(-leftD1.y, leftD1.x, leftD1.z);
	/// Enregistrement des segments.
	segLeft[0][0] = segment(p1LeftDanger, p2LeftDanger, leftD1, leftD2);
	segLeft[0][1] = segment(p2LeftDanger, p3LeftDanger, leftD2, leftD1);
	segLeft[0][2] = segment(p3LeftDanger, p4LeftDanger, leftD1, leftD2);
	segLeft[1][0] = segment(p1LeftSafe, p2LeftSafe, leftD1, leftD2);
	segLeft[1][1] = segment(p2LeftSafe, p3LeftSafe, leftD2, leftD1);
	segLeft[1][2] = segment(p3LeftSafe, p4LeftSafe, leftD1, leftD2);


	/// Capteur Droit
	auto hitboxRightSensorDanger = _robot->getRightSensorDanger();
	auto hitboxRightSensorSafe = _robot->getRightSensorSafe();
	/// Creation des points.
	auto p1RightDanger = glm::dvec3(hitboxRightSensorDanger->coinMax.x, hitboxRightSensorDanger->coinMax.y, hitboxRightSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2RightDanger = glm::dvec3(hitboxRightSensorDanger->coinMax.x, hitboxRightSensorDanger->coinMin.y, hitboxRightSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3RightDanger = glm::dvec3(hitboxRightSensorDanger->coinMin.x, hitboxRightSensorDanger->coinMin.y, hitboxRightSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4RightDanger = glm::dvec3(hitboxRightSensorDanger->coinMin.x, hitboxRightSensorDanger->coinMax.y, hitboxRightSensorDanger->coinMin.z) * scale + _robot->obtenirPositionRelative();

	auto p1RightSafe = glm::dvec3(hitboxRightSensorSafe->coinMax.x, hitboxRightSensorSafe->coinMax.y, hitboxRightSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p2RightSafe = glm::dvec3(hitboxRightSensorSafe->coinMax.x, hitboxRightSensorSafe->coinMin.y, hitboxRightSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p3RightSafe = glm::dvec3(hitboxRightSensorSafe->coinMin.x, hitboxRightSensorSafe->coinMin.y, hitboxRightSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	auto p4RightSafe = glm::dvec3(hitboxRightSensorSafe->coinMin.x, hitboxRightSensorSafe->coinMax.y, hitboxRightSensorSafe->coinMin.z) * scale + _robot->obtenirPositionRelative();
	
	rotate(p1RightDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p2RightDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p3RightDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p4RightDanger, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());

	rotate(p1RightSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p2RightSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p3RightSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	rotate(p4RightSafe, initAngle + utilitaire::DEG_TO_RAD(_robot->obtenirAngle() - 45.0), _robot->obtenirPositionRelative());
	
	/// Droite et normale
	auto rightD1 = p2RightDanger - p1RightDanger;
	auto rightD2 = glm::dvec3(-rightD1.y, rightD1.x, rightD1.z);
	/// Enregistrement des segments.
	segRight[0][0] = segment(p1RightDanger, p2RightDanger, rightD1, rightD2);
	segRight[0][1] = segment(p2RightDanger, p3RightDanger, rightD2, rightD1);
	segRight[0][2] = segment(p3RightDanger, p4RightDanger, rightD1, rightD2);
	segRight[1][0] = segment(p1RightSafe, p2RightSafe, rightD1, rightD2);
	segRight[1][1] = segment(p2RightSafe, p3RightSafe, rightD2, rightD1);
	segRight[1][2] = segment(p3RightSafe, p4RightSafe, rightD1, rightD2);

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
	computeCollision(node);
	if (node->estAffiche() && difftime(time(0), _robot->getLastDetection()) > 1)
	{
		computeDetection(node);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::computeCollision(NoeudCylindre* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::computeCollision(NoeudCylindre* node)
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
/// @fn virtual void CollisionTool::computeDetection(NoeudCylindre* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudCylindre.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::computeDetection(NoeudCylindre* node)
{
	for (int j = 0; j < 2; j++)
	{
		for (const auto& segment : segCenter[j])
		{
			const auto robotLine = math::Droite3D(segment.p1, segment.p2);
			if (node->obtenirAngle() == 0.0f)  // ajout pour un angle egal a zero
				node->assignerAngle(0.00001f);

			const auto impactLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + segment.norm);
			const auto intersection = robotLine.intersectionDroite(impactLine);
			const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x; // 0.4 obtenu par tests

			// Intersection dans le segment = detection possible
			if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
				&& length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
			{
				const auto impactVect = intersection - node->obtenirPositionRelative();
				// Intersection dans le poteau = detection
				if (length(impactVect) <= radius)
				{					
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE, "Poteau");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE);
					return;
				}
			}
			else
			{
				// Coin dans le poteau = detection
				const auto impactVect = node->obtenirPositionRelative() - segment.p1;
				if (length(impactVect) <= radius)
				{
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE, "Poteau ");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE);
					return;
				}
			}
		}

		for (const auto& segment : segLeft[j])
		{
			const auto robotLine = math::Droite3D(segment.p1, segment.p2);
			if (node->obtenirAngle() == 0.0f)  // ajout pour un angle egal a zero
				node->assignerAngle(0.00001f);

			const auto impactLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + segment.norm);
			const auto intersection = robotLine.intersectionDroite(impactLine);
			const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x; // 0.4 obtenu par tests

			// Intersection dans le segment = detection possible
			if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
				&& length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
			{
				const auto impactVect = intersection - node->obtenirPositionRelative();
				// Intersection dans le poteau = detection
				if (length(impactVect) <= radius)
				{
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE, "Poteau ");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE);
					return;
				}
			}
			else
			{
				// Coin dans le poteau = detection
				const auto impactVect = node->obtenirPositionRelative() - segment.p1;
				if (length(impactVect) <= radius)
				{
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE, "Poteau");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE);
					return;
				}
			}
		}

		for (const auto& segment : segRight[j])
		{
			const auto robotLine = math::Droite3D(segment.p1, segment.p2);
			if (node->obtenirAngle() == 0.0f)  // ajout pour un angle egal a zero
				node->assignerAngle(0.00001f);

			const auto impactLine = math::Droite3D(node->obtenirPositionRelative(), node->obtenirPositionRelative() + segment.norm);
			const auto intersection = robotLine.intersectionDroite(impactLine);
			const auto radius = (utilitaire::calculerCylindreEnglobant(*node->getModele()).rayon + 0.4) * node->getScale().x; // 0.4 obtenu par tests

			// Intersection dans le segment = detection possible
			if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
				&& length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
			{
				const auto impactVect = intersection - node->obtenirPositionRelative();
				// Intersection dans le poteau = detection
				if (length(impactVect) <= radius)
				{
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE, "Poteau");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE);
					return;
				}
			}
			else
			{
				// Coin dans le poteau = detection
				const auto impactVect = node->obtenirPositionRelative() - segment.p1;
				if (length(impactVect) <= radius)
				{
					Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE, "Poteau");
					_robot->setLastDetection(time(0));
					_robot->objectDetected(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE);
					return;
				}
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
	computeCollision(node);
	if (node->estAffiche() && difftime(time(0), _robot->getLastDetection()) > 1)
	{
		computeDetection(node);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void CollisionTool::computeCollision(NoeudMur* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::computeCollision(NoeudMur* node)
{
	int i = 0;
	for (const auto& segment : segments)
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
			|| abs(m1) >= abs(m2) - 0.0001))
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
/// @fn virtual void CollisionTool::computeDetection(NoeudMur* node)
///
/// Implémentation du visiteur CollisionTool pour un noeud de type
/// NoeudMur.
///
/// @param[in] node : Le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTool::computeDetection(NoeudMur* node)
{
	for (int j = 0; j < 2; j++)
	{
		for (const auto& segment : segCenter[j])
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
				|| abs(m1) >= abs(m2) - 0.0001))
			{
				Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE, "Mur");
				_robot->setLastDetection(time(0));
				_robot->objectDetected(j == 0 ? Debug::CAPTEUR_CENTRE_DANGER : Debug::CAPTEUR_CENTRE_SAFE);
				return;
			}
		}

		for (const auto& segment : segLeft[j])
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
				|| abs(m1) >= abs(m2) - 0.0001))
			{
				Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE, "Mur");
				_robot->setLastDetection(time(0));
				_robot->objectDetected(j == 0 ? Debug::CAPTEUR_GAUCHE_DANGER : Debug::CAPTEUR_GAUCHE_SAFE);
				return;
			}
		}

		for (const auto& segment : segRight[j])
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
				|| abs(m1) >= abs(m2) - 0.0001))
			{
				Debug::getInstance()->printMessage(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE, "Mur");
				_robot->setLastDetection(time(0));
				_robot->objectDetected(j == 0 ? Debug::CAPTEUR_DROIT_DANGER : Debug::CAPTEUR_DROIT_SAFE);
				return;
			}
		}
	}
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
