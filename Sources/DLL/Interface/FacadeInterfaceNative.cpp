////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include <string>

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
		FacadeModele::obtenirInstance()->addNode(nodeType);
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
	__declspec(dllexport) void __cdecl scale()
	{
		FacadeModele::obtenirInstance()->doScaling();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) 
	///
	/// Cette fonction permet d'effectuer une duplication des objets s�lectionn�s
	///
	/// @return 
	///
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl duplicate()
	{
		FacadeModele::obtenirInstance()->doDuplication();
	}

}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////

