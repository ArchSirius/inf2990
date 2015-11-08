//////////////////////////////////////////////////////////////////////////////
/// @file Droite3DTest.h
/// @author INF2990-A15-01
/// @date 2015-11-06
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "Droite3D.h"

///////////////////////////////////////////////////////////////////////////
/// @class Droite3DTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Droite3D
///
/// @author INF2990-A15-01
/// @date 2015-11-06
///////////////////////////////////////////////////////////////////////////
class Droite3DTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(Droite3DTest);
	CPPUNIT_TEST(testVecteur);
	CPPUNIT_TEST(testIntersection);
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

	/// Cas de test: vecteur directeur de la droite
	void testVecteur();

	/// Cas de test: intersection entre deux droites
	void testIntersection();

private:
	/// Instance d'une droite
	std::unique_ptr<math::Droite3D> droite1, droite2;
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
