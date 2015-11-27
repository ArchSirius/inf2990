////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__
#include <string>
#include "NodeProperties.h"
#include "Profil.h"
#include "DebugSettings.h"

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY);
	__declspec(dllexport) void zoomerIn();
	__declspec(dllexport) void zoomerIOut();
	__declspec(dllexport) void setInitPos();
	__declspec(dllexport) void translate(float deltaX, float deltaY, float deltaZ);
	__declspec(dllexport) void setInitAngle();
	__declspec(dllexport) void rotate(float deltaX, float deltaY, float deltaZ);
	__declspec(dllexport) void setInitScale();
	__declspec(dllexport) void scale(float deltaX, float deltaY, float deltaZ);
	__declspec(dllexport) void initializeDuplication();
	__declspec(dllexport) void updateDuplication();
	__declspec(dllexport) void endDuplication();
	__declspec(dllexport) void deleteObj();
	__declspec(dllexport) void checkValidPos();
	__declspec(dllexport) bool isMouseOnTable();
	__declspec(dllexport) int getNbNodesSelected();
	__declspec(dllexport) void getSelectedNodeData(NodeProperties* dataRef);
	__declspec(dllexport) void setSelectedNodeData(NodeProperties* dataRef);
	__declspec(dllexport) void setProfileData(Profil* data);
	__declspec(dllexport) void resetMap();

	// Ajouts
	__declspec(dllexport) void addNode(const char* type);
	__declspec(dllexport) void updateNode();
	__declspec(dllexport) void abortTerminalNode();
	__declspec(dllexport) void abortCompositeNode();



	// Sélection
	__declspec(dllexport) void selectObject(bool keepOthers);
	__declspec(dllexport) void selectMultipleObjects(bool keepOthers);
	__declspec(dllexport) void selectAll();

	// Caméra
    __declspec(dllexport) void saveMousePos();
	__declspec(dllexport) void moveCameraMouse();
	__declspec(dllexport) void moveCameraMouseOrbit(int deltaX, int deltaY);

	// save/load
	__declspec(dllexport) void save(const char* filePath);
	__declspec(dllexport) void load(const char* filePath);

	// rectangle
	__declspec(dllexport) void __cdecl preparerRectangleElastique();
	__declspec(dllexport) void __cdecl initialiserRectangleElastique();
	__declspec(dllexport) void __cdecl mettreAJourRectangleElastique();
	__declspec(dllexport) void __cdecl terminerRectangleElastique();

	// Zoom rectangle
	__declspec(dllexport) void __cdecl zoomInRectangle();
	__declspec(dllexport) void __cdecl zoomOutRectangle();

	// Debug
	__declspec(dllexport) void setDebug(DebugSettings* settings);

	//Star Simulation
	__declspec(dllexport) void __cdecl startSimulation();
	__declspec(dllexport) void __cdecl stopSimulation();

	// pour les touches manuelles du robot
	__declspec(dllexport) void __cdecl robotTurnRight();
	__declspec(dllexport) void __cdecl robotTurnLeft();
	__declspec(dllexport) void __cdecl robotReverse();
	__declspec(dllexport) void __cdecl robotForward();
	__declspec(dllexport) void __cdecl robotToggleManualMode();

	//pour la Skybox
	__declspec(dllexport) void __cdecl setEstEnModeTest(bool estEnModeTest);

    // Vues et projections
    __declspec(dllexport) void __cdecl setOrbitView();
    __declspec(dllexport) void __cdecl setOrthoView();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
