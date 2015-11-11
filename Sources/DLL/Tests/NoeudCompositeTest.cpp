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
#include "NoeudMur.h"
#include "NoeudRobot.h"
#include "NoeudConeCube.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	composite = std::make_unique<NoeudComposite>(ArbreRenduINF2990::NOM_TABLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{
	composite->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testObtenirNombreEnfants()
///
/// Cas de test: vider le noeud composite (supprimer tous ses enfants)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testObtenirNombreEnfants()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudMur>(ArbreRenduINF2990::NOM_MUR);
	auto n3 = std::make_unique<NoeudConeCube>(ArbreRenduINF2990::NOM_CONECUBE);
	auto n4 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n5 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);

	auto ptr1 = n1.get();
	auto ptr2 = n2.get();
	auto ptr3 = n3.get();

	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n2));
	composite->ajouter(std::move(n3));


	// 1ier test : on vérifie le nombre d'enfants 
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 3);

	composite->ajouter(std::move(n4));
	composite->ajouter(std::move(n5));
	
	// 2ieme test : on vérifie le nombre d'enfants aprés l'ajout
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 5);

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
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacer()
///
/// Cas de test: Efface un noeud qui est un enfant ou qui est contenu dans un des
/// enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacer()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudMur>(ArbreRenduINF2990::NOM_MUR);
	auto n3 = std::make_unique<NoeudConeCube>(ArbreRenduINF2990::NOM_CONECUBE);

	auto ptr1 = n1.get();
	auto ptr2 = n2.get();
	auto ptr3 = n3.get();

	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n2));
	composite->ajouter(std::move(n3));

	composite->effacer(ptr1);

	// 1ier test : on vérifie le nombre d'enfants aprés avoir effacer un seul enfant
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 2);

	// 2ieme test : le noeud effacé n'est pas trouvé
	CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_CYLINDRE) != ptr1);

	// 3ieme test : on vérifie le nombre d'enfants aprés avoir effacer un deuxieme enfant
	composite->effacer(ptr2);
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 1);

	// 4ieme test : on vérifie le nombre d'enfants aprés avoir effacer tous les enfants
	composite->effacer(ptr3);
	CPPUNIT_ASSERT(composite->obtenirNombreEnfants() == 0);

	// 5ieme test : le noeud effacé n'est pas trouvé
	CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_ROBOT) != ptr3);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacerSelection()
///
/// Cas de test: effacer les noeuds enfants sélectionnés
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{

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

	// Troisième test : le bon enfant
	CPPUNIT_ASSERT(composite->chercher(ArbreRenduINF2990::NOM_CYLINDRE) == ptr);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::selectionnerTout()
///
/// Cas de test: selectionner tous les enfants
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSelectionnerTout()
{
	auto n1 = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	auto n2 = std::make_unique<NoeudMur>(ArbreRenduINF2990::NOM_MUR);
	auto n3 = std::make_unique<NoeudConeCube>(ArbreRenduINF2990::NOM_CONECUBE);
	n3->assignerEstSelectionnable(false);

	auto ptr1 = n1.get();
	auto ptr2 = n2.get();
	auto ptr3 = n3.get();

	composite->ajouter(std::move(n1));
	composite->ajouter(std::move(n2));
	composite->ajouter(std::move(n3));

	composite->selectionnerTout();

	// tests : on vérifie que tous les noeuds sont selectionnés
	CPPUNIT_ASSERT(ptr1->selectionExiste() == true);
	CPPUNIT_ASSERT(ptr2->selectionExiste() == true);
	CPPUNIT_ASSERT(ptr3->selectionExiste() == false);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
