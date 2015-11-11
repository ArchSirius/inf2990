////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudAbstraitTest.h"
#include "NoeudConeCube.h"
#include "NoeudCylindre.h"
#include "NoeudMur.h"
#include "NoeudSegmentConcret.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudAbstraitTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
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
void NoeudAbstraitTest::setUp()
{
	noeud = std::make_unique<NoeudConeCube>( ArbreRenduINF2990::NOM_CONECUBE );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
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
void NoeudAbstraitTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testPositionRelative()
///
/// Cas de test: �criture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testPositionRelative()
{
	// Premier test : on v�rifie que la position initiale est un vector nul
	glm::dvec3 vecteur{ noeud->obtenirPositionRelative() };
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	// On modifie la position
	noeud->assignerPositionRelative(glm::dvec3{ 2.2, 3.3, 4.4 });

	// Second test : on v�rifie que la position a �t� modifi�e
	vecteur = noeud->obtenirPositionRelative();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 2.2));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 3.3));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 4.4));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testType()
///
/// Cas de test: type de noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testType()
{
	CPPUNIT_ASSERT(noeud->obtenirType() == ArbreRenduINF2990::NOM_CONECUBE);
	CPPUNIT_ASSERT(noeud->obtenirType() != ArbreRenduINF2990::NOM_ARAIGNEE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testSelection()
///
/// Cas de test: d�finition/obtention des �tats de s�lection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testSelection()
{
	// Cas 1 : non s�lectionnable, non s�lectionn�
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 2 : non s�lectionnable, s�lectionn�
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 3 : s�lectionnable, non s�lectionn�
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 4 : non s�lectionnable, s�lectionn�
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEnfants()
{
	// On v�rifie qu'initialement, le noeud n'a pas d'enfant
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	auto nouveauNoeud = std::make_unique<NoeudConeCube>( ArbreRenduINF2990::NOM_CONECUBE );
	bool ajout{ noeud->ajouter(std::move(nouveauNoeud)) };

	// L'ajout devrait avoir �chou� puisqu'il s'agit d'un noeud abstrait...
	CPPUNIT_ASSERT(ajout == false);

	// Assurons-nous que le noeud ne poss�de pas d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testScale()
///
/// Cas de test: s'assurer que les restrictions sur l'�chelle sont respect�es
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testScale()
{
	auto defaultScale = glm::fvec3(1.0f, 1.0f, 1.0f);
	const auto targetScale = glm::fvec3(2.0f, 3.0f, 2.5f);

	// Cas 1 : poteau
	auto poteau = std::make_unique<NoeudCylindre>(ArbreRenduINF2990::NOM_CYLINDRE);
	CPPUNIT_ASSERT(poteau->getScale() == defaultScale);
	poteau->setScale(targetScale);
	CPPUNIT_ASSERT(poteau->getScale().x == targetScale.x);
	CPPUNIT_ASSERT(poteau->getScale().y == targetScale.x);
	CPPUNIT_ASSERT(poteau->getScale().z == defaultScale.z);

	// Cas 2 : mur
	auto mur = std::make_unique<NoeudMur>(ArbreRenduINF2990::NOM_MUR);
	CPPUNIT_ASSERT(mur->getScale() == defaultScale);
	mur->setScale(targetScale);
	CPPUNIT_ASSERT(mur->getScale().x == defaultScale.x);
	CPPUNIT_ASSERT(mur->getScale().y == targetScale.y);
	CPPUNIT_ASSERT(mur->getScale().z == defaultScale.z);

	// Cas 3 : ligne (segment)
	defaultScale.x = 2.0f;
	auto ligne = std::make_unique<NoeudSegmentConcret>(ArbreRenduINF2990::NOM_SEGMENT);
	CPPUNIT_ASSERT(ligne->getScale() == defaultScale);
	ligne->setScale(targetScale);
	CPPUNIT_ASSERT(ligne->getScale().x == defaultScale.x);
	CPPUNIT_ASSERT(ligne->getScale().y == targetScale.y);
	CPPUNIT_ASSERT(ligne->getScale().z == defaultScale.z);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
