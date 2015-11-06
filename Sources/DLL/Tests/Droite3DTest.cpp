////////////////////////////////////////////////////////////////////////////////////
/// @file Droite3DTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-06
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Droite3DTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(Droite3DTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void Droite3DTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Droite3DTest::setUp()
{
	droite1 = std::make_unique<math::Droite3D>(glm::dvec3(1.0, 2.0, 0.0), glm::dvec3(5.0, 7.0, 0.0));
	droite2 = std::make_unique<math::Droite3D>(glm::dvec3(3.0, 3.0, 0.0), glm::dvec3(4.0, 5.0, 0.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Droite3DTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Droite3DTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Droite3DTest::testVecteur()
///
/// Cas de test: vecteur directeur de la droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Droite3DTest::testVecteur()
{
	// Premier test : droite1
	auto vecteur = droite1->lireVecteur();
	CPPUNIT_ASSERT(vecteur == glm::dvec3(4.0, 5.0, 0.0));

	// Second test : droite2
	vecteur = droite2->lireVecteur();
	CPPUNIT_ASSERT(vecteur == glm::dvec3(1.0, 2.0, 0.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Droite3DTest::testIntersection()
///
/// Cas de test: intersection entre deux droites
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Droite3DTest::testIntersection()
{
	const auto intersection = droite1->intersectionDroite(*droite2);
	CPPUNIT_ASSERT(intersection == glm::dvec3(5.0, 7.0, 0.0));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
