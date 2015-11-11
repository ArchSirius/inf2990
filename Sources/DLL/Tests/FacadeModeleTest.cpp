////////////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "FacadeModeleTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(FacadeModeleTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::setUp()
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
void FacadeModeleTest::setUp()
{
	facade = FacadeModele::obtenirInstance();
	facade->initialiserOpenGL(nullptr);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::tearDown()
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
void FacadeModeleTest::tearDown()
{
	facade->libererOpenGL();
	facade->libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::isOnTableTest()
///
/// Cas de test: pr�sence d'un noeud sur la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::isOnTableTest()
{
	facade->addNode(ArbreRenduINF2990::NOM_CYLINDRE);
	auto noeud = facade->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_CYLINDRE);
	auto position = noeud->obtenirPositionRelative();

	// Premier test : le cylindre est sur la table
	CPPUNIT_ASSERT(facade->isOnTable(noeud));

	// Second test : le cylindre n'est pas sur la table
	position.x = -60.0;
	noeud->assignerPositionRelative(position);
	CPPUNIT_ASSERT(!facade->isOnTable(noeud));

	// Troisi�me test : cas limite o� une partie du cylindre d�passe de la table
	position.x = -57.0;
	noeud->assignerPositionRelative(position);
	CPPUNIT_ASSERT(!facade->isOnTable(noeud));

	facade->obtenirArbreRenduINF2990()->reinitialiser();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
