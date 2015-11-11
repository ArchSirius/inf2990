////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "ArbreRenduINF2990.h"
#include "NoeudCylindre.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	composite = std::make_unique<NoeudComposite>(ArbreRenduINF2990::NOM_TABLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{
	composite->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testVider()
///
/// Cas de test: vider le noeud composite (supprimer tous ses enfants)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testVider()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n3 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n2));
	composite->ajouter(std::move(n3));
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 3);

	composite->vider();
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacerSelection()
///
/// Cas de test: effacer les noeuds enfants s�lectionn�s
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n3 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n4 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n5 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	n2->assignerSelection(true);
	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n3));
	composite->ajouter(std::move(n5));

	// Premier test : aucune s�lection
	composite->effacerSelection();
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 3);

	// Second test : s�lection d'un noeud
	composite->ajouter(std::move(n2));
	composite->ajouter(std::move(n4));
	composite->effacerSelection();
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 4);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// Cas de test: rechercher un noeud enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto ptr1 = n1.get();
	auto ptr2 = n2.get();
	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n2));

	CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_CYLINDRE) == ptr1);
	CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_CYLINDRE) != ptr2);

	composite->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjouter()
///
/// Cas de test: ajouter un noeud enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjouter()
{
	// Premier test : aucun enfant
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 0);

	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto ptr = n1.get();
	composite->ajouter(std::move(n1));

	// Second test : un enfant
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 1);

	// Troisi�me test : le bon enfant (voir testChercher)
	//CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_CYLINDRE) == ptr);

	composite->vider();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////