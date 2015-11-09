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
///        m�thodes de la classe Droite3D
///
/// @author INF2990-A15-01
/// @date 2015-11-06
///////////////////////////////////////////////////////////////////////////
class Droite3DTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(Droite3DTest);
	CPPUNIT_TEST(testVecteur);
	CPPUNIT_TEST(testIntersection);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
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
