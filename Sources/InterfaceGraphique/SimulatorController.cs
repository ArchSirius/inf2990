using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using Forms = System.Windows.Forms;
using Microsoft.Win32;
using InterfaceGraphique;
using Newtonsoft.Json.Linq;

namespace InterfaceGraphique
{
    class SimulatorController
    {
        private Engine engine;
        private Tools.ToolContext toolContext;
        private KeyBindings keybindings;
        private Settings settings;
        private bool manualModeEnabled = false;
        private bool modeSimulation = true;
        private bool start = true;
        private bool isChanged = false;
        private bool isManualPressed = false;
        private bool mouseClicked = false;
        public static bool dragEnter = false;
        private bool clicIsLeft;
        int xPos = Forms.Control.MousePosition.X;
        int yPos = Forms.Control.MousePosition.Y;


        public SimulatorController(Engine _engine)
        {
            engine = _engine;
            var selectTool = new Tools.Selection(toolContext, engine);

            toolContext = new Tools.ToolContext(selectTool, engine);
            keybindings = (new ConfigPanelData()).LoadKeybindings();
            settings = (new ConfigPanelData()).LoadSettings();
        }

        public void InitializeGamePanel(IntPtr source, int width, int weight)
        {
            engine.setDebug(settings.getDebugSettings());
            engine.initialiserOpenGL(source);
            engine.dessinerOpenGL();

            /// Pour une raison inconnue, si on fait la fonction moins de 4 fois, la
            /// fenêtre n'aura pas fait un redimensionnement suffisant. CEPENDANT, le
            /// redimensionnement OnResize est correct, puisqu'il s'appelle 60 fois/s.

            for (int i = 0; i < 30; i++)
                engine.redimensionnerFenetre(width, weight);

            if (start)
            {
                OpenFile();
                start = false;
            }

            engine.startSimulation();
        }

        public void ResizeGamePanel(int width, int weight)
        {
            /// Si on met ça ici, et dans InitializeGamePanel, on peut retirer celui
            /// de FrameUpdate. PAR CONTRE, le premier resize est étrange.       
            for (int i = 0; i < 10; i++)
                engine.redimensionnerFenetre(width, weight);
        }

        public void ChangeProfile(Profil profile)
        {
            engine.setProfileData(profile.GetData());
        }

