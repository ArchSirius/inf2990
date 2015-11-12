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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: présence d'un noeud sur la table
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

	// Troisième test : cas limite où une partie du cylindre dépasse de la table
	position.x = -57.0;
	noeud->assignerPositionRelative(position);
	CPPUNIT_ASSERT(!facade->isOnTable(noeud));

	facade->obtenirArbreRenduINF2990()->reinitialiser();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
