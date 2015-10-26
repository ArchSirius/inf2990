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
	const glm::dvec3 offset = glm::dvec3(0.0, 15.0, 0.0);
	auto hitbox = utilitaire::calculerBoiteEnglobante(*_robot->getModele());

	_p1.x = hitbox.coinMin.x * scale.x + _robot->obtenirPositionRelative().x + offset.x;
	_p1.y = hitbox.coinMin.y * scale.y + _robot->obtenirPositionRelative().y + offset.y;
	_p1.z = hitbox.coinMin.z * scale.z + _robot->obtenirPositionRelative().z + offset.z;
	_p2.x = hitbox.coinMin.x * scale.x + _robot->obtenirPositionRelative().x + offset.x;
	_p2.y = hitbox.coinMax.y * scale.y + _robot->obtenirPositionRelative().y + offset.y;
	_p2.z = hitbox.coinMin.z * scale.z + _robot->obtenirPositionRelative().z + offset.z;
	_p3.x = hitbox.coinMax.x * scale.x + _robot->obtenirPositionRelative().x + offset.x;
	_p3.y = hitbox.coinMax.x * scale.y + _robot->obtenirPositionRelative().y + offset.y;
	_p3.z = hitbox.coinMax.x * scale.z + _robot->obtenirPositionRelative().z + offset.z;
	_p4.x = hitbox.coinMax.x * scale.x + _robot->obtenirPositionRelative().x + offset.x;
	_p4.y = hitbox.coinMin.y * scale.y + _robot->obtenirPositionRelative().y + offset.y;
	_p4.z = hitbox.coinMin.z * scale.z + _robot->obtenirPositionRelative().z + offset.z;

	rotate(_p1, _robot->obtenirAngle() * static_cast<float>(utilitaire::PI) / 180.0f, _robot->obtenirPositionRelative());
	rotate(_p2, _robot->obtenirAngle() * static_cast<float>(utilitaire::PI) / 180.0f, _robot->obtenirPositionRelative());
	rotate(_p3, _robot->obtenirAngle() * static_cast<float>(utilitaire::PI) / 180.0f, _robot->obtenirPositionRelative());
	rotate(_p4, _robot->obtenirAngle() * static_cast<float>(utilitaire::PI) / 180.0f, _robot->obtenirPositionRelative());

	//glDisable(GL_DEPTH_TEST);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d( 10.0,  10.0, 5.0);
	glVertex3d(-10.0,  10.0, 5.0);
	glVertex3d(-10.0, -10.0, 5.0);
	glVertex3d( 10.0, -10.0, 5.0);
	/*
	glVertex3d(_p1.x, _p1.y, _p1.z);
	glVertex3d(_p2.x, _p2.y, _p2.z);
	glVertex3d(_p3.x, _p3.y, _p3.z);
	glVertex3d(_p4.x, _p4.y, _p4.z);
	*/
	glEnd();
	//glEnable(GL_DEPTH_TEST);

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
		auto test1 = length(intersection - segment.p1);
		auto test2 = length(segment.p2 - segment.p1);
		auto test3 = length(intersection - segment.p2);
		auto test4 = length(segment.p2 - segment.p1);
		if (length(intersection - segment.p1) <= length(segment.p2 - segment.p1)
			&& length(intersection - segment.p2) <= length(segment.p2 - segment.p1))
		{
			glm::dvec3 impactVect = intersection - node->obtenirPositionRelative();
			// Intersection dans le poteau = collision
			if (length(impactVect) <= radius)
			{
				Debug::getInstance()->printMessage(Debug::TEST, "Collision frontale!");
				std::cout << length(node->obtenirPositionRelative() - intersection) << std::endl;
				std::cout << "Cylindre: " << node->obtenirPositionRelative().y << std::endl;
				std::cout << "Robot: " << _robot->obtenirPositionRelative().y << std::endl;
				doCollision(atan2(impactVect.y, impactVect.x));
				return;
			}
		}
		else
		{
			// Coin dans le poteau = collision
			glm::dvec3 impactVect = node->obtenirPositionRelative() - segment.p1;
			if (length(impactVect) <= radius)
			{
				doCollision(atan2(impactVect.y, impactVect.x));
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
