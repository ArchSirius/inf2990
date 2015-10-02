///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

*/

namespace vue {
	class Camera;
}

#include <windows.h>
#include <cassert>
#include <fstream>

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
//test only
#include "Visitor\HelloTool.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <functional>

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_;

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };



////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
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
/// Cette fonction libère l'instance unique de cette classe.
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
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	rectangleElastique_ = false;

	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumières
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lumière ambiante "globale"
	// Attention :
	//La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glm::vec4 ambiant{ 0.2f, 0.2, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = std::make_unique<ArbreRenduINF2990>();
	arbre_->initialiser();
	HelloTool* tool = new HelloTool();
	arbre_->accept(*tool);

	// Inspiré de http://stackoverflow.com/questions/8690619/how-to-get-screen-resolution-in-c
	RECT panel;
	GetWindowRect(hWnd, &panel);

	// On crée une vue par défaut.
	vue_ = std::make_unique<vue::VueOrtho>(
		vue::Camera{ 
		glm::dvec3(195, 75, 200), glm::dvec3(195, 75, 0),	// WTF
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionOrtho{ 
				0, panel.right, 0, panel.bottom,
				1, 1000, 1, 10000, 1.25,
				-100, 100, -100, 100 }
	);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
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
	}
	

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la scène
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumière.
	glm::vec4 position{ 0, 0, 1, 0 };
	
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumière
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));

	// Afficher la scène.
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
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);
	// Mise à jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerXY(double deplacementX, double deplacementY)
