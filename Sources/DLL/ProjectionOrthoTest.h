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
///        m�thodes de la classe ProjectionOrtho
///
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProjectionOrthoTest);
	CPPUNIT_TEST(testZoomIn);
	CPPUNIT_TEST(testZoomInRec);
	CPPUNIT_TEST(testRedimentionnementDeLaFenetre);
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

	/// Cas de test:
	void testZoomIn();
	void testZoomInRec();
	void testRedimentionnementDeLaFenetre();

private:
	vue::ProjectionOrtho *projectionOrthoTest_;

	int xMinClotureTest_ = -100;
	int xMaxClotureTest_ = 100;
	int yMinClotureTest_ = -50;
	int yMaxClotureTest_ = 50;

	double xMinFenetreTest_ = -100.0;
	double xMaxFenetreTest_ = +100;
	double yMinFenetreTest_ = -50.0;
	double yMaxFenetreTest_ = 50.0;
	double zAvantTest_ = 0.2;
	double zArriereTest_ = 4.0;
	double zoomInMaxTest_ = 0.03;
	double zoomOutMaxTest_ = 0.5;
	double zoomTest_ = 0.1;
	double incrementZoomTest_ = 0.01;

};

#endif 
///////////////////////////////////////////////////////////////////////////////
