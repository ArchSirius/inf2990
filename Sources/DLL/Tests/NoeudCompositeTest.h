//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author INF2990-A15-01
/// @date 2015-11-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "NoeudComposite.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCompositeTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudComposite
///
/// @author INF2990-A15-01
/// @date 2015-11-10
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST(testVider);
	CPPUNIT_TEST(testEffacerSelection);
	CPPUNIT_TEST(testChercher);
	CPPUNIT_TEST(testAjouter);
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

	/// Cas de test: vider le noeud composite (supprimer tous ses enfants)
	void testVider();

	/// Cas de test: effacer les noeuds enfants sélectionnés
	void testEffacerSelection();

	/// Cas de test: rechercher un noeud enfant
	void testChercher();

	/// Cas de test: ajouter un noeud enfant
	void testAjouter();

private:
	/// Instance d'un noeud composite
	std::unique_ptr<NoeudComposite> composite;
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
