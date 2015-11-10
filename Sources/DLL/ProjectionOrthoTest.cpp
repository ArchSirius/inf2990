////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// 
/// @date 2015-11-01
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////

#include "projectionOrthoTest.h"
#include "Utilitaire.h"

using namespace vue;

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectionOrthoTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
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
void ProjectionOrthoTest::setUp()
{
	projectionOrthoTest_ = new ProjectionOrtho(xMinClotureTest, xMaxClotureTest, yMinClotureTest, yMaxClotureTest,
		zAvantTest, zArriereTest, zoomInMaxTest, zoomOutMaxTest,
		incrementZoomTest, xMinFenetreTest, xMaxFenetreTest,
		yMinFenetreTest, yMaxFenetreTest);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
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
void ProjectionOrthoTest::tearDown()
{
		

}

////////////////////////////////////////////////////////////////////////
///

///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomIn()
{
	/*double xMin, yMin, xMax, yMax;
	projectionOrthoTest_->zoomerIn(glm::ivec2(xMin, yMin), glm::ivec2(xMax, yMax));
	double zoom = projectionOrthoTest_->getZoom();

	CPPUNIT_ASSERT(zoom > zoomTest);*/

}

////////////////////////////////////////////////////////////////////////
///

///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomOut()
{
	
}

////////////////////////////////////////////////////////////////////////
///

///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testTranslate()
{	
	
	//Avec aucune transaltion
	projectionOrthoTest_->translater(0, 0);

	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre == xMinFenetreTest);
	CPPUNIT_ASSERT(xMaxFenetre == xMaxFenetreTest);
	CPPUNIT_ASSERT(yMinFenetre == yMinFenetreTest);
	CPPUNIT_ASSERT(yMaxFenetre == yMaxFenetreTest);
	/*
	// translation en X positif
	double pourcentage = 10 / 100;
	projectionOrthoTest_->translater(pourcentage, 0);

	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre < xMinFenetreTest);
	CPPUNIT_ASSERT(xMaxFenetre < xMaxFenetreTest);
	CPPUNIT_ASSERT(yMinFenetre == yMinFenetreTest);
	CPPUNIT_ASSERT(yMaxFenetre == yMaxFenetreTest);


	// Translation Y positif apr�s la transaltion en X
	projectionOrthoTest_->translater(0, pourcentage);
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre > xMinFenetreTest);
	CPPUNIT_ASSERT(xMaxFenetre > xMaxFenetreTest);
	CPPUNIT_ASSERT(yMinFenetre > yMinFenetreTest);
	CPPUNIT_ASSERT(yMaxFenetre > yMaxFenetreTest);*/

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
