//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <string>
#include <memory>

// Pour le unique_ptr, beacuase MSCV
#include "Vue.h"
#include "ArbreRenduINF2990.h"

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
	class Camera;
}

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Lib�re l'instance unique de la classe.
   static void libererInstance();

   /// Cr�e un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration � partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Lib�re le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du mod�le.
   void afficher() const; 
   /// Affiche la base du contenu du mod�le.
   void afficherBase() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);

   //Deplace la camera.
   void deplacerXY(double deplacementX, double deplacementY);
   void setViewInit();
   void moveCameraMouse();

   //ZoomIN
   void zoomerIn();

   //ZoomOut
   void zoomerOut();

   // initialiser rectangle
   void initialiserRectangleElastique();

   // mettre a jour rectangle

   void mettreAJourRectangleElastique( );
 
   // terminer rectangle 
   void terminerRectangleElastique();

   glm::ivec2 getCoordinate();

   // ajuster la nouvelle fenetre
   void redimensionnerFenetre(const glm::ivec2& coinMin,
	   const glm::ivec2& coinMax);

   // Remember object position
   void doSetInitPos();

   // Translate object
   void doTranslation(float deltaX, float deltaY, float deltaZ);

   // Remember object angle
   void doSetInitAngle();

   // Rotate object
   void doRotation(float deltaX, float deltaY, float deltaZ);

   // Scale object
   void doScaling(float deltaX, float deltaY, float deltaZ);

   // Duplicate object
   void doDuplication();

   // Remember object scale
   void doSetInitScale();

   // Save rendering tree
   void save(std::string filePath);

   // Load saved rendering tree
   void load(std::string filePath);

   // Delete object
   void doDeleteObj();

   // Check position validity
   void checkValidPos();

   // Check mouse validity
   bool isMouseOnTable();

   // Check point validity
   bool isOnTable(glm::dvec3 point);

   // Ajouter un cylindre � la sc�ne
   void addNode(std::string type);
   void convertMouseToClient(
	   GLdouble& worldX, GLdouble& worldY, GLdouble& worldZ);
   // selection
   void selectObject(bool keepOthers);

private:
   /// Constructeur par d�faut.
	FacadeModele() = default;
	/// Destructeur.
	~FacadeModele() = default;
	/// Constructeur copie d�sactiv�.
	FacadeModele(const FacadeModele&) = delete;

	/// Op�rateur d'assignation d�sactiv�.
	FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   // variable pour rectangle elastique

   glm::ivec2 ancrage_, oldPos_, olderPos_;
   bool rectangleElastique_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   std::unique_ptr<vue::Vue> vue_{ nullptr };

   // Positions initiales de la cam�ra (pour d�placement)
   glm::dvec3 viewInit_; 
   glm::dvec3 cameraPosInit_;
   glm::dvec3 cameraTargetInit_;

   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   std::unique_ptr<ArbreRenduINF2990> arbre_;




};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_.get();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_.get();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_.get();
}




#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
