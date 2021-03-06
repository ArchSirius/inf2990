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
#include <chrono>
#include <ctime>

// Pour le unique_ptr, beacuase MSCV
#include "Vue.h"
#include "ArbreRenduINF2990.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "NodeProperties.h"
#include "Profil.h"
#include "../Interface/DebugSettings.h"
#include "Visitor\DuplicateTool.h"
#include "Sound.h"
#include "Text.h"
#include "BoiteEnvironnement.h"
#include "utilitaire.h"

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
   /// Cr�e un contexte FMOD et initialise celui-ci.
   int initialiserFMOD(HWND hWnd);
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

   /// Deplace la camera.
   void deplacerXY(double deplacementX, double deplacementY);
   /// Sauvegarder la vue initiale
   void saveMousePos();
   /// Bouge la cam�ra avec la sourie
   void moveCameraMouse();
   void moveCameraMouse(int deltaX, int deltaY); // Avec les coordonn�es de la fen�tre

   /// Zoom in
   void zoomerIn();

   /// Zoom out
   void zoomerOut();

   /// Prepare le rectangle �lastique
   void preparerRectangleElastique();
   /// Initialise le rectangle �lastique
   void initialiserRectangleElastique();
   /// Met � jour le rectangle �lastique
   void mettreAJourRectangleElastique( ); 
   /// Termine le rectangle �lastique
   void terminerRectangleElastique();

   /// Coordonn�es de la souris
   glm::dvec3 getCoordinates();
   std::vector<GLubyte> getColor();
   glm::dvec3 getLastCoordinates() { return lastMousePos_; }
   glm::dvec3 getUnprojectedCoords();

   /// Ajuster la nouvelle fenetre
   void redimensionnerFenetre(const glm::ivec2& coinMin, const glm::ivec2& coinMax);

   /// Se souvient de la position d'un objet
   void doSetInitPos();
   /// D�place un noeud
   void doTranslation(float deltaX, float deltaY, float deltaZ);
   /// Se souvient de l'angle d'un objet
   void doSetInitAngle();
   /// Pivote un objet
   void doRotation(float deltaX, float deltaY, float deltaZ);
   /// Se souvient de l'�chelle d'un objet
   void doSetInitScale();
   /// Met un noeud � l'�chelle
   void doScaling(float deltaX, float deltaY, float deltaZ);

   /// Initialise la diuplication d'un objet
   void initializeDuplication();
   /// Affiche le fant�me de duplication
   void updateDuplication();
   /// Termine la duplication
   void endDuplication();

   /// Compte les noeud s�lectionn�s
   int getNbNodesSelected();
   /// Obtient les donn�es du noeud s�lectionn�
   void getSelectedNodeData(NodeProperties* dataRef);
   // Assigne les donn�es du noeud s�lectionn�
   void setSelectedNodeData(NodeProperties* dataRef);

   /// Remet la map � z�ro
   void resetMap();
   /// Sauvegarde l'arbre de rendu
   void save(std::string filePath);
   /// Charge l'arbre de rendu
   void load(std::string filePath);

   /// Efface un noeud
   void doDeleteObj();

   /// V�rifie la validit� de la position des objets
   void checkValidPos();

   /// Si la souris est sur la table
   bool isMouseOnTable();

   /// Si un point est sur la table
   bool isOnTable(glm::dvec3 point);
   bool isOnTable(NoeudAbstrait* node);

   /// Ajouter un noeud � la sc�ne
   void addNode(std::string type);
   void addComposite(std::string);

   /// Mettre � jour les noeuds fant�mes (murs et lignes)
   void updateNode();
   /// Annule la cr�ation d'un noeud terminal fant�me
   void abortTerminalNode();
   /// Annule la cr�ation d'un noeud composite fant�me
   void abortCompositeNode();
   
   /// S�lectionne un noeud
   void selectObject(bool keepOthers);
   /// S�lectionne plusieurs noeud
   void selectMultipleObjects(bool keepOthers);
   void selectAll();

   /// Zoom out d'un rectangle �lastique
   void zoomOutRectangle();
   /// Zoom in d'un rectangle �lastique
   void zoomInRectangle();

   /// Debug
   void setDebug(DebugSettings* settings);

   // ajout du robot lors de la simulation
   void startSimulation();
   void stopSimulation();

   void setProfileData(std::shared_ptr<Profil> data);
   std::shared_ptr<Profil> getProfileData() const { return profile_; }

   // robot : pour les touches manuelles
   void robotTurnRight();
   void robotTurnLeft();
   void robotReverse();
   void robotForward();
   void robotToggleManualMode();

   //Skybox
   void skybox();
   bool getEstEnModeTest();
   void setEstEnModeTest(bool estEnModeTest);

   //Eclairage
   void lumiereDirectionnelleAmbiante() const;
   void spotSuiveurRobot() const;

   void toggleAmbiante() ;
   void toggleDirectional();
   void toggleSpots();
   void LumiereOff();

   // Vues et projections
   void changeToOrbitView();
   void changeToOrthoView();
   bool isOrbitActive() { return orbitActive_; }

   std::vector<GLubyte> genSelectionColor();
   bool isSelecting() { return isSelecting_; }
   void setIsSelecting(bool isSelecting) { isSelecting_ = isSelecting; }

   // FMOD
   void playMusicSimulation();
   void playMusicEditor();
   void playSoundTurn(bool pause);
   void unloadFmod();

