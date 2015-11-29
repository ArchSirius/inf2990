///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la premi�re page de la documentation Doxygen.
/**

@mainpage Projet int�grateur de deuxi�me ann�e -- INF2990

*/

namespace vue {
	class Camera;
}

#include <windows.h>
#include <cassert>
#include <fstream>
#include <stdlib.h>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"
#include "NoeudRobot.h"

#include "VueOrtho.h"
#include "VueOrbite.h"
#include "Camera.h"
#include "Projection.h"


#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

#include "Visitor\Tools.h"
#include "../../Application/Visitor/CollisionTool.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <functional>

#include "Debug.h"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_;

/// Cha�ne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::FacadeModele()
///
/// Constructeur par d�faut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::FacadeModele()
{
	skybox1[0] = "../Exe/Skybox/atrium_front.png";
	skybox1[1] = "../Exe/Skybox/atrium_back.png";
	skybox1[2] = "../Exe/Skybox/atrium_right.png";
	skybox1[3] = "../Exe/Skybox/atrium_left.png";
	skybox1[4] = "../Exe/Skybox/atrium_down.png";
	skybox1[5] = "../Exe/Skybox/atrium_up.png";

	skybox2[0] = "../Exe/Skybox/roger-gaudry_front.png";
	skybox2[1] = "../Exe/Skybox/roger-gaudry_back.png";
	skybox2[2] = "../Exe/Skybox/roger-gaudry_right.png";
	skybox2[3] = "../Exe/Skybox/roger-gaudry_left.png";
	skybox2[4] = "../Exe/Skybox/roger-gaudry_down.png";
	skybox2[5] = "../Exe/Skybox/roger-gaudry_up.png";
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas �t� cr��e, elle la cr�e.  Cette
/// cr�ation n'est toutefois pas n�cessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa cr�ation.
///
/// @param[] aucun
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
    if (!instance_) {
        instance_ = new FacadeModele;
		instance_->selectionColor_ = std::vector<GLubyte>({0, 0, 0});
    }		

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction lib�re l'instance unique de cette classe.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle cr�e
/// un contexte OpenGL sur la fen�tre pass�e en param�tre, initialise
/// FreeImage (utilis�e par le chargeur de mod�les) et assigne des 
/// param�tres du contexte OpenGL.
///
/// @param[in] hWnd : La poign�e ("handle") vers la fen�tre � utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	rectangleElastique_ = false;
	simulationStarted = 0;

	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	//assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilis�e par le chargeur, doit �tre initialis�e
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumi�res
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualit�
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lumi�re ambiante "globale"
	// Attention :
	//La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glm::vec4 ambiant{ 0.2f, 0.2, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));

	// Cr�ation de l'arbre de rendu.  � moins d'�tre compl�tement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de cr�er
	// l'arbre apr�s avoir cr�� le contexte OpenGL.
	arbre_ = std::make_unique<ArbreRenduINF2990>();
	arbre_->initialiser();

	// Inspir� de http://stackoverflow.com/questions/8690619/how-to-get-screen-resolution-in-c
	RECT panel;
	GetWindowRect(hWnd, &panel);

	// On cr�e une vue par d�faut.
	vue_ = std::make_unique<vue::VueOrtho>(
		vue::Camera{ 
		glm::dvec3(170, 83, 200), glm::dvec3(170, 83, 0),	// Pour centrer la cam�ra sur la table
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionOrtho{ 
				0, panel.right, 0, panel.bottom,
				1, 1000, 0.03, 0.5, 0.01,
				-100, 100, -100, 100 }
	);

	textRender = new Text();


	// On se souvient des valeurs par defaut de la camera
	vue_->obtenirCamera().assignerPositionInitiale({ 170, 83, 200 });
	vue_->obtenirCamera().assignerPointViseInitial({ 170, 83, 0 });

	// Initialisation de la skybox
	skybox();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration � partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est g�n�r� �
/// partir de valeurs par d�faut directement dans le code.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// V�rification de l'existance du ficher

	// Si le fichier n'existe pas, on le cr�e.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire � partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les diff�rentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction g�n�re un fichier XML de configuration � partir de
/// valeurs par d�faut directement dans le code.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// �crire la d�claration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les diff�rentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// �crire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction lib�re le contexte OpenGL et d�sinitialise FreeImage.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On lib�re les instances des diff�rentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre d�truit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	
	// Efface l'ancien rendu
	if (!rectangleElastique_)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Ne devrait pas �tre n�cessaire
		vue_->appliquerProjection();

		// Positionne la cam�ra
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		vue_->appliquerCamera();
		
		// Afficher la sc�ne
		afficherBase();

		std::ostringstream time_s;

		if (simulationStarted)
		{
			time_s = std::ostringstream();
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> time_d = end - start_simulation_time;

			// On peut pas depasser 59:59
			double total = std::min(3599.0, time_d.count());
			
			// Calcul des minutes et des secondes
			int minutes = (int)total / 60;
			int seconds = (int)total % 60;

			// Ajout du z�ro signifiatif des minutes au besoin
			if (minutes < 10)
			{
				time_s << "0";
			}

			time_s << minutes << ":";

			// Ajout du z�ro signifiatif des secondes au besoin
			if (seconds < 10)
			{
				time_s << "0";
			}
			
			time_s << seconds;
		}
		else
		{
			time_s = std::ostringstream();
			time_s << "00:00";
		}

		textRender->render("Profil actif: " + profile_name_, "Temps: " + time_s.str());
		// Compte de l'affichage
		utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

		// �change les tampons pour que le r�sultat du rendu soit visible.
        if (!isSelecting_)
		    ::SwapBuffers(hDC_);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la sc�ne, c'est-�-dire
/// qu'elle met en place l'�clairage et affiche les objets.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumi�re.
	glm::vec4 position{ 0, 0, 1, 0 };
	
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumi�re
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));

	// Afficher la sc�ne.
	if (!rectangleElastique_)
	{
		if (!isSelecting_) {
			// affichage de la skybox dans le monde virtuel, avant l'affichage de l'arbre
			skybox_->afficher(glm::dvec3(0.0, 0.0, 0.0), 400);
		}
		arbre_->afficher();
	}
	else
	{
		this->obtenirInstance()->mettreAJourRectangleElastique();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction r�initialise la sc�ne � un �tat "vide".
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// R�initialisation de la sc�ne.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise � jour des objets.
	arbre_->animer(temps);
	// Mise � jour de la vue.
	vue_->animer(temps);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerXY(double deplacementX, double deplacementY)
///
/// Pour le deplacement de la vue
///
/// @param[in] deplacerX : selon l'axe des X
/// @param[in] deplacerY : selon l'axe des Y
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerXY(double deplacementX, double deplacementY)
{
    vue_->deplacerXY(deplacementX, deplacementY);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomerIn()
///
///Pour le zoom avant de la vue
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomerIn()
{
	vue_->zoomerIn();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomerOut()
///
///Pour le zoom Out
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomerOut()
{
	vue_->zoomerOut();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::addNode(std::string type)
///
/// Cr�e un noeud et l'ajoute � l'arbre, avec la table comme parent.
/// Lui donne ensuite les coordonn�es n�cessaire � son affichage.
///
/// @param[in] std::string type Le type du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::addNode(std::string type)
{
	NoeudAbstrait* newNode;
	if (type == ArbreRenduINF2990::NOM_SEGMENT)
	{
		auto newSegment = arbre_->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		newNode = newSegment.get();
		lastCreatedComposite_->ajouter(std::move(newSegment));
		newNode->assignerParent(lastCreatedComposite_);
	}
	else
		newNode = arbre_->ajouterNouveauNoeud(
		ArbreRenduINF2990::NOM_TABLE, 
		type);
	
	newNode->assignerEstSelectionnable(true);

	auto cursor = getCoordinates();
	newNode->assignerPositionRelative(glm::dvec3(cursor.x, cursor.y, -5.0));
    newNode->assignerPositionInitiale(glm::dvec3(cursor.x, cursor.y, -5.0));

	// On v�rifie s'il est sur la table
	if (!isOnTable(newNode))
		newNode->obtenirParent()->effacer(newNode);

	// On garde une r�f�rence au noeud, pour la cr�ation de murs et de lignes
    else
		lastCreatedNode_ = newNode;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::addComposite(std::string type)
///
/// Cr�e un composite et l'ajoute � l'arbre, avec la table comme parent.
/// Lui donne ensuite les coordonn�es n�cessaire � son affichage.
///
/// @param[in] std::string type Le type du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::addComposite(std::string type)
{
	auto newNode = arbre_->ajouterNouveauNoeud(
		ArbreRenduINF2990::NOM_TABLE,
		type);

	//Si c'est le mode teste on ajoute le robot

	

	newNode->assignerEstSelectionnable(false);

	glm::dvec3 cursor = { 0.0, 0.0, getCoordinates().z }; // 0 pour composite
	newNode->assignerPositionRelative(cursor); 
	newNode->assignerPositionInitiale(cursor);

	// On garde une r�f�rence au noeud, pour la cr�ation de murs et de lignes
	lastCreatedComposite_ = newNode;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::updateNode()
///
/// Calcule la position de la souris, puis la donne au dernier noeud
/// cr�� pour qu'il actualise son affichage.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::updateNode()
{
	auto cursor = getCoordinates();
	lastCreatedNode_->updateCreation(cursor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::abortTerminalNode()
///
/// Annule la cr�ation d'un noeud terminal fant�me
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::abortTerminalNode()
{
	arbre_->effacer(lastCreatedNode_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::abortTerminalNode()
///
/// Annule la cr�ation d'un noeud composite fant�me
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::abortCompositeNode()
{
	arbre_->effacer(lastCreatedComposite_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::ivec3 FacadeModele::getCoordinates()
///
/// Transforme les donn�es de la position de la souris en coordonn�es
/// utilisable dans la fen�tre
///
/// @param[] aucun
///
/// @return Coordonn�es du pixel.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 FacadeModele::getCoordinates()
{
	/*
	* Proc�dure et explications tir�es de http://nehe.gamedev.net/article/using_gluunproject/16013/
	*/

	GLint viewport[4];					//var to hold the viewport info
	GLdouble modelview[16];				//var to hold the modelview info
	GLdouble projection[16];			//var to hold the projection matrix info
	GLfloat winX, winY, winZ;			//variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);	//get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport);			//get the viewport info



	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	winX = (float)mouse.x;                  // Holds The Mouse X Coordinate
	winY = (float)mouse.y;                  // Holds The Mouse Y Coordinate

	winY = (float)viewport[3] - (float)winY;

	glReadPixels(mouse.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	//winZ = 0;
	//get the world coordinates from the screen coordinates
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

	return glm::dvec3(static_cast<double>(worldX), static_cast<double>(worldY), 0.0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<GLubyte> FacadeModele::getColor()
///
/// Lis les coordonn�es de la souris dans la fen�tre et en trouve la couleur.
///
/// @param[] aucun
///
/// @return Couleur du pixel
///
////////////////////////////////////////////////////////////////////////
std::vector<GLubyte> FacadeModele::getColor()
{
	/*
	* Proc�dure et explications tir�es de http://nehe.gamedev.net/article/using_gluunproject/16013/
	*/

	GLint viewport[4];					//var to hold the viewport info
	GLdouble modelview[16];				//var to hold the modelview info
	GLdouble projection[16];			//var to hold the projection matrix info
	GLfloat winX, winY, winZ;			//variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);	//get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport);			//get the viewport info
	
	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	winX = (float)mouse.x;                  // Holds The Mouse X Coordinate
	winY = (float)mouse.y;                  // Holds The Mouse Y Coordinate

	winY = (float)viewport[3] - (float)winY;

	GLubyte data[3];
	glReadPixels(mouse.x, int(winY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &data);

	return std::vector<GLubyte>({ data[0], data[1], data[2] });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::ivec3 FacadeModele::getCoordinate()
///
/// Transforme les donn�es de la position de la souris, avant de faire
/// la projection inverse
///
/// @param[] aucun
///
/// @return Coordonn�es du pixel.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 FacadeModele::getUnprojectedCoords()
{
	/*
	* Proc�dure et explications tir�es de http://nehe.gamedev.net/article/using_gluunproject/16013/
	*/

	GLint viewport[4];					//var to hold the viewport info
	GLdouble modelview[16];				//var to hold the modelview info
	GLdouble projection[16];			//var to hold the projection matrix info
	GLfloat winX, winY, winZ;			//variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);	//get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport);			//get the viewport info

	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	winX = (float)mouse.x;                  // Holds The Mouse X Coordinate
	winY = (float)mouse.y;                  // Holds The Mouse Y Coordinate

	winY = (float)viewport[3] - (float)winY;

	return glm::dvec3(static_cast<double>(worldX), static_cast<double>(worldY), 0.0);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::redimensionnerFenetre(const glm::ivec2& coinMin, const glm::ivec2& coinMax)
///
/// Redimensionne la fen�tre du programme
///
/// @param[in] coinMin : Nouveau coin inf�rieur
/// @param[in] coinMax : Nouveau coin sup�rieur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::redimensionnerFenetre(const glm::ivec2& coinMin, const glm::ivec2& coinMax)
{
	vue_->redimensionnerFenetre(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectObject()
///
/// Pour chaque �l�ment de l'arbre, v�rifie s'il est touch� par la
/// souris et, le cas �ch�ant, le signale comme s�lectionn�
///
/// @param[in] keepOthers : Pr�server la s�lection actuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectObject(bool keepOthers)
{
	if (!keepOthers)
		arbre_->deselectionnerTout();

    glFinish();
    glReadBuffer(GL_BACK);

    auto data = getColor();
    isSelecting_ = false;

	arbre_->assignerSelectionEnfants(keepOthers, data);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectAll()
///
/// S�lectionne chaque �l�ment de l'arbre
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectAll()
{
	arbre_->selectionnerTout();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doSetInitPos()
///
/// Cette fonction permet d'enregistrer la position des objets
/// s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitPos()
{
	auto visitor = PositionTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doSetInitScale()
///
/// Cette fonction permet d'enregistrer l'�chelle des objets
/// s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitScale()
{
	auto visitor = SetScaleTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doTranslation()
///
/// Cette fonction permet d'effectuer une translation des objets
/// s�lectionn�s
///
/// @param[in] deltaX : Composante en X de la translation
/// @param[in] deltaY : Composante en Y de la translation
/// @param[in] deltaZ : Composante en Z de la translation
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doTranslation(float deltaX, float deltaY, float deltaZ)
{
	auto visitor = TranslateTool(deltaX, deltaY, deltaZ);
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doSetInitAngle()
///
/// Cette fonction permet d'enregistrer l'angle des objets s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitAngle()
{
	auto visitor = AngleTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doRotation()
///
/// Cette fonction permet d'effectuer une rotation des objets s�lectionn�s
///
/// @param[in] deltaX : Composante en X de la rotation
/// @param[in] deltaY : Composante en Y de la rotation
/// @param[in] deltaZ : Composante en Z de la rotation
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doRotation(float deltaX, float deltaY, float deltaZ)
{
	// Obtenir le centre de rotation
	auto centerVisitor = CenterTool();
	obtenirArbreRenduINF2990()->accept(centerVisitor);
	glm::dvec3 center = centerVisitor.getCenter();

	// Rotation
	auto rotateVisitor = RotateTool((float)center[0], (float)center[1], (float)center[2], (float)deltaX, (float)deltaY, (float)deltaZ);
	obtenirArbreRenduINF2990()->accept(rotateVisitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doScaling()
///
/// Cette fonction permet d'effectuer une mise � l'�chelle des objets
/// s�lectionn�s
///
/// @param[in] deltaX : Composante en X de la mise � l'�chelle
/// @param[in] deltaY : Composante en Y de la mise � l'�chelle
/// @param[in] deltaZ : Composante en Z de la mise � l'�chelle
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doScaling(float deltaX, float deltaY, float deltaZ)
{
	auto visitor = ScaleTool(deltaX, deltaY, deltaZ);
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initializeDuplication()
///
/// Cette fonction permet d'effectuer une duplication des objets
/// s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::initializeDuplication()
{
	// Obtenir le centre des objets
	auto centerVisitor = CenterTool();
	obtenirArbreRenduINF2990()->accept(centerVisitor);
	glm::dvec3 center = centerVisitor.getCenter();

	// Duplication initiale
	_duplicator = std::make_unique<DuplicateTool>(center);
	obtenirArbreRenduINF2990()->accept(*_duplicator.get());
	_duplicator->duplicate();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::updateDuplication()
///
/// Cette fonction permet de mettre � jour l'estampe de duplication
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::updateDuplication()
{
	// Obtenir les coordonn�es du curseur
	auto cursor = getCoordinates();
	// Mise � jour du tampon
	_duplicator->updateBuffer(cursor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::endDuplication()
///
/// Cette fonction permet de terminer l'estampe de duplication
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::endDuplication()
{
	_duplicator->confirmBuffer();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::doDeleteObj()
///
/// Cette fonction permet d'effectuer une suppression des objets
/// s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doDeleteObj()
{
	auto visitor = DeleteTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::getNbNodesSelected()
///
/// Cette fonction permet de d�terminer le nombre de noeuds s�lectionn�s
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
int FacadeModele::getNbNodesSelected()
{
	auto visitor = SelectTool();
	obtenirArbreRenduINF2990()->accept(visitor);
	return visitor.getNbSelected();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::getSelectedNodeData()
///
/// Cette fonction permet de retourner les donn�es (pos, scale, rot)
/// du noeud s�lectionn�
///
/// @param[out] dataRef : Donn�es � obtenir
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::getSelectedNodeData(NodeProperties* dataRef)
{
	auto visitor = GetDataTool(dataRef);
	obtenirArbreRenduINF2990()->accept(visitor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setSelectedNodeData()
///
/// Cette fonction permet de d�finir les donn�es (pos, scale, rot)
/// du noeud s�lectionn�
///
/// @param[in] dataRef : Donn�es � assigner
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::setSelectedNodeData(NodeProperties* dataRef)
{
	doSetInitPos();
	doSetInitScale();
	doSetInitAngle();

	auto visitor = SetDataTool(dataRef);
	obtenirArbreRenduINF2990()->accept(visitor);

	checkValidPos();

	doSetInitPos();
	doSetInitScale();
	doSetInitAngle();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::resetMap()
///
/// Cette fonction permet de r�initialiser l'arbre par d�faut
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::resetMap()
{
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::save()
///
/// Cette fonction permet de sauvegarder l'arbre de rendu dans un fichier
///		
/// @param[in] filePath : URL local du fichier � enregistrer
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::save(std::string filePath)
{
	auto data = obtenirArbreRenduINF2990()->getSavableData();

	std::ofstream saveFile(filePath);

	saveFile << data.serializeJson();
	saveFile.close();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::load()
///
/// Cette fonction permet de charger un arbre de rendu depuis un fichier
///
/// @param[in] filePath : URL local du fichier � charger
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::load(std::string filePath)
{
	std::function<void(const rapidjson::Value&, NoeudAbstrait*)> loadNode = [&](const rapidjson::Value& node, NoeudAbstrait* parentNode) {

		auto type = std::string(node["type"].GetString());
		auto parent_type = std::string(node["parent_type"].GetString());

		if (type != "racine") {

			auto newNode = arbre_->creerNoeud(type);

			newNode->assignerPositionRelative(
				glm::dvec3(
					std::stod(node["position_x"].GetString()),
					std::stod(node["position_y"].GetString()),
					std::stod(node["position_z"].GetString())
				)
			);

			newNode->assignerPositionInitiale(
				glm::dvec3(
					std::stod(node["position_x"].GetString()),
					std::stod(node["position_y"].GetString()),
					std::stod(node["position_z"].GetString())
				)
			);

			newNode->setScalable(true);
			newNode->setScale(
				glm::fvec3(
					std::stod(node["scale_x"].GetString()),
					std::stod(node["scale_y"].GetString()),
					std::stod(node["scale_z"].GetString())
				)
			);
			newNode->setScalable(false);

			newNode->assignerAngle(std::stof(node["angle_rotation"].GetString()));
			newNode->assignerAngleInitial(std::stof(node["angle_rotation"].GetString()));

			if (node.HasMember("children")) {
				for (auto& child : node["children"]) {
					loadNode(child, newNode.get());
				}
			}

			parentNode->ajouter(std::move(newNode));
		}
		else
		{
			if (node.HasMember("children")) {
				for (auto& child : node["children"]) {
					loadNode(child, arbre_.get());
				}
			}
		}
	};

	// Vider la table
	arbre_->reinitialiser();

	// Tir� de: https://github.com/pah/rapidjson/blob/master/doc/stream.md
	FILE* fp = fopen(filePath.c_str(), "rb");

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document document;
	document.ParseStream(is);

	assert(document.IsObject());
	assert(document.HasMember("children"));

	loadNode(document, arbre_.get());

	fclose(fp);

	arbre_->accept(UpdatePosTool());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::checkValidPos()
///
/// Cette fonction v�rifie si les objets sont � une position valide.
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::checkValidPos()
{
	auto validCheck = ValidCheckTool();
	obtenirArbreRenduINF2990()->accept(validCheck);

	if (!validCheck.isValid())
	{
		auto invalid = InvalidTool();
		obtenirArbreRenduINF2990()->accept(invalid);
	}
	else
	{
		auto position = PositionTool();
		obtenirArbreRenduINF2990()->accept(position);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::isMouseOnTable()
///
/// Cette fonction v�rifie si le curseur est au-dessus de la table.
///
/// @param[] aucun
///
/// @return True si oui, false sinon.
///
///////////////////////////////////////////////////////////////////////
bool FacadeModele::isMouseOnTable()
{
	auto cursor = getCoordinates();;
	return isOnTable(cursor);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::isOnTable()
///
/// Cette fonction v�rifie si un point est au-dessus de la table.
///
/// @param[in] point : Le point � v�rifier
///
/// @return True si oui, false sinon.
///
///////////////////////////////////////////////////////////////////////
bool FacadeModele::isOnTable(glm::dvec3 point)
{
	auto table = arbre_->chercher(arbre_->NOM_TABLE);
	return table->clickHit(point);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::isOnTable()
///
/// Cette fonction v�rifie si un noeud est au-dessus de la table.
///
/// @param[in] point : Le noeud
///
/// @return True si oui, false sinon.
///
///////////////////////////////////////////////////////////////////////
bool FacadeModele::isOnTable(NoeudAbstrait* node)
{
	auto table = arbre_->chercher(arbre_->NOM_TABLE);
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*table->getModele());

	glm::ivec2 hitboxMin = { hitbox.coinMin.x, hitbox.coinMin.y };
	glm::ivec2 hitboxMax = { hitbox.coinMax.x, hitbox.coinMax.y };
	return node->clickHit(hitboxMin, hitboxMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::saveMousePos()
///
/// Cette fonction permet de sauvegarder la position actuelle de 
/// la souris
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::saveMousePos()
{
    lastMousePos_ = getCoordinates();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::moveCameraMouse()
///
/// Cette fonction permet de changer la position de la vue (avec cam�ra)
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::moveCameraMouse()
{
	// On prend la diff�rence entre la position de la souris et
	// la position initiale de la vue (vecteur de d�placement)
    vue_->deplacerSouris(getCoordinates() - lastMousePos_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::moveCameraMouse(int deltaX, int deltaY)
///
/// Cette fonction permet de changer la position de la vue (avec cam�ra)
/// Utilise les coordonn�es de l'�cran (venues du C#)
///
/// @param[] int deltaX, int deltaY, la diff�rence de coordonn�es en C#
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::moveCameraMouse(int deltaX, int deltaY)
{
	vue_->deplacerSouris(glm::dvec3{ deltaX, deltaY, 0.0 });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::preparerRectangleElastique()
///
/// Prend en memoire le point d'ancrage du prochain rectangle elastique
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::preparerRectangleElastique()
{
	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	ancrageRectangle_ = { static_cast<double>(mouse.x), static_cast<double>(mouse.y), 0.0 };
	ancrage_ = getCoordinates();
	firstSelectionPixel_ = ancrageRectangle_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRectangleElastique()
///
/// Cr�e un petit rectangle elastique
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRectangleElastique()
{

	rectangleElastique_= true;
	oldPos_ = ancrageRectangle_;
	aidegl::initialiserRectangleElastique({ static_cast<int>(ancrageRectangle_.x), static_cast<int>(ancrageRectangle_.y) });

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mettreAJourRectangleElastique()
///
/// Pour chaque �l�ment de l'arbre, v�rifie s'il est touch� par la souris
/// et, le cas �ch�ant, le signale comme s�lectionn�
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::mettreAJourRectangleElastique()
{

	//auto temp = getCoordinates();
	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	if (abs(ancrageRectangle_.x - oldPos_.x) == 0 || abs(ancrageRectangle_.y - oldPos_.y) == 0 || (abs(ancrageRectangle_.x - oldPos_.x) < 4 && abs(ancrageRectangle_.y - oldPos_.y) < 4))
	{
		//Refaire le rectangle pour quil soit effacer de nouveau par mettre a jour
		aidegl::effaceRectangleElastique(
		{ static_cast<int>(ancrageRectangle_.x), static_cast<int>(ancrageRectangle_.y) },
		{ static_cast<int>(oldPos_.x), static_cast<int>(oldPos_.y) });
	}
	
	aidegl::mettreAJourRectangleElastique(
	{ static_cast<int>(ancrageRectangle_.x), static_cast<int>(ancrageRectangle_.y) },
		{ static_cast<int>(oldPos_.x), static_cast<int>(oldPos_.y) },
		{ static_cast<int>(mouse.x), static_cast<int>(mouse.y) });
	
	if (abs(ancrageRectangle_.x - mouse.x) == 0 || abs(ancrageRectangle_.y - mouse.y) == 0 || (abs(ancrageRectangle_.x - mouse.x) < 4 && abs(ancrageRectangle_.y - mouse.y) < 4))
	{
		//Effacer le rectangle qui vient detre aficher.
		aidegl::effaceRectangleElastique({ static_cast<int>(ancrageRectangle_.x), static_cast<int>(ancrageRectangle_.y) },
		{ static_cast<int>(mouse.x), static_cast<int>(mouse.y) });
	}
	oldPos_ = { mouse.x, mouse.y, 0.0 };

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::terminerRectangleElastique()
///
/// Pour chaque �l�ment de l'arbre, v�rifie s'il est touch� par la souris
/// et, le cas �ch�ant, le signale comme s�lectionn�
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangleElastique()
{
	rectangleElastique_ = false;
	
	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	glm::ivec2 temp = { static_cast<int>(mouse.x), static_cast<int>(mouse.y) };
	aidegl::terminerRectangleElastique({ static_cast<int>(ancrageRectangle_.x), static_cast<int>(ancrageRectangle_.y) }, temp);
	lastSelectionPixel_ = glm::dvec3{temp.x, temp.y, 0.0};
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectMultipleObjects(bool keepOthers)
///
/// Pour chaque �l�ment de l'arbre, v�rifie s'il est touch� par la souris
/// et, le cas �ch�ant, le signale comme s�lectionn�
///
/// @param[in] keepOthers : Conserver la s�lection actuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectMultipleObjects(bool keepOthers)
{
	if (!keepOthers)
		arbre_->deselectionnerTout();
	
	glFinish();
	glReadBuffer(GL_BACK);

	unsigned int sizeOfData = 3 * static_cast<int>(abs(lastSelectionPixel_.x - firstSelectionPixel_.x) * abs(lastSelectionPixel_.y - firstSelectionPixel_.y));
	auto minX = std::min(lastSelectionPixel_.x, firstSelectionPixel_.x);
	auto minY = std::min(lastSelectionPixel_.y, firstSelectionPixel_.y);
	GLubyte* data = new GLubyte[sizeOfData];
	for (unsigned int i = 0; i < abs(lastSelectionPixel_.x - firstSelectionPixel_.x); i++)
	{
		for (unsigned int j = 0; j < abs(lastSelectionPixel_.y - firstSelectionPixel_.y); j++)
		{
			glReadPixels(minX + i, minY + j, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &data[3 * (i * static_cast<int>(abs(lastSelectionPixel_.y - firstSelectionPixel_.y))) + 3 * j]);
		}
	}
	isSelecting_ = false;

	arbre_->assignerSelectionEnfants(keepOthers, data, sizeOfData);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomInRectangle()
///
/// 
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomInRectangle()
{
	glm::ivec2 temp = { static_cast<int>(getCoordinates().x), static_cast<int>(getCoordinates().y) };
	if (abs(ancrageRectangle_.x - oldPos_.x) != 0 && abs(ancrageRectangle_.y - oldPos_.y) != 0 && (abs(ancrageRectangle_.x - oldPos_.x) > 3 || abs(ancrageRectangle_.y - oldPos_.y) > 3))
		vue_->zoomerInElastique({ static_cast<int>(ancrage_.x), static_cast<int>(ancrage_.y) }, temp);
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomOutRectangle()
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomOutRectangle()
{
	glm::ivec2 temp = { static_cast<int>(getCoordinates().x), static_cast<int>(getCoordinates().y) };
	if (abs(ancrageRectangle_.x - oldPos_.x) != 0 && abs(ancrageRectangle_.y - oldPos_.y) != 0 && (abs(ancrageRectangle_.x - oldPos_.x) > 3 || abs(ancrageRectangle_.y - oldPos_.y) > 3))
		vue_->zoomerOutElastique({ static_cast<int>(ancrage_.x), static_cast<int>(ancrage_.y) }, temp);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setDebug(DebugSettings settings)
///
/// @param[in] settings: �tats d'activation des d�clancheurs et informations
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setDebug(DebugSettings* settings)
{
	Debug::getInstance()->setTriggers(settings);
}


////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::startSimulation()
///		@param[in] aucun
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::startSimulation()
{
	// ajout du robot � la table
	arbre_->deselectionnerTout();
	auto robot = arbre_->ajouterNouveauNoeud(
		ArbreRenduINF2990::NOM_TABLE,
		"robot");

	auto depart = arbre_->chercher(arbre_->NOM_DEPART);

	depart->assignerAffiche(false);
	simulationStarted = 1;

	start_simulation_time = std::chrono::system_clock::now();

    robot->assignerPositionRelative({ depart->obtenirPositionInitiale().x, depart->obtenirPositionInitiale().y, -4.5 });
	//robot->assignerPositionInitiale(depart->obtenirPositionRelative());
	robot->assignerAngleInitial(depart->obtenirAngleInitial());
	robot->assignerAngle(depart->obtenirAngle());
	((NoeudRobot*)robot)->initSensorDist();
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::stopSimulation()
///		@param[in] aucun
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::stopSimulation()
{
	auto depart = arbre_->chercher(arbre_->NOM_DEPART);
	depart->assignerAffiche(true);
	simulationStarted = 0;

	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	auto parent = robot->obtenirParent();
	parent->effacer(robot);
}


////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::setProfileData()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setProfileData(std::shared_ptr<Profil> data)
{
	profile_name_ = std::string(data->profile_name);
	profile_ = data;

	if (arbre_ != nullptr)
	{
		auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
		if (robot != nullptr)
		{
			((NoeudRobot*)robot)->loadProfile(profile_);
			((NoeudRobot*)robot)->initSensorDist();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::robotTurnRight()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::robotTurnRight()
{
	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	((NoeudRobot*)robot)->turnRight();
	auto collision = CollisionTool(((NoeudRobot*)robot));
	arbre_->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::robotTurnRight()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::robotTurnLeft()
{
	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	((NoeudRobot*)robot)->turnLeft();
	auto collision = CollisionTool(((NoeudRobot*)robot));
	arbre_->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::robotReverse()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::robotReverse()
{
	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	((NoeudRobot*)robot)->reverse();
	auto collision = CollisionTool(((NoeudRobot*)robot));
	arbre_->accept(collision);
}
////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::robotForward()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::robotForward()
{
	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	((NoeudRobot*)robot)->forward();
	auto collision = CollisionTool(((NoeudRobot*)robot));
	arbre_->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::robotToggleManualMode()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::robotToggleManualMode()
{
	auto robot = arbre_->chercher(arbre_->NOM_ROBOT);
	((NoeudRobot*)robot)->toggleManualMode();
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::skybox()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::skybox() 
{
	
	if (estEnModeTest_)
	{
		skybox_ = new utilitaire::BoiteEnvironnement(
			skybox1[0], skybox1[1],
			skybox1[2], skybox1[3],
			skybox1[4], skybox1[5]);
	}
	else
	{
		skybox_ = new utilitaire::BoiteEnvironnement(
			skybox2[0], skybox2[1],
			skybox2[2], skybox2[3],
			skybox2[4], skybox2[5]);
	}

}
////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::getEstEnModeEdition()
///		@param[in] data
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::getEstEnModeTest()
{
	return estEnModeTest_;
}

////////////////////////////////////////////////////////////////////////
///
///		void FacadeModele::setEstEnModeEdition()
///		@param[in] bool estEnModeEdition
///		@return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setEstEnModeTest(bool estEnModeTest)
{
	estEnModeTest_ = estEnModeTest;
}

////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::changeToOrbitView()
///
/// Change la vue active en vue orbite, avec projection en perspective.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changeToOrbitView()
{
    RECT panel;
    GetWindowRect(hWnd_, &panel);

    vue_ = std::make_unique<vue::VueOrbite>(
        vue::Camera{
        glm::dvec3(9, 2, 200), glm::dvec3(9, 2, 0),     // Camera centr�e sur la table
        glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0) },
        vue::ProjectionPerspective{
            0, panel.right, 0, panel.bottom,
            1, 1000, -0.2, 0.5, 0.01,
            -100, 100, -100, 100 }
        );

    // On se souvient des valeurs par defaut de la camera
    vue_->obtenirCamera().assignerPositionInitiale({ 9.0, 2.0, 200.0 });
	vue_->obtenirCamera().assignerPointViseInitial({ 9.0, 2.0, 0.0 });
    orbitActive_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::changeToOrthoView()
///
/// Change la vue active en vue 2D, avec projection orthogonale.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changeToOrthoView()
{
    RECT panel;
    GetWindowRect(hWnd_, &panel);

    vue_ = std::make_unique<vue::VueOrtho>(
        vue::Camera{
        glm::dvec3(170, 83, 200), glm::dvec3(170, 83, 0),	// Pour centrer la cam�ra sur la table
        glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0) },
        vue::ProjectionOrtho{
            0, panel.right, 0, panel.bottom,
            1, 1000, 0.03, 0.5, 0.01,
            -100, 100, -100, 100 }
        );

    // On se souvient des valeurs par defaut de la camera
    vue_->obtenirCamera().assignerPositionInitiale({ 170, 83, 200 });
    vue_->obtenirCamera().assignerPointViseInitial({ 170, 83, 0 });
    orbitActive_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<GLubyte> FacadeModele::genSelectionColor()
///
/// G�n�re une couleur unique pour la s�lection.
///
/// @param[] Aucun
///
/// @return La nouvelle couleur.
///
////////////////////////////////////////////////////////////////////////
std::vector<GLubyte> FacadeModele::genSelectionColor()
{
    if (selectionColor_[0] <= 255) {
		selectionColor_[0]++;
    }
    else {
		selectionColor_[0] = 0;
		if (selectionColor_[1] <= 255) {
			selectionColor_[1]++;
        }
        else {
			selectionColor_[1]  = 0;
			if (selectionColor_[2] <= 255) {
				selectionColor_[2]++;
            }
            else {
				selectionColor_[2] = 0;
            }
        }
    }
    return selectionColor_;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
