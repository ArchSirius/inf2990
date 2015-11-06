////////////////////////////////////////////////////////////////////////////////////
/// @file CollisionToolTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-06
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "CollisionToolTest.h"
#include "utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CollisionToolTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionToolTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionToolTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionToolTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionToolTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionToolTest::testRotate()
///
/// Cas de test: rotation d'un point autour d'un autre
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionToolTest::testRotate()
{
	// Premier test : cas simple
	auto centre = glm::dvec3(0.0, 0.0, 0.0);
	auto point = glm::dvec3(1.0, 0.0, 0.0);

	CollisionTool::rotate(point, utilitaire::PI / 2.0, centre);
	//CPPUNIT_ASSERT(point == glm::dvec3(0.0, 1.0, 0.0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(point.x));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(point.y, 1.0 - utilitaire::EPSILON, 1.0 + utilitaire::EPSILON));

	// Second test : cas moyen
	centre = glm::dvec3(10.0, 23.0, 0.0);
	point = glm::dvec3(42.0, 13.0, 0.0);

	CollisionTool::rotate(point, 3.0 * utilitaire::PI / 2.0, centre);
	//CPPUNIT_ASSERT(point == glm::dvec3(0.0, -9.0, 0.0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(point.x));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(point.y, -9.0 - utilitaire::EPSILON, -9.0 + utilitaire::EPSILON));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionToolTest::testLength()
///
/// Cas de test: longueur d'un vecteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionToolTest::testLength()
{
	const auto vecteur = glm::dvec3(6.0, 2.0, 9.0);
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(CollisionTool::length(vecteur), 11.0 - utilitaire::EPSILON, 11.0 + utilitaire::EPSILON));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
