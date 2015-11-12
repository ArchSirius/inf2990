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
	projectionOrthoTest_ = new ProjectionOrtho (xMinClotureTest_, xMaxClotureTest_, yMinClotureTest_, yMaxClotureTest_,
		zAvantTest_, zArriereTest_, zoomInMaxTest_, zoomOutMaxTest_,
		incrementZoomTest_, xMinFenetreTest_, xMaxFenetreTest_,
		yMinFenetreTest_, yMaxFenetreTest_);
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
	projectionOrthoTest_->zoomerIn();
	double zoom = projectionOrthoTest_->getZoom();

	// Le zoom diminue quand on zoomIn
	CPPUNIT_ASSERT(zoom < zoomTest_);
	CPPUNIT_ASSERT(zoom == zoomTest_ - incrementZoomTest_);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomIn()
///
/// pour tester si la fonction fait un zoom in Rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomInRec()
{
	projectionOrthoTest_->zoomerIn(glm::ivec2(-81, -60), glm::ivec2(60, 84));
	double zoom = projectionOrthoTest_->getZoom();

	int xMinCloture, xMaxCloture, yMinCoture, yMaxCloture;
	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);

	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	// la cloture garde les m�mes proportions que la cl�ture de base
	CPPUNIT_ASSERT((xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture) == (xMaxClotureTest_ - xMinClotureTest_) / (yMaxClotureTest_ - yMinClotureTest_));

	//un bon rapport d'Aspect
	CPPUNIT_ASSERT((xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture) == (xMaxFenetre - xMinFenetre) / (yMaxFenetre - yMinFenetre));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testRedimentionnementDeLaFenetre()
///
/// pour tester si la fonction fait le bon redimentionnement de la fen�tre 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testRedimentionnementDeLaFenetre()
{
	projectionOrthoTest_->redimensionnerFenetre(glm::ivec2(-120, -150), (glm::ivec2(80, -50)));

	int xMinCloture, xMaxCloture, yMinCoture, yMaxCloture;
	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);

	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);

	//rapport respect�
	CPPUNIT_ASSERT((xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture) == (xMaxFenetre - xMinFenetre) / (yMaxFenetre - yMinFenetre));

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
