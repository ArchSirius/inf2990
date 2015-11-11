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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{
	projectionOrthoTest_ = new ProjectionOrtho(xMinClotureTest_, xMaxClotureTest_, yMinClotureTest_, yMaxClotureTest_,
		zAvantTest_, zArriereTest_, zoomInMaxTest_, zoomOutMaxTest_,
		incrementZoomTest_, xMinFenetreTest_, xMaxFenetreTest_,
		yMinFenetreTest_, yMaxFenetreTest_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
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
void ProjectionOrthoTest::tearDown()
{
	delete projectionOrthoTest_;
	projectionOrthoTest_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomIn()
///
/// pour tester si la fonction fait un zoom in
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomIn()
{
	double xMin, yMin, xMax, yMax;
	projectionOrthoTest_->zoomerIn(glm::ivec2(xMin, yMin), glm::ivec2(xMax, yMax));
	double zoom = projectionOrthoTest_->getZoom();

	CPPUNIT_ASSERT(zoom < zoomTest_);
	//CPPUNIT_ASSERT(zoom == (zoomTest_ - 0.01) );

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomOut()
///
/// pour tester si la fonction fait un zoom out
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomOut()
{
	double xMin, yMin, xMax, yMax;
	projectionOrthoTest_->zoomerOut(glm::ivec2(xMin, yMin), glm::ivec2(xMax, yMax));
	double zoom = projectionOrthoTest_->getZoom();

	CPPUNIT_ASSERT(zoom > zoomTest_);
	//CPPUNIT_ASSERT(zoom == (zoomTest_ + 0.01) );
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testTranslateXY()
///
/// pour tester si la fonction fait une translation par rapport aux coordonnées de fentre virtuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testTranslateXY()
{	
	
	//Avec aucune transaltion
	projectionOrthoTest_->translater(0, 0);

	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre == xMinFenetreTest_);
	CPPUNIT_ASSERT(xMaxFenetre == xMaxFenetreTest_);
	CPPUNIT_ASSERT(yMinFenetre == yMinFenetreTest_);
	CPPUNIT_ASSERT(yMaxFenetre == yMaxFenetreTest_);
	
	// translation en X positif
	double pourcentageX = 10.0/100.0;
	

	projectionOrthoTest_->translater(pourcentageX, 0.0);

	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre >= xMinFenetreTest_);
	CPPUNIT_ASSERT(xMaxFenetre >= xMaxFenetreTest_);
	CPPUNIT_ASSERT(yMinFenetre == yMinFenetreTest_);
	CPPUNIT_ASSERT(yMaxFenetre == yMaxFenetreTest_);

	double pourcentageY = -10.0 / 100.0;

	// translation en Y aprés un translate en X

	projectionOrthoTest_->translater(0.0, pourcentageY);
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	CPPUNIT_ASSERT(xMinFenetre >= xMinFenetreTest_);
	CPPUNIT_ASSERT(xMaxFenetre >= xMaxFenetreTest_);
	CPPUNIT_ASSERT(yMinFenetre <= yMinFenetreTest_);
	CPPUNIT_ASSERT(yMaxFenetre <= yMaxFenetreTest_);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testTranslateCoordCloture()
///
/// pour tester si la fonction fait une translation par rapport aux coordonnées de cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testTranslateCoordCloture()
{

	//Avec aucune transaltion
	projectionOrthoTest_->translater( glm::ivec2(0.0 , 0.0) );

	int xMinCloture, xMaxCloture, yMinCoture, yMaxCloture;
	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);

	CPPUNIT_ASSERT(xMinCloture == xMinClotureTest_);
	CPPUNIT_ASSERT(xMaxCloture == xMaxClotureTest_);
	CPPUNIT_ASSERT(yMinCoture == yMinClotureTest_);
	CPPUNIT_ASSERT(yMaxCloture == yMaxClotureTest_);

	// translation en X positif
	double pourcentageX = 10.0 / 100.0;


	projectionOrthoTest_->translater(glm::ivec2(pourcentageX, 0.0));

	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);

	CPPUNIT_ASSERT(xMinCloture >= xMinClotureTest_);
	CPPUNIT_ASSERT(xMaxCloture >= xMaxClotureTest_);
	CPPUNIT_ASSERT(yMinCoture == yMinClotureTest_);
	CPPUNIT_ASSERT(yMaxCloture == yMaxClotureTest_);

	double pourcentageY = -10.0 / 100.0;

	// translation en Y aprés un translate en X

	projectionOrthoTest_->translater(glm::ivec2(0.0, pourcentageY));
	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);

	CPPUNIT_ASSERT(xMinCloture >= xMinClotureTest_);
	CPPUNIT_ASSERT(xMaxCloture >= xMaxClotureTest_);
	CPPUNIT_ASSERT(yMinCoture <= yMinClotureTest_);
	CPPUNIT_ASSERT(yMaxCloture <= yMaxClotureTest_);

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
