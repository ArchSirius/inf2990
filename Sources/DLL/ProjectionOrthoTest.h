////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// 
/// @date 2015-11-01
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONTEST_H
#define _TESTS_PROJECTIONTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class ProjectionOrtho;

#include"ProjectionOrtho.h"

#define xMinClotureTest 0
#define xMaxClotureTest 300
#define yMinClotureTest 0
#define yMaxClotureTest 150

#define xMinFenetreTest -100
#define xMaxFenetreTest +100
#define yMinFenetreTest -50
#define yMaxFenetreTest +50

#define zAvantTest 0.2
#define zArriereTest 4

#define zoomInMaxTest 0.1
#define zoomOutMaxTest 3

#define incrementZoomTest 0.1


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
	CPPUNIT_TEST(testZoomOut);
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
	void testZoomOut();

private:
	vue::ProjectionOrtho* projectionOrthoTest_;
};

#endif // _TESTS_NOEUDABSTRAITTEST_H
///////////////////////////////////////////////////////////////////////////////
