////////////////////////////////////////////////////////////////////////////////////
/// @file CenterToolTest.cpp
/// @author INF2990-A15-01
/// @date 2015-11-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "CenterToolTest.h"
#include <memory>
#include <vector>
#include "NoeudCylindre.h"
#include "ArbreRenduINF2990.h"
#include "../Application/Visitor/CenterTool.h"
#include "utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CenterToolTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void CenterToolTest::setUp()
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
void CenterToolTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CenterToolTest::tearDown()
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
void CenterToolTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CenterToolTest::testCenter()
///
/// Cas de test: centre géométrique de plusieurs objets
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CenterToolTest::testCenter()
{
	std::vector <NoeudCylindre> noeuds;
	for (int i = 0; i < 5; i++)
		noeuds.push_back(NoeudCylindre(ArbreRenduINF2990::NOM_CYLINDRE));

	noeuds.at(0).assignerPositionInitiale(glm::dvec3(0.0, 0.0, 0.0));
	noeuds.at(1).assignerPositionInitiale(glm::dvec3(-2.0, 5.0, 1.0));
	noeuds.at(2).assignerPositionInitiale(glm::dvec3(6.0, -4.0, 2.0));
	noeuds.at(3).assignerPositionInitiale(glm::dvec3(-4.0, -4.0, 3.0));
	noeuds.at(4).assignerPositionInitiale(glm::dvec3(12.0, 0.0, 4.0));
	const auto th = glm::dvec3(2.4, -0.6, 2.0);
	auto tool = CenterTool();

	// Premier test : aucun noeud
	auto center = tool.getCenter();
	CPPUNIT_ASSERT(center == glm::dvec3(0.0, 0.0, 0.0));

	// Second test : noeud non sélectionnés
	for (auto& noeud : noeuds)
		noeud.accept(tool);
	center = tool.getCenter();
	CPPUNIT_ASSERT(center == glm::dvec3(0.0, 0.0, 0.0));

	// Troisième test : centre des noeuds
	for (auto& noeud : noeuds)
	{
		noeud.assignerSelection(true);
		noeud.accept(tool);
	}
	center = tool.getCenter();
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(center.x, th.x - utilitaire::EPSILON, th.x + utilitaire::EPSILON));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(center.y, th.y - utilitaire::EPSILON, th.y + utilitaire::EPSILON));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(center.z, th.z - utilitaire::EPSILON, th.z + utilitaire::EPSILON));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
