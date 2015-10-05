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
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_ROBOT, new UsineNoeud<NoeudRobot>{ NOM_ROBOT, std::string{ "media/robot.obj" } });

	///Ajout usine Noeud table, cylindre, mur, etc.
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "media/Table_1.obj" } });
	ajouterUsine(NOM_CYLINDRE, new UsineNoeud<NoeudCylindre>{ NOM_CYLINDRE, std::string{ "media/Cylindre_1.obj" } });
	ajouterUsine(NOM_MUR, new UsineNoeud<NoeudMur>{ NOM_MUR, std::string{ "media/MUR_1.obj" } });

	// Ligne noire (entité logique)
	ajouterUsine(NOM_LIGNE, new UsineNoeud<NoeudLigneComposite>{ NOM_LIGNE, std::string{""} });

	// Segment de ligne (concret)
	ajouterUsine(NOM_SEGMENT, new UsineNoeud<NoeudSegmentConcret>{ NOM_SEGMENT, std::string{ "media/ligne.obj" } });

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
	// On vide l'arbre
	vider();

	auto noeudTable = creerNoeud(NOM_TABLE);
	noeudTable->assignerEstSelectionnable(false);
	
	auto noeudDepart = creerNoeud(NOM_DEPART);
	noeudDepart->assignerEstSelectionnable(true);

	noeudTable->ajouter(std::move(noeudDepart));
	
	ajouter(std::move(noeudTable));
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
