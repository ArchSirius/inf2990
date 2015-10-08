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

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"


#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

#include "Visitor\Tools.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <functional>

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_;

/// Cha�ne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };


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
	if (!instance_)
		instance_ = new FacadeModele;

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

	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

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
				1, 1000, 1, 10000, 1.25,
				-100, 100, -100, 100 }
	);

	// On se souvient des valeurs par defaut de la camera
	vue_->obtenirCamera().assignerPositionInitiale({ 170, 83, 200 });
	vue_->obtenirCamera().assignerPointViseInitial({ 170, 83, 0 });
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

		// Compte de l'affichage
		utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

		// �change les tampons pour que le r�sultat du rendu soit visible.
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
		arbre_->afficher();
	}
	else{
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
	// Nouvelle m�thode : Plus longue que l'ancienne, mais ne devrait plus
	// entrer en conflit avec les projections (redimensionnement & such)
	auto cameraPos = vue_->obtenirCamera().obtenirPosition();
	auto dimensions = (glm::dvec2)vue_->obtenirProjection().obtenirDimensionCloture();
	auto cameraVise = vue_->obtenirCamera().obtenirPointVise();
	auto zoom = vue_->obtenirProjection().getZoom();

	// Selon les donn�es entr�es en C#, soit 0.10 :
	//	PositionX += (10% * LargeurFenetre)
	//	PositionY += (10% * HauteurFenetre)
	glm::dvec3 newCameraPos = { cameraPos.x + (deplacementX * dimensions.x * zoom), cameraPos.y + (deplacementY * dimensions.y * zoom), cameraPos.z };
	glm::dvec3 newCameraVise = { newCameraPos.x, newCameraPos.y, cameraVise.z };

	vue_->obtenirCamera().assignerPosition(newCameraPos);
	vue_->obtenirCamera().assignerPointVise(newCameraVise);

	
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
	newNode->assignerPositionRelative(cursor);
	newNode->assignerPositionInitiale(cursor);

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
/// @fn glm::ivec3 FacadeModele::getCoordinate()
///
/// Transforme les donn�es de la position de la souris en coordonn�es
/// utilisable dans la fen�tre
///
/// @param[] aucun
///
/// @return Aucune.
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
	arbre_->assignerSelectionEnfants(ancrage_, keepOthers);
	arbre_->afficherSelectionsConsole();
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

			newNode->setScale(
				glm::fvec3(
					std::stod(node["scale_x"].GetString()),
					std::stod(node["scale_y"].GetString()),
					std::stod(node["scale_z"].GetString())
				)
			);

			newNode->assignerAngle(std::stof(node["angle_rotation"].GetString()));

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
	arbre_->vider();

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
/// @fn void FacadeModele::setViewInit()
///
/// Cette fonction permet de sauvegarder les positions initiales de 
/// la vue et de la cam�ra
///
/// @param[] aucun
///
/// @return Aucun
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::setViewInit()
{
	viewInit_ = getCoordinates();
	cameraPosInit_	  = vue_->obtenirCamera().obtenirPosition();
	cameraTargetInit_ = vue_->obtenirCamera().obtenirPointVise();
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
	auto delta = getCoordinates();
	delta -= viewInit_;
	delta[2] = 0;	// On ignore les Z

	// Nouvelle position de la cam�ra
	cameraPosInit_	  -= delta;
	cameraTargetInit_ -= delta;

	vue_->obtenirCamera().assignerPosition(cameraPosInit_);
	vue_->obtenirCamera().assignerPointVise(cameraTargetInit_);

	
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

	arbre_->assignerSelectionEnfants(
		{ static_cast<int>(ancrage_.x), static_cast<int>(ancrage_.y) }, 
		{ static_cast<int>(getCoordinates().x), static_cast<int>(getCoordinates().y) }, 
		keepOthers);
	arbre_->afficherSelectionsConsole();
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
/// 
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
