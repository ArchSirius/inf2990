//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author INF2990-A15-01
/// @date 2015-11-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Utilitaire
///
/// @author INF2990-A15-09
/// @date 2015-11-09
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
	CPPUNIT_TEST(testRad2deg);
	CPPUNIT_TEST(testDeg2rad);
	CPPUNIT_TEST(testEgalZero);
	CPPUNIT_TEST(testIntervalle);
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

	/// Cas de test: Pour convertir les angles de radians en degrés.
	void testRad2deg();

	/// Cas de test: Pour convertir les angles de degrés en radians.
	void testDeg2rad();

	/// Cas de test: Fonction pour savoir si un double est égal à zéro.
	void testEgalZero();

	/// Cas de test: Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
	void testIntervalle();
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
