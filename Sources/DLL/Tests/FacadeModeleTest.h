//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.h
/// @author INF2990-A15-01
/// @date 2015-11-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "FacadeModele.h"

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModeleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe FacadeModele
///
/// @author INF2990-A15-01
/// @date 2015-11-09
///////////////////////////////////////////////////////////////////////////
class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(FacadeModeleTest);
	CPPUNIT_TEST(isOnTableTest);
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

	/// Cas de test: présence d'un noeud sur la table
	void isOnTableTest();

private:
	/// Instance d'une droite
	FacadeModele* facade;
	
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
