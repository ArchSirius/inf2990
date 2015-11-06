//////////////////////////////////////////////////////////////////////////////
/// @file CollisionToolTest.h
/// @author INF2990-A15-01
/// @date 2015-11-06
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "../Application/Visitor/CollisionTool.h"

///////////////////////////////////////////////////////////////////////////
/// @class CollisionToolTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe CollisionTool
///
/// @author INF2990-A15-01
/// @date 2015-11-06
///////////////////////////////////////////////////////////////////////////
class CollisionToolTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(CollisionToolTest);
	CPPUNIT_TEST(testRotate);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: rotation d'un point autour d'un autre
	void testRotate();

	/// Cas de test: longueur d'un vecteur
	void testLength();
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
