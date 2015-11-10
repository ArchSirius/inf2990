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
///        m�thodes de la classe Utilitaire
///
/// @author INF2990-A15-09
/// @date 2015-11-09
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
	CPPUNIT_TEST(testRad2deg);
	CPPUNIT_TEST(testDeg2rad);
	CPPUNIT_TEST(testEgalZero);
	CPPUNIT_TEST(testIntervalle);
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

	/// Cas de test: Pour convertir les angles de radians en degr�s.
	void testRad2deg();

	/// Cas de test: Pour convertir les angles de degr�s en radians.
	void testDeg2rad();

	/// Cas de test: Fonction pour savoir si un double est �gal � z�ro.
	void testEgalZero();

	/// Cas de test: Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
	void testIntervalle();
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