private:
	/// Constructeur par d�faut.
	FacadeModele();
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

	/// Duplicateur
	std::unique_ptr<DuplicateTool> _duplicator;

   // Variables pour rectangle elastique
   // et souris
   glm::dvec3 ancrage_,ancrageRectangle_, oldPos_;
   bool rectangleElastique_;
   glm::dvec3 firstSelectionPixel_;
   glm::dvec3 lastSelectionPixel_;

	/// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
	HWND  hWnd_{ nullptr };
	/// Poign�e ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_{ nullptr };
	/// Poign�e ("handle") vers le "device context".
	HDC   hDC_{ nullptr };

	/// Vue courante de la sc�ne.
	std::unique_ptr<vue::Vue> vue_{ nullptr };
    bool orbitActive_ = false;

	// Positions initiales de la souris (pour d�placement)
    glm::dvec3 lastMousePos_;

	/// Arbre de rendu contenant les diff�rents objets de la sc�ne.
	std::unique_ptr<ArbreRenduINF2990> arbre_;
	NoeudAbstrait* lastCreatedNode_;
	NoeudAbstrait* lastCreatedComposite_;

	std::shared_ptr<Profil> profile_;

	//FMOD
	std::unique_ptr<Sound> son_;

	std::string profile_name_;

	int simulationStarted;

	Text* textRender;
	std::chrono::time_point<std::chrono::system_clock> start_simulation_time;

	//Skybox;
	std::string skybox1[6];
	std::string skybox2[6];



	utilitaire::BoiteEnvironnement* skybox_= NULL;
	 
	bool estEnModeTest_ = false;

    /// Pour la selection
    std::vector<GLubyte> selectionColor_;
    bool isSelecting_ = false;

	// Positionner la lumi�re.
	glm::vec4 const positionAmbiante_{ 0, 0, 75, 0 };
	glm::vec4 const positionDirectionnelle_{ 50, 50, 75, 0 };
	glm::vec4 const zeroContribution_{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 const contributionMoyenne_{ 0.25, 0.25, 0.25, 1.0 };
	glm::vec4 const contributionMaximale_{ 1.0, 1.0, 1.0, 1.0 };

	// Etat lumiere
	bool ambiante_ = true;
	bool directional_ = true;
	bool spots_ = false;

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


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

// Tir� de https://github.com/miloyip/rapidjson/issues/162
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