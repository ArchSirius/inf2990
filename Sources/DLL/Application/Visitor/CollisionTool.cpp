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
	/*
	1. Calculer les 4 segments
	2. Boucler sur les segments
	3. Pour chaque segment, déterminer sa normale
	4. Déterminer l'intersection entre le segment et la normale passant par le centre
		voir http://www.softwareandfinance.com/Visual_CPP/VCPP_Intersection_Two_lines_EndPoints.html
	5. Si aucune intersection n'est trouvée, on passe
		Si une intersection est trouvée, on calcule la distance
		-> utilitaire::distancePoint
	* vérifier la possibilité si la droite entre le segment et le centre est parallèle au segment
	6. Si la distance est inférieure ou égale au rayon du cylindre, il y a collision
	
	7. Maintenant, vérifier les coins:
	8. Pour chaque coin, si la distance entre le coin et le centre est inférieure ou égale au rayon, il y a collision

	9. S'il y a collision, appliquer le rebond
	*/
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
