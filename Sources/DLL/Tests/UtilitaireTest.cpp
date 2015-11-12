////////////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "UtilitaireTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(UtilitaireTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::setUp()
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
void UtilitaireTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::tearDown()
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
void UtilitaireTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testRad2deg()
///
/// Cas de test: Pour convertir les angles de radians en degr�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testRad2deg()
{
	// Premier test : cas nul
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::RAD_TO_DEG(0.0), 0.0 - utilitaire::EPSILON, 0.0 + utilitaire::EPSILON));

	// Second test : cas positif
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::RAD_TO_DEG(utilitaire::PI / 2.0), 90.0 - utilitaire::EPSILON, 90.0 + utilitaire::EPSILON));

	// Troisi�me test : cas n�gatif
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::RAD_TO_DEG(-utilitaire::PI / 2.0), -90.0 - utilitaire::EPSILON, -90.0 + utilitaire::EPSILON));

	// Quatri�me test : cas large
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::RAD_TO_DEG(13.0 * utilitaire::PI), 2340.0 - utilitaire::EPSILON, 2340.0 + utilitaire::EPSILON));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testDeg2rad()
///
/// Cas de test: Pour convertir les angles de degr�s en radians.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testDeg2rad()
{
	// Premier test : cas nul
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::DEG_TO_RAD(0.0), 0.0 - utilitaire::EPSILON, 0.0 + utilitaire::EPSILON));

	// Second test : cas positif
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::DEG_TO_RAD(90.0), utilitaire::PI / 2.0 - utilitaire::EPSILON, utilitaire::PI / 2.0 + utilitaire::EPSILON));

	// Troisi�me test : cas n�gatif
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::DEG_TO_RAD(-90.0), -utilitaire::PI / 2.0 - utilitaire::EPSILON, -utilitaire::PI / 2.0 + utilitaire::EPSILON));

	// Quatri�me test : cas large
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(utilitaire::DEG_TO_RAD(2340.0), 13.0 * utilitaire::PI - utilitaire::EPSILON, 13.0 * utilitaire::PI + utilitaire::EPSILON));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testEgalZero()
///
/// Cas de test: Fonction pour savoir si un double est �gal � z�ro.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testEgalZero()
{
	// Premier test : cas nul
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(0.0));

	// Second test : cas faux
	CPPUNIT_ASSERT(!utilitaire::EGAL_ZERO(1.0));

	// Troisi�me test : cas interm�diaire
	CPPUNIT_ASSERT(!utilitaire::EGAL_ZERO(0.0001));

	// Quatri�me test : cas limite
	CPPUNIT_ASSERT(!utilitaire::EGAL_ZERO(utilitaire::EPSILON));

	// Cinqui�me test : cas quasi-nul
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(utilitaire::EPSILON / 2.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testIntervalle()
///
/// Cas de test: Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testIntervalle()
{
	// Premier test : cas faux
	CPPUNIT_ASSERT(!utilitaire::DANS_INTERVALLE(-1.0, 0.0, 1.0));

	// Second test : cas large
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(3.6, -1.0 / 12.0, 100.0));

	// Troisi�me test : cas pr�cis
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(0.0, 0.0 - utilitaire::EPSILON, 0.0 + utilitaire::EPSILON));

	// Quatri�me test : cas singulier
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(0.0, 0.0, 0.0));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
