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
	__declspec(dllexport) void translate();
	__declspec(dllexport) void rotate();
	__declspec(dllexport) void scale();
	__declspec(dllexport) void duplicate();
	// <f3.2.3_ajoutPoteaux>
	__declspec(dllexport) void addNode(const char* type);
	__declspec(dllexport) void selectObject(bool keepOthers);

}

#endif // __FACADE_INTERFACE_NATIVE_H__