        public void KeyPressed(object o, KeyEventArgs e)
        {
            var convert = new KeyConverter();
            if (e.Key == Key.Left)
            {
                Debug.Write("Deplacement camera gauche");
                engine.deplacerXY(-0.10, 0.0);
            }
            else if (e.Key == Key.Right)
            {
                Debug.Write("Deplacement camera droite");
                engine.deplacerXY(0.10, 0.0);
            }
            else if (e.Key == Key.Up)
            {
                Debug.Write("Deplacement camera haut");
                engine.deplacerXY(0.0, 0.10);
            }
            else if (e.Key == Key.Down)
            {
                Debug.Write("Deplacement camera bas");
                engine.deplacerXY(0.0, -0.10);
            }
            else if (e.Key == Key.OemMinus || e.Key == Key.Subtract)
            {
                Debug.Write("ZoomOut");
                engine.zoomerOut();
            }
            else if (e.Key == Key.OemPlus || e.Key == Key.Add)
            {
                Debug.Write("ZoomIN");
                engine.zoomerIn();
            }
            else if (e.Key == Key.Escape)
            {
                toolContext.esc();
            }
            else if (e.Key == Key.A && System.Windows.Forms.Control.ModifierKeys == System.Windows.Forms.Keys.Control)
            {
                engine.selectAll();
            }
            else if (modeSimulation && e.Key == (Key)convert.ConvertFromString(keybindings.Toggle) && !isManualPressed)
            {
                engine.robotToggleManualControl();
                manualModeEnabled = !manualModeEnabled;
                isManualPressed = true;
            }

        }
        public void KeyUnPressed(object o, KeyEventArgs e)
        {
            var convert = new KeyConverter();
            if (e.Key == (Key)convert.ConvertFromString(keybindings.Toggle))
            {
                isManualPressed = false;
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::DetectUserInput()
        ///
        /// Cette fonction détacte quand on actionne une touche du mode manuel.
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void DetectUserInput()
        {
            if (modeSimulation)
            {
                var convert = new KeyConverter();

                if (manualModeEnabled == true)
                {
                    if (Keyboard.IsKeyDown((Key)convert.ConvertFromString(keybindings.Forward)))
                    {
                        engine.robotForward();
                    }
                    if (Keyboard.IsKeyDown((Key)convert.ConvertFromString(keybindings.Reverse)))
                    {
                        engine.robotReverse();
                    }
                    if (Keyboard.IsKeyDown((Key)convert.ConvertFromString(keybindings.TurnLeft)))
                    {
                        engine.robotTurnLeft();
                    }
                    if (Keyboard.IsKeyDown((Key)convert.ConvertFromString(keybindings.TurnRight)))
                    {
                        engine.robotTurnRight();
                    }
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::OpenFile()
        ///
        /// Fonction d'ouvrir un fichier de sauvegarde
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void OpenFile()
        {
            var exePath = System.Reflection.Assembly.GetEntryAssembly().Location;
            var savePath = exePath.Substring(0, exePath.Length - 22) + "zones";

            var dialog = new OpenFileDialog();
            dialog.InitialDirectory = savePath;

            if (dialog.ShowDialog() == true)
            {
                engine.load(dialog.FileName);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::MouseButtonUp()
        ///
        /// Cette fonction bind des touche du clavier à des actions
        ///
        /// @param[in] o : celui qui a envoyé l'action
        /// @param[in] e : Les données de l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MouseButtonUp(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                // Si on sort d'un drag & drop
                if (dragEnter)
                {
                    toolContext.LeftMouseReleased(e);
                }

                // Si c'est un clic complet
                else
                {
                    toolContext.LeftMouseFullClicked(e);
                }
                mouseClicked = false;
                dragEnter = false;
            }

            else if (e.Button == Forms.MouseButtons.Right)
            {
                mouseClicked = false;
                dragEnter = false;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::MouseMove()
        ///
        /// Cette fonction bind les outils quand la souris bouge
        ///
        /// @param[in] o : celui qui a envoyé l'action
        /// @param[in] e : Les données de l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MouseMove(Object o, Forms.MouseEventArgs e)
        {
            toolContext.MouseMove(e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::MouseMoved()
        ///
        /// Cette fonction retourne le déplacement e la souris
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool MouseMoved(int x, int y, int delta)
        {
            return (Math.Abs(x - Forms.Control.MousePosition.X) >= delta || Math.Abs(y - Forms.Control.MousePosition.Y) >= delta);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::RouletteSouris()
        ///
        /// Cette fonction bind la roulette de la sourie
        ///
        /// @param[in] o : celui qui a envoyé l'action
        /// @param[in] e : Les données de l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RouletteSouris(Object o, Forms.MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                engine.zoomerIn();
            }
            else if (e.Delta < 0)
            {
                engine.zoomerOut();
            }

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::select()
        ///
        /// Active l'outils de sélection
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void select()
        {
            var selectTool = new Tools.Selection(toolContext, engine);

            toolContext.ChangeState(selectTool);
            isChanged = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::DetectDrag()
        ///
        /// Cette fonction détacte quand on déplace un noeud
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void DetectDrag()
        {
            if (mouseClicked)
            {
                if (MouseMoved(xPos, yPos, 4) || dragEnter)
                {
                    if (mouseClicked)
                    {
                        int origX = Forms.Control.MousePosition.X;
                        int origY = Forms.Control.MousePosition.Y;

                        if (MouseMoved(xPos, yPos, 1))
                        {
                            toolContext.Dragging(Forms.Control.MousePosition.X - origX, origY - Forms.Control.MousePosition.Y, 0, clicIsLeft);
                            xPos = Forms.Control.MousePosition.X;
                            yPos = Forms.Control.MousePosition.Y;
                        }
                        dragEnter = true;
                    }
                }
            }

        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void SimulatorController::MouseButtonDown()
        ///
        /// Cette fonction bind des touche du clavier à des actions
        ///
        /// @param[in] o : celui qui a envoyé l'action
        /// @param[in] e : Les données de l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MouseButtonDown(Object o, Forms.MouseEventArgs e)
        {
            xPos = Forms.Control.MousePosition.X;
            yPos = Forms.Control.MousePosition.Y;

            if (e.Button == Forms.MouseButtons.Left)
            {
                clicIsLeft = true;
                toolContext.LeftMousePressed(e);

                mouseClicked = true;
                DetectDrag();


            }
            else if (e.Button == Forms.MouseButtons.Right)
            {
                clicIsLeft = false;

                toolContext.RightMouseClicked(e);

                mouseClicked = true;
                DetectDrag();
            }
        }

    }
}
