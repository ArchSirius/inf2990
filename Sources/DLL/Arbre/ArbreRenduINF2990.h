///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "utilitaire.h"
#include "BoiteEnvironnement.h"



#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par défaut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu à son état initial.
   void initialiser();
   void reinitialiser();

	/// La chaîne représentant le type des araignées.
   static const std::string NOM_ARAIGNEE;
	/// La chaîne représentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;
   /// La chaîne représentant le type du robot.
   static const std::string NOM_ROBOT;
   /// La chaîne représentant le type de la table.
   static const std::string NOM_TABLE;
   /// La chaîne représentant le type du cylindre.
   static const std::string NOM_CYLINDRE;
   /// La chaîne représentant le type du mur.
   static const std::string NOM_MUR;

   /// La chaîne représentant le type du mur.
   static const std::string NOM_LIGNE;

   /// La chaîne représentant le spawn point
   static const std::string NOM_DEPART;
   static const std::string NOM_SEGMENT;

};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
