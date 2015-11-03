////////////////////////////////////////////////////////////////////////////////////
/// @file Droite3DTest.h
/// 
/// @date 2015-11-01
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////
/*
#ifndef _TESTS_Droite3DTEST_H
#define _TESTS_Droite3DTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

#include "Droite3D.h"
#include "glm\glm.hpp"


//class Droite3D;


//#define pointDroite_ = (0.0, 1.0, 2.0);
/// @f$ (a, b, c) @f$
//#define direction_ = (0.0, 1.0, 2.0);


///////////////////////////////////////////////////////////////////////////
/// @class Droite3DTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Droite3D
///
///////////////////////////////////////////////////////////////////////////
class Droite3DTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( Droite3DTest );
	CPPUNIT_TEST(intersectionTest);
	CPPUNIT_TEST(intersectionSegmentTest);
	CPPUNIT_TEST(distancePointTest);
	CPPUNIT_TEST(perpendiculaireDroiteTEst);
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

	/// Cas de test:
	void intersectionTest();
	void intersectionSegmentTest();
	void distancePointTest();
	void perpendiculaireDroiteTEst();


private:
	math::Droite3D* droite3d_;
	const glm::dvec3& point1;
	const glm::dvec3& point2;
	
};

#endif */
///////////////////////////////////////////////////////////////////////////////