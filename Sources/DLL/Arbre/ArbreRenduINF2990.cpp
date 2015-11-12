///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"
#include "Noeuds/NoeudRobot.h"


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La chaîne représentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La chaîne représentant le type de la table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La chaîne représentant le type du cylindre.
const std::string ArbreRenduINF2990::NOM_CYLINDRE{ "cylindre" };
/// La chaîne représentant le type du mur.
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };

/// La chaîne représentant le type du mur.
const std::string ArbreRenduINF2990::NOM_SEGMENT{ "segment" };

/// La chaîne représentant le type du mur.
const std::string ArbreRenduINF2990::NOM_LIGNE{ "ligne" };

/// La chaîne représentant le spawn point
const std::string ArbreRenduINF2990::NOM_DEPART{ "depart" };


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Ligne noire (entité logique)
	ajouterUsine(NOM_LIGNE, new UsineNoeud<NoeudLigneComposite>{ NOM_LIGNE, std::string{ "" } });

	// Segment de ligne (concret)
	ajouterUsine(NOM_SEGMENT, new UsineNoeud<NoeudSegmentConcret>{ NOM_SEGMENT, std::string{ "media/ligne.obj" } });

	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_ROBOT, new UsineNoeud<NoeudRobot>{ NOM_ROBOT, std::string{ "media/robot.obj" } });

	///Ajout usine Noeud table, cylindre, mur, etc.
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "media/Table_1.obj" } });
	ajouterUsine(NOM_CYLINDRE, new UsineNoeud<NoeudCylindre>{ NOM_CYLINDRE, std::string{ "media/Cylindre_1.obj" } });
	ajouterUsine(NOM_MUR, new UsineNoeud<NoeudMur>{ NOM_MUR, std::string{ "media/MUR_1.obj" } });

	ajouterUsine(NOM_DEPART, new UsineNoeud<NoeudDepart>{ NOM_DEPART, std::string{ "media/depart.obj" } });

}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	reinitialiser();
	chercher(NOM_TABLE)->ajouter(creerNoeud(NOM_DEPART));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::reinitialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::reinitialiser()
{
	// On vide l'arbre
	vider();

	auto noeudTable = creerNoeud(NOM_TABLE);

	auto noeudMur1 = creerNoeud(NOM_MUR);
	auto noeudMur2 = creerNoeud(NOM_MUR);
	auto noeudMur3 = creerNoeud(NOM_MUR);
	auto noeudMur4 = creerNoeud(NOM_MUR);

	noeudMur1->assignerAffiche(false);
	noeudMur1->assignerEstSelectionnable(false);
	noeudMur1->assignerEstEnregistrable(false);
	noeudMur1->assignerPositionRelative(glm::dvec3(-8.0, 25.0, 5.0));
	//p1_ (glm::dev3(-58.0, 24.5, 5.0)
	//p2_ (glm::dev3( 42.0, 24.5, 5.0)
	noeudMur1->setScale(glm::fvec3(1.0, 64.0, 1.0));
	noeudMur1->assignerAngle(90.00001f);
	noeudMur1->updatePos();

	noeudMur2->assignerAffiche(false);
	noeudMur2->assignerEstSelectionnable(false);
	noeudMur2->assignerEstEnregistrable(false);
	noeudMur2->assignerPositionRelative(glm::dvec3(43.0, -0.25, 5.0));
	//p1_ (glm::dev3(42.0, 24.5, 5.0)
	//p2_ (glm::dev3(42.0,-25.5, 5.0)
	noeudMur2->setScale(glm::fvec3(1.0, 32.0, 1.0));
	noeudMur2->assignerAngle(0.00001f);
	noeudMur2->updatePos();

	noeudMur3->assignerAffiche(false);
	noeudMur3->assignerEstSelectionnable(false);
	noeudMur3->assignerEstEnregistrable(false);
	noeudMur3->assignerPositionRelative(glm::dvec3(-8.0, -27.0, 5.0));
	//p1_ (glm::dev3( 42.0,-25.5, 5.0)
	//p2_ (glm::dev3(-58.0,-25.5, 5.0)
	noeudMur3->setScale(glm::fvec3(1.0, 64.0, 1.0));
	noeudMur3->assignerAngle(90.00001f);
	noeudMur3->updatePos();

	noeudMur4->assignerAffiche(false);
	noeudMur4->assignerEstSelectionnable(false);
	noeudMur4->assignerEstEnregistrable(false);
	noeudMur4->assignerPositionRelative(glm::dvec3(-59.0, -0.25, 5.0));
	//p1_ (glm::dev3(-58.0,-25.5, 5.0)
	//p2_ (glm::dev3(-58.0, 24.5, 5.0)
	noeudMur4->setScale(glm::fvec3(1.0, 32.0, 1.0));
	noeudMur4->assignerAngle(0.00001f);
	noeudMur4->updatePos();

	noeudTable->ajouter(std::move(noeudMur1));
	noeudTable->ajouter(std::move(noeudMur2));
	noeudTable->ajouter(std::move(noeudMur3));
	noeudTable->ajouter(std::move(noeudMur4));

	ajouter(std::move(noeudTable));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
