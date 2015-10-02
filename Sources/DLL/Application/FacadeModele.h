//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once


#include <windows.h>
#include <string>
#include <memory>

// Pour le unique_ptr, beacuase MSCV
#include "Vue.h"
#include "ArbreRenduINF2990.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
	class Camera;
}

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Libère l'instance unique de la classe.
   static void libererInstance();

   /// Crée un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration à partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Libère le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du modèle.
   void afficher() const; 
   /// Affiche la base du contenu du modèle.
   void afficherBase() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// Réinitialise la scène.
   void reinitialiser();

   /// Anime la scène.
   void animer(float temps);

   //Deplace la camera.
   void deplacerXY(double deplacementX, double deplacementY);
   void setViewInit();
   void moveCameraMouse();

   //ZoomIN
   void zoomerIn();

   //ZoomOut
   void zoomerOut();

   // preparer rectangle
   void preparerRectangleElastique();
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

   // Count selected nodes
   int getNbNodesSelected();

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

   // Ajouter un cylindre à la scène
   void addNode(std::string type);
   void convertMouseToClient(
	   GLdouble& worldX, GLdouble& worldY, GLdouble& worldZ);
   // selection
   void selectObject(bool keepOthers);
   void dessinerLigne();

   void selectMultipleObjects(bool keepOthers);

   //afficher mur fantome
   void afficherFantome();

   glm::ivec2 FinLigne();

private:
   /// Constructeur par défaut.
	FacadeModele() = default;
	/// Destructeur.
	~FacadeModele() = default;
	/// Constructeur copie désactivé.
	FacadeModele(const FacadeModele&) = delete;

	/// Opérateur d'assignation désactivé.
	FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   // variable pour rectangle elastique

   glm::ivec2 ancrage_, oldPos_, olderPos_;
   bool rectangleElastique_;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la scène.
   std::unique_ptr<vue::Vue> vue_{ nullptr };

   // Positions initiales de la caméra (pour déplacement)
   glm::dvec3 viewInit_; 
   glm::dvec3 cameraPosInit_;
   glm::dvec3 cameraTargetInit_;

   /// Arbre de rendu contenant les différents objets de la scène.
   std::unique_ptr<ArbreRenduINF2990> arbre_;




};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
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
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
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
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_.get();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

// Tiré de https://github.com/miloyip/rapidjson/issues/162
// Parce que en fin 2015, certaines libs sont pas encore compatible c++ 2011 (emoticone vomi)
namespace rapidjson {
	template <typename Encoding, typename Allocator>
	typename GenericValue<Encoding, Allocator>::ValueIterator begin(GenericValue<Encoding, Allocator>& v) { return v.Begin(); }
	template <typename Encoding, typename Allocator>
	typename GenericValue<Encoding, Allocator>::ConstValueIterator begin(const GenericValue<Encoding, Allocator>& v) { return v.Begin(); }

	template <typename Encoding, typename Allocator>
	typename GenericValue<Encoding, Allocator>::ValueIterator end(GenericValue<Encoding, Allocator>& v) { return v.End(); }
	template <typename Encoding, typename Allocator>
	typename GenericValue<Encoding, Allocator>::ConstValueIterator end(const GenericValue<Encoding, Allocator>& v) { return v.End(); }
} // namespace rapidjson