﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class Engine : Observable
    {
        protected List<Observer> observers;
        private bool isVueOrtho = true;

        public Engine()
        {
            observers = new List<Observer>();
        }

        public void subscribe(Observer o)
        {
            observers.Add(o);
        }

        public void unsubscribe(Observer o)
        {
            observers.RemoveAll(x => x == o);
        }

        private void notifyObservers()
        {
            foreach (Observer o in observers)
            {
                o.update(this);
            }
        }

        public void zoomerIn()
        {
            FonctionsNatives.zoomerIn();
        }

        public void zoomerOut()
        {
            FonctionsNatives.zoomerOut();
        }

        public void save(string filePath)
        {
	        FonctionsNatives.save(filePath);
        }

        public void load(string filePath)
        {
	        FonctionsNatives.load(filePath);
        }

        public void resetMap()
        {
            FonctionsNatives.resetMap();
            notifyObservers();
        }

        public void setSelectedNodeData(NodeData data)
        {
            FonctionsNatives.setSelectedNodeData(data);
            notifyObservers();
        }

        public void addNode(string type)
        {
	        FonctionsNatives.addNode(type);
            notifyObservers();
        }

        public void deleteObj()
        {
            FonctionsNatives.deleteObj();
            notifyObservers();
        }

        public bool isMouseOnTable()
        {
            return FonctionsNatives.isMouseOnTable() == 1;
        }

        public bool updateNode()
        {
            return FonctionsNatives.updateNode();
        }

        public void duplicate()
        {
            FonctionsNatives.duplicate();
            notifyObservers();
        }

        public void setInitPos()
        {
            FonctionsNatives.setInitPos();
        }

        public void checkValidPos()
        {
            FonctionsNatives.checkValidPos();
        }

        public void deplacerXY(double deplacementX, double deplacementY)
        {
	        FonctionsNatives.deplacerXY(deplacementX, deplacementY);
        }

        public void preparerRectangleElastique()
        {
            FonctionsNatives.preparerRectangleElastique();
        }

        public void prepareSelection()
        {
            FonctionsNatives.prepareSelection();
        }

        public void initialiserRectangleElastique()
        {
            FonctionsNatives.initialiserRectangleElastique();
        }

        public void mettreAJourRectangleElastique()
        {
            FonctionsNatives.mettreAJourRectangleElastique();
        }

        public void terminerRectangleElastique()
        {
            FonctionsNatives.terminerRectangleElastique();
        }

        public void afficherFantome()
        {
            FonctionsNatives.afficherFantome();
        }

        public bool abortCompositeNode()
        {
            return FonctionsNatives.abortCompositeNode();
        }

        public bool abortTerminalNode()
        {
            return FonctionsNatives.abortTerminalNode();
        }

        public void initializeDuplication()
        {
            FonctionsNatives.initializeDuplication();
        }

        public bool updateDuplication()
        {
            return FonctionsNatives.updateDuplication();
        }

        public bool endDuplication()
        {
            return FonctionsNatives.endDuplication();
        }

        public void translate(float deltaX, float deltaY, float deltaZ)
        {
            FonctionsNatives.translate(deltaX, deltaY, deltaZ);
            notifyObservers();
        }

        public void rotate(float deltaX, float deltaY, float deltaZ)
        {
            FonctionsNatives.rotate(deltaX, deltaY, deltaZ);
            notifyObservers();
        }

        public void setInitAngle()
        {
            FonctionsNatives.setInitAngle();
        }

        public void scale(float deltaX, float deltaY, float deltaZ)
        {
            FonctionsNatives.scale(deltaX, deltaY, deltaZ);
            notifyObservers();
        }

        public void setInitScale()
        {
            FonctionsNatives.setInitScale();
        }

        public void selectAll()
        {
            FonctionsNatives.selectAll();
            notifyObservers();
        }

        public void selectObject(bool keepOthers)
        {
            FonctionsNatives.selectObject(keepOthers);
            notifyObservers();
        }

        public void selectMultipleObjects(bool keepOthers)
        {
            FonctionsNatives.selectMultipleObjects(keepOthers);
            notifyObservers();
        }

        public int getNbNodesSelected()
        {
            return FonctionsNatives.getNbNodesSelected();
        }

        public void saveMousePos()
        {
            FonctionsNatives.saveMousePos();
        }

        public void moveCameraMouse(int deltaX, int deltaY)
        {
            if (isVueOrtho)
                FonctionsNatives.moveCameraMouse();
            else
                FonctionsNatives.moveCameraMouseOrbit(deltaX, deltaY);
        }

        public void zoomOutRectangle()
        {
            FonctionsNatives.zoomOutRectangle();
        }

        public void zoomInRectangle()
        {
            FonctionsNatives.zoomInRectangle();
        }

        public void initialiserOpenGL(IntPtr handle)
        {
	        FonctionsNatives.initialiserOpenGL(handle);
        }

        public void libererOpenGL()
        {
            FonctionsNatives.libererOpenGL();
        }

        public void dessinerOpenGL()
        {
            FonctionsNatives.dessinerOpenGL();
        }

        public void animer(double temps)
        {
	        FonctionsNatives.animer(temps);
        }

        public void redimensionnerFenetre(int largeur, int hauteur)
        {
	        FonctionsNatives.redimensionnerFenetre(largeur, hauteur);
        }

        public void getSelectedNodeData(out NodeData dataRef)
        {
            FonctionsNatives.getSelectedNodeData(out dataRef);
        }

        public void startSimulation()
        {
            FonctionsNatives.startSimulation();
        }

        public void stopSimulation()
        {
            FonctionsNatives.stopSimulation();
        }

        public void pauseSimulation()
        {
            FonctionsNatives.pauseSimulation();
        }


        public void unpauseSimulation()
        {
            FonctionsNatives.unpauseSimulation();
        }

        public void setProfileData(ProfileData data)
        {
            FonctionsNatives.setProfileData(data);
        }

        public void setDebug(DebugSettings data)
        {
            FonctionsNatives.setDebug(data);
        }

        public void robotForward()
        {
            FonctionsNatives.robotForward();
        }

        public void robotReverse()
        {
           FonctionsNatives.robotReverse();
        }

        public void robotTurnLeft()
        {
            FonctionsNatives.robotTurnLeft();
        }

        public void robotTurnRight()
        {
           FonctionsNatives.robotTurnRight();
        }

        public void robotToggleManualControl()
        {
            FonctionsNatives.robotToggleManualMode();
        }
        public void setEstEnModeTest(bool estEnModeTest)
        {
            FonctionsNatives.setEstEnModeTest(estEnModeTest);
        }
        public void  toggleAmbiante()
        {
            FonctionsNatives.toggleAmbiante();
        }
        public void toggleDirectional()
        {
            FonctionsNatives.toggleDirectional();
        }
        public void toggleSpots()
        {
            FonctionsNatives.toggleSpots();
        }
        public void LumiereOff()
        {
            FonctionsNatives.LumiereOff();
        }

        // LIVRABLE 3 : Vues orbite / orthographique
        public void SetOrbitView()
        {
            isVueOrtho = false;
            FonctionsNatives.setOrbitView();
        }

        public void SetOrthoView()
        {
            isVueOrtho = true;
            FonctionsNatives.setOrthoView();
        }

        public void playMusicSimulation()
        {
            FonctionsNatives.playMusicSimulation();
        }

        public void playMusicEditor()
        {
            FonctionsNatives.playMusicEditor();
        }

        public void playSoundTurn(bool pause)
        {
            FonctionsNatives.playSoundTurn(pause);
        }

        static partial class FonctionsNatives
        {
            // Fonctions pour EditorController.cs
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerIn();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerOut();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void save(string filePath);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void load(string filePath);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void resetMap();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setSelectedNodeData(NodeData data);

            // Général
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deleteObj();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int isMouseOnTable();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool updateNode();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void duplicate();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitPos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void checkValidPos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);

            // Rectangle Elastique
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void preparerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();

            // Lignes
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void afficherFantome();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool abortCompositeNode();

            // Murs
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool abortTerminalNode();

            // Duplicate
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initializeDuplication();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool updateDuplication();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool endDuplication();

            // Move 
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void translate(float deltaX, float deltaY, float deltaZ);

            // Rotation
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void rotate(float deltaX, float deltaY, float deltaZ);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitAngle();

            // Scale
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void scale(float deltaX, float deltaY, float deltaZ);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitScale();

            // Selection
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectAll();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectObject(bool keepOthers);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectMultipleObjects(bool keepOthers);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int getNbNodesSelected();

            // Tool Context
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void saveMousePos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void moveCameraMouse();
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void moveCameraMouseOrbit(int deltaX, int deltaY);            

            // Zoom Rectangle
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomOutRectangle();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomInRectangle();

            // Editor.cs
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserOpenGL(IntPtr handle);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void libererOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(double temps);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void redimensionnerFenetre(int largeur, int hauteur);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void getSelectedNodeData(out NodeData dataRef);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void pauseSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void unpauseSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void startSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void stopSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setProfileData(ProfileData data);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setDebug(DebugSettings data);

            // Mode manuel
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void robotForward();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void robotReverse();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void robotTurnLeft();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void robotTurnRight();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void robotToggleManualMode();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setEstEnModeTest(bool estEnModeTest);

            // Modes lumiere
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void toggleAmbiante();
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void toggleDirectional();
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void toggleSpots();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void LumiereOff();

            // Vues et projections
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setOrbitView();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setOrthoView();

            //FMOD
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void playMusicSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void playMusicEditor();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void playSoundTurn(bool pause);
            

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void prepareSelection();

        }
    }
}
