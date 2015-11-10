////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// 
/// @date 2015-11-01
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TEST_PROJECTIONORTHOTESTS_H
#define _TEST_PROJECTIONORTHOTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include "ProjectionOrtho.h"
#include "VueOrtho.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ProjectionOrtho
///
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProjectionOrthoTest);
	CPPUNIT_TEST(testZoomIn);
	CPPUNIT_TEST(testZoomOut);
	CPPUNIT_TEST(testTranslateXY);
	CPPUNIT_TEST(testTranslateCoordCloture);
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
	void testZoomIn();
	void testZoomOut();
	void testTranslateXY();
	void testTranslateCoordCloture();

private:

	vue::ProjectionOrtho* projectionOrthoTest_;
	int xMinClotureTest_ = 0;
	int xMaxClotureTest_ = 300;
	int yMinClotureTest_ = 0;
	int yMaxClotureTest_ = 150;

	double xMinFenetreTest_ = -100.0;
	double xMaxFenetreTest_ = +100;
	double yMinFenetreTest_ = -50.0;
	double yMaxFenetreTest_ = 50.0;
	double zAvantTest_ = 0.2;
	double zArriereTest_ = 4.0;
	double zoomInMaxTest_ = 0.1;
	double zoomOutMaxTest_ = 3.0;;
	double zoomTest_ = 0.1;
	double incrementZoomTest_ = 0.1;

};

#endif 
///////////////////////////////////////////////////////////////////////////////
