////////////////////////////////////////////////
/// @file FacadeInterfaceNative.cpp
/// @author INF2990
/// @date 2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include <string>
#include <memory>

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include "BancTests.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fen�tre
	/// identifi�e par le handle pass� en param�tre.  Cette fonction doit
	/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
	/// C++ s'attend � avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction lib�re le contexte OpenGL. Cette fonction doit �tre la
	/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
		// d�sinitialisation du contexte OpenGL aura pour cons�quence que la
		// lib�ration des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la sc�ne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit �tre appel�e lorsque la fen�tre est
	/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fen�tre.
	/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
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
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arri�re sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'ex�cuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet de deplacer la camera en XY
	///
	/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerXY(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->deplacerXY(deplacementX, deplacementY);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de zoom en avant
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomerIn()
	{
		FacadeModele::obtenirInstance()->zoomerIn();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de zoom Out
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomerOut()
	{
		FacadeModele::obtenirInstance()->zoomerOut();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void addNode(int x, int y, int z)
	///
	/// Cette fonction ajoute un cylindre � la sc�ne
	///
	/// @return Aucune
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void addNode(const char* type)
	{
		std::string nodeType(type);
		if (nodeType == ArbreRenduINF2990::NOM_TABLE ||
			nodeType == ArbreRenduINF2990::NOM_LIGNE)
			FacadeModele::obtenirInstance()->addComposite(nodeType);
		else
			FacadeModele::obtenirInstance()->addNode(nodeType);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void updateNode()
	///
	/// Cette fonction sert de deuxi�me �tape � l'ajout de noeud (mur, ligne)
	///
	/// @return Aucune
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void updateNode()
	{
		FacadeModele::obtenirInstance()->updateNode();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void FacadeModele::abortTerminalNode()
	///
	/// Annule la cr�ation d'un noeud terminal fant�me
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void abortTerminalNode()
	{
		FacadeModele::obtenirInstance()->abortTerminalNode();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void FacadeModele::abortTerminalNode()
	///
	/// Annule la cr�ation d'un noeud composite fant�me
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void abortCompositeNode()
	{
		FacadeModele::obtenirInstance()->abortCompositeNode();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction fait marque les objets point�s par la souris comme
	/// s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectObject(bool keepOthers)
	{
		FacadeModele::obtenirInstance()->selectObject(keepOthers);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction fait marque les objets point�s par la souris comme
	/// s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectMultipleObjects(bool keepOthers)
	{
		FacadeModele::obtenirInstance()->selectMultipleObjects(keepOthers);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void selectAll()
	///
	/// Cette fonction s�lectionne tous les noeuds
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void selectAll()
	{
		FacadeModele::obtenirInstance()->selectAll();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'enregistrer le position des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setInitPos()
	{
		FacadeModele::obtenirInstance()->doSetInitPos();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'effectuer une translation des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translate(float deltaX, float deltaY, float deltaZ)
	{
		FacadeModele::obtenirInstance()->doTranslation(deltaX, deltaY, deltaZ);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'enregistrer l'angle des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setInitAngle()
	{
		FacadeModele::obtenirInstance()->doSetInitAngle();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'effectuer une rotation des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rotate(float deltaX, float deltaY, float deltaZ)
	{
		FacadeModele::obtenirInstance()->doRotation(deltaX, deltaY, deltaZ);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'effectuer une mise � l'�chelle des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl scale(float deltaX, float deltaY, float deltaZ)
	{
		FacadeModele::obtenirInstance()->doScaling(deltaX, deltaY, deltaZ);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de d�buter le procesus de duplication
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initializeDuplication()
	{
		FacadeModele::obtenirInstance()->initializeDuplication();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de mettre � jour le procesus de duplication
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void updateDuplication()
	{
		FacadeModele::obtenirInstance()->updateDuplication();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de terminer le procesus de duplication
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void endDuplication()
	{
		FacadeModele::obtenirInstance()->endDuplication();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de sauvegarder les donn�es
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl save(const char* filePath)
	{
		FacadeModele::obtenirInstance()->save(filePath);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de charger un fichier sauvegard�
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl load(const char* filePath)
	{
		FacadeModele::obtenirInstance()->load(filePath);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'effectuer une suppression des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deleteObj()
	{
		FacadeModele::obtenirInstance()->doDeleteObj();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction v�rifie si les objets sont � une position valide.
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl checkValidPos()
	{
		FacadeModele::obtenirInstance()->checkValidPos();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'enregistrer l'�chelle des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setInitScale()
	{
		FacadeModele::obtenirInstance()->doSetInitScale();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction v�rifie si le curseur est au-dessus de la table.
	///
	/// @return True si oui, false sinon.
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl isMouseOnTable()
	{
		return FacadeModele::obtenirInstance()->isMouseOnTable();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de d�terminer le nombre de noeuds s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int getNbNodesSelected()
	{
		return FacadeModele::obtenirInstance()->getNbNodesSelected();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'aller cherche la position du noeud s�lectionn�
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void getSelectedNodeData(NodeProperties* dataRef)
	{
		FacadeModele::obtenirInstance()->getSelectedNodeData(dataRef);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'aller cherche la position du noeud s�lectionn�
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setSelectedNodeData(NodeProperties* dataRef)
	{
		FacadeModele::obtenirInstance()->setSelectedNodeData(dataRef);
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de changer le profil
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setProfileData(Profil* data)
	{
		FacadeModele::obtenirInstance()->setProfileData(std::make_shared<Profil>(*data));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de remettre la map dans son �tat initial
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void resetMap()
	{
		FacadeModele::obtenirInstance()->resetMap();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn preparerRectangleElastique
	///
	/// Cette fonction permet de garder en memoire le futur point d'ancrage
	/// du prochain rectangle elastique.
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl preparerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->preparerRectangleElastique();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'initialiser rectangleElastque
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserRectangleElastique()
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElastique();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de mettre a jour rectangle 
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl mettreAJourRectangleElastique()
	{
		FacadeModele::obtenirInstance()->mettreAJourRectangleElastique();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de terminer rectangle 
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl terminerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique();
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de sauvegarder les positions initiales de la vue
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setViewInit()
	{
		FacadeModele::obtenirInstance()->setViewInit();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de bouger la vue avec la souris
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl moveCameraMouse()
	{
		FacadeModele::obtenirInstance()->moveCameraMouse();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de faire le zoomOut avec le rectangle elastique
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOutRectangle()
	{
		FacadeModele::obtenirInstance()->zoomOutRectangle();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet de faire le zoomIn avec le rectangle elastique
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomInRectangle()
	{
		FacadeModele::obtenirInstance()->zoomInRectangle();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'assigner l'activation d'un d�clancheur de console
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setDeclencheur(const char* name, bool enabled)
	{
		FacadeModele::obtenirInstance()->setDeclencheur(name, enabled);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'assigner l'activation de la sortie journal de console
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setLogOutput(bool enabled)
	{
		FacadeModele::obtenirInstance()->setLogOutput(enabled);
	}

	////////////////////////////////////////////////////////////////////////
	///@fn __declspec(dllexport) 
	///
	/// Cette fonction permet de commencer la simulation
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl startSimulation()
	{
		FacadeModele::obtenirInstance()->startSimulation();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de terminer la simulation
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl stopSimulation()
	{
		FacadeModele::obtenirInstance()->stopSimulation();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de tourner le robot a droite
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl robotTurnRight()
	{
		FacadeModele::obtenirInstance()->robotTurnRight();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de tourner le robot a gauche
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl robotTurnLeft()
	{
		FacadeModele::obtenirInstance()->robotTurnLeft();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de faire reculer le robot
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl robotReverse()
	{
		FacadeModele::obtenirInstance()->robotReverse();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de faire avancer le robot
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl robotForward()
	{
		FacadeModele::obtenirInstance()->robotForward();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)
	///
	/// Cette fonction permet de d'entrer ou sortir du mode manuel
	///
	/// @return
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl robotToggleManualMode()
	{
		FacadeModele::obtenirInstance()->robotToggleManualMode();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