///
/// Pour le deplacement de la vue
///
/// @param[double] deplacerX : selon l'axe des X
///
/// @param[double] deplacerY : selon l'axe des Y
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
/// Crée un noeud et l'ajoute à l'arbre, avec la table comme parent.
/// Lui donne ensuite les coordonnées nécessaire à son affichage.
///
/// @param[] std::string type Le type du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::addNode(std::string type)
{
	auto newNode = arbre_->ajouterNouveauNoeud(
		ArbreRenduINF2990::NOM_TABLE, 
		type);
	
	newNode->assignerEstSelectionnable(true);

	GLdouble worldX, worldY, worldZ;	//variables to hold world x,y,z coordinates
	convertMouseToClient(worldX, worldY, worldZ);
	newNode->assignerPositionRelative(glm::dvec3(worldX, worldY, worldZ));
	newNode->assignerPositionInitiale(glm::dvec3(worldX, worldY, worldZ));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::convertMouseToClient(
///			GLdouble& worldX, GLdouble& worldY, GLdouble& worldZ)
///
/// Transforme les données de la position de la souris en coordonnées
/// utilisable dans la fenêtre
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::convertMouseToClient(
	GLdouble& worldX, GLdouble& worldY, GLdouble& worldZ) 
{
	/*
	* Procédure et explications tirées de http://nehe.gamedev.net/article/using_gluunproject/16013/
	*/

	GLint viewport[4];					//var to hold the viewport info
	GLdouble modelview[16];				//var to hold the modelview info
	GLdouble projection[16];			//var to hold the projection matrix info
	GLfloat winX, winY, winZ;			//variables to hold screen x,y,z coordinates

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

	//get the world coordinates from the screen coordinates
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::convertMouseToClient()
///
/// Transforme les données de la position de la souris en coordonnées
/// utilisable dans la fenêtre
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
glm::ivec2 FacadeModele::getCoordinate()
{
	/*
	* Procédure et explications tirées de http://nehe.gamedev.net/article/using_gluunproject/16013/
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

	return(glm::ivec2(int(worldX), int(worldY)));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectObject()
///
/// Pour chaque élément de l'arbre, vérifie s'il est touché par la souris
/// et, le cas échéant, le signale comme sélectionné
///
/// @param[] aucun
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
/// Pour chaque élément de l'arbre, vérifie s'il est touché par la souris
/// et, le cas échéant, le signale comme sélectionné
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectObject(bool keepOthers)
{
	GLdouble x, y, z;
	convertMouseToClient(x, y, z);
	if (!keepOthers)
		arbre_->deselectionnerTout();
	arbre_->assignerSelectionEnfants(x, y, z, keepOthers);
	arbre_->afficherSelectionsConsole();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) doSetInitPos()
///
/// Cette fonction permet d'enregistrer la position des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitPos()
{
	auto visitor = PositionTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) doSetInitScale()
///
/// Cette fonction permet d'enregistrer l'échelle des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitScale()
{
	auto visitor = SetScaleTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'effectuer une translation des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doTranslation(float deltaX, float deltaY, float deltaZ)
{
	auto visitor = TranslateTool(deltaX, deltaY, deltaZ);
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'enregistrer l'angle des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doSetInitAngle()
{
	auto visitor = AngleTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'effectuer une rotation des objets sélectionnés
///
/// @return 
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
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'effectuer une mise à l'échelle des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doScaling(float deltaX, float deltaY, float deltaZ)
{
	auto visitor = ScaleTool(deltaX, deltaY, deltaZ);
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'effectuer une duplication des objets sélectionnés
///
/// @return 
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

void FacadeModele::updateDuplication()
{
	// Obtenir les coordonnées du curseur
	glm::dvec3 cursor;
	convertMouseToClient(cursor[0], cursor[1], cursor[2]);

	// Mise à jour du tampon
	_duplicator->updateBuffer(cursor);
}

void FacadeModele::endDuplication()
{
	_duplicator->confirmBuffer();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet d'effectuer une suppression des objets sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::doDeleteObj()
{
	auto visitor = DeleteTool();
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de déterminer le nombre de noeuds sélectionnés
///
/// @return 
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
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de déterminer le nombre de noeuds sélectionnés
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::getSelectedPosition(NodeProperties* dataRef)
{
	auto visitor = GetDataTool(dataRef);
	obtenirArbreRenduINF2990()->accept(visitor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de sauvegarder l'arbre de rendu dans un fichier
///
/// @return 
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
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de charger un arbre de rendu depuis un fichier
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::load(std::string filePath)
{
	std::function<void(const rapidjson::Value&)> loadNode = [&](const rapidjson::Value& node) {

		auto type = std::string(node["type"].GetString());
		auto parent_type = std::string(node["parent_type"].GetString());

		if (type != "racine") {
			auto newNode = arbre_->ajouterNouveauNoeud(parent_type, type);

			newNode->assignerEstSelectionnable(true);

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
		}

		if (node.HasMember("children")) {
			for (auto& child : node["children"]) {
				loadNode(child);
			}
		}
	
	};

	// Vider la table
	arbre_->vider();

	// Tiré de: https://github.com/pah/rapidjson/blob/master/doc/stream.md
	FILE* fp = fopen(filePath.c_str(), "rb");

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document document;
	document.ParseStream(is);

	assert(document.IsObject());
	assert(document.HasMember("children"));

	loadNode(document);

	fclose(fp);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction vérifie si les objets sont à une position valide.
///
/// @return 
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
/// @fn __declspec(dllexport) 
///
/// Cette fonction vérifie si le curseur est au-dessus de la table.
///
/// @return True si oui, false sinon.
///
///////////////////////////////////////////////////////////////////////
bool FacadeModele::isMouseOnTable()
{
	glm::dvec3 cursor;
	convertMouseToClient(cursor[0], cursor[1], cursor[2]);
	return isOnTable(cursor);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction vérifie si un point est au-dessus de la table.
///
/// @return True si oui, false sinon.
///
///////////////////////////////////////////////////////////////////////
bool FacadeModele::isOnTable(glm::dvec3 point)
{
	auto table = arbre_->chercher(arbre_->NOM_TABLE);
	return table->clickHit(point[0], point[1], point[2]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de sauvegarder les positions initiales de 
/// la vue et de la caméra
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::setViewInit()
{
	convertMouseToClient(viewInit_[0], viewInit_[1], viewInit_[2]);
	cameraPosInit_	  = vue_->obtenirCamera().obtenirPosition();
	cameraTargetInit_ = vue_->obtenirCamera().obtenirPointVise();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) 
///
/// Cette fonction permet de changer la position de la vue (avec caméra)
///
/// @return 
///
///////////////////////////////////////////////////////////////////////
void FacadeModele::moveCameraMouse()
{
	// On prend la différence entre la position de la souris et
	// la position initiale de la vue (vecteur de déplacement)
	glm::dvec3 delta;
	convertMouseToClient(delta[0], delta[1], delta[2]);
	delta -= viewInit_;
	delta[2] = 0;	// On ignore les Z

	// Nouvelle position de la caméra
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
	ancrage_ = getCoordinate();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRectangleElastique()
///
/// Crée un petit rectangle elastique
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
// initialiser rectangle
void FacadeModele::initialiserRectangleElastique()
{
	rectangleElastique_= true;
	// ancrage_ = getCoordinate();	// Maintenant dans preparerRectangleElastique
	olderPos_ = ancrage_;
	oldPos_ = ancrage_;
	aidegl::initialiserRectangleElastique(ancrage_);

}

// mettre a jour rectangle
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mettreAJourRectangleElastique()
///
/// Pour chaque élément de l'arbre, vérifie s'il est touché par la souris
/// et, le cas échéant, le signale comme sélectionné
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::mettreAJourRectangleElastique()
{

	glm::ivec2 temp = getCoordinate();
	aidegl::mettreAJourRectangleElastique(ancrage_, olderPos_, temp);
	olderPos_ = oldPos_;
	oldPos_ = temp;


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::terminerRectangleElastique()
///
/// Pour chaque élément de l'arbre, vérifie s'il est touché par la souris
/// et, le cas échéant, le signale comme sélectionné
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangleElastique()
{
	
		rectangleElastique_ = false;
		oldPos_ = getCoordinate();
		aidegl::terminerRectangleElastique(ancrage_, oldPos_);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectMultipleObjects(bool keepOthers)
///
/// Pour chaque élément de l'arbre, vérifie s'il est touché par la souris
/// et, le cas échéant, le signale comme sélectionné
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectMultipleObjects(bool keepOthers)
{
	if (!keepOthers)
		arbre_->deselectionnerTout();
	arbre_->assignerSelectionEnfants(ancrage_, oldPos_, keepOthers);
	arbre_->afficherSelectionsConsole();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
