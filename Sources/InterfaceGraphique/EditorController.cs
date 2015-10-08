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

namespace InterfaceGraphique
{
    class EditorController
    {
        public delegate void SelectedEventHandler(int nbSelected);
        public event SelectedEventHandler SelectedEvent;

        public delegate void NodeChangedEventHandler();
        public event NodeChangedEventHandler NodeChangedEvent;

        private bool mouseClicked = false;
        private Tools.ToolContext toolContext;
        public static bool dragEnter = false;
        private bool clicIsLeft;
        private string loadedFile;
        private bool isChanged = false;

        int xPos = Forms.Control.MousePosition.X;
        int yPos = Forms.Control.MousePosition.Y;

        public EditorController()
        {
            var selectTool = new Tools.Selection(toolContext);
            selectTool.SelectedEvent += OnObjectSelected;

            toolContext = new Tools.ToolContext(selectTool);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::KeyPressed()
        ///
        /// Cette fonction bind des touche du clavier à des actions
        ///
        /// @param[in] o : celui qui a envoyé l'action
        /// @param[in] e : Les données de l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void KeyPressed(object o, KeyEventArgs e)
        {
            if (e.Key == Key.Left)
            {
                Debug.Write("Deplacement camera gauche");
                FonctionsNatives.deplacerXY(-0.10, 0.0);
            }
            else if (e.Key == Key.Right)
            {
                Debug.Write("Deplacement camera droite");
                FonctionsNatives.deplacerXY(0.10, 0.0);
            }
            else if (e.Key == Key.Up)
            {
                Debug.Write("Deplacement camera haut");
                FonctionsNatives.deplacerXY(0.0, 0.10);
            }
            else if (e.Key == Key.Down)
            {
                Debug.Write("Deplacement camera bas");
                FonctionsNatives.deplacerXY(0.0, -0.10);
            }
            else if (e.Key == Key.OemMinus || e.Key == Key.Subtract)
            {
                Debug.Write("ZoomOut");
                FonctionsNatives.zoomerOut();
            }
            else if (e.Key == Key.OemPlus || e.Key == Key.Add)
            {
                Debug.Write("ZoomIN");
                FonctionsNatives.zoomerIn();
            }
            else if (e.Key == Key.Escape)
            {
                toolContext.esc();
            }
            else if (e.Key == Key.A && System.Windows.Forms.Control.ModifierKeys == System.Windows.Forms.Keys.Control)
            {
                FonctionsNatives.selectAll();
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::MouseButtonDown()
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


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::MouseButtonUp()
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
        /// @fn void EditorController::MouseMove()
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
        /// @fn void EditorController::MouseMoved()
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
        /// @fn void EditorController::RouletteSouris()
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
                FonctionsNatives.zoomerIn();
            }
            else if (e.Delta < 0)
            {
                FonctionsNatives.zoomerOut();
            }

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::DetectDrag()
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
        /// @fn void EditorController::create()
        ///
        /// Active l'outils de création
        /// 
        /// @param[in] nodeType : le type de noeud
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void create(string nodeType)
        {
            switch(nodeType)
            {
                case Tools.CreatePoteau.nodeType:
                    toolContext.ChangeState(new Tools.CreatePoteau(toolContext));
                    break;

                case Tools.CreateLigne.nodeType:
                    toolContext.ChangeState(new Tools.CreateLigne(toolContext));
                    break;

                case Tools.CreateMur.nodeType:
                    toolContext.ChangeState(new Tools.CreateMur(toolContext));
                    break;

                default:
                    break;
            }
            isChanged = true;
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::translate()
        ///
        /// Active l'outils de translation
        ///
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void translate()
        {
            var tool = new Tools.Move(toolContext);
            tool.NodeChangedEvent += OnNodeChanged;

            toolContext.ChangeState(tool);
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::select()
        ///
        /// Active l'outils de sélection
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void select()
        {
            var selectTool = new Tools.Selection(toolContext);
            selectTool.SelectedEvent += OnObjectSelected;

            toolContext.ChangeState(selectTool);
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::zoomRectangle()
        ///
        /// Active l'outils de zoom élastique
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void zoomRectangle()
        {
            toolContext.ChangeState(new Tools.ZoomRectangle(toolContext));
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::rotate()
        ///
        /// Active l'outils de rotation
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void rotate()
        {
            var tool = new Tools.Rotation(toolContext);
            tool.NodeChangedEvent += OnNodeChanged;

            toolContext.ChangeState(tool);
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::scale()
        ///
        /// Active l'outils de mise à l'échelle
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void scale()
        {
            var tool = new Tools.Scale(toolContext);
            tool.NodeChangedEvent += OnNodeChanged;

            toolContext.ChangeState(tool);
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::duplicate()
        ///
        /// Active l'outils de duplication
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void duplicate()
        {
            toolContext.ChangeState(new Tools.Duplicate(toolContext));
            FonctionsNatives.initializeDuplication();
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::deleteObj()
        ///
        /// Supprime un noeud
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void deleteObj()
        {
            FonctionsNatives.deleteObj();
            isChanged = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::SaveAs()
        ///
        /// Fonction d'enregistrer dans un nouveau fichier
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void SaveAs()
        {
            var exePath = Environment.CurrentDirectory;
            var savePath = exePath.Substring(0, exePath.Length-3) + "zones";

            var dialog = new SaveFileDialog();
            dialog.InitialDirectory = savePath;

            if (dialog.ShowDialog() == true)
            {
                if (System.IO.Path.GetDirectoryName(dialog.FileName) != savePath)
                {
                    System.Windows.MessageBox.Show("Il n’est pas possible d'enregistrer ailleur que dans le répertoire 'zones' parceque les exigences du projet sont connes.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else if (dialog.FileName.Contains("Default.scene"))
                {
                    System.Windows.MessageBox.Show("Il n’est pas possible de modifier la zone de simulation par défaut.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else
                {
                    FonctionsNatives.save(dialog.FileName);
                    loadedFile = dialog.FileName;
                    isChanged = false;
                }
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::Save()
        ///
        /// Fonction d'enregistrer dans le fichier actuel
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Save()
        {
            if (loadedFile == null)
            {
                SaveAs();
            }
            else if (loadedFile.Contains("Default.scene"))
            {
                System.Windows.MessageBox.Show("Il n’est pas possible de modifier la zone de simulation par défaut.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                FonctionsNatives.save(loadedFile);
                isChanged = false;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::OpenFile()
        ///
        /// Fonction d'ouvrir un fichier de sauvegarde
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void OpenFile()
        {
            if (isChanged)
            {
                var choice = System.Windows.MessageBox.Show("Voulez-vous enregistrer vos modifications?", "Modifications", MessageBoxButton.YesNoCancel);

                if (choice == MessageBoxResult.Cancel)
                {
                    return;
                }

                if (choice == MessageBoxResult.Yes)
                {
                    Save();
                }
            }

            var exePath = Environment.CurrentDirectory;
            var savePath = exePath.Substring(0, exePath.Length - 3) + "zones";

            var dialog = new OpenFileDialog();
            dialog.InitialDirectory = savePath;

            if (dialog.ShowDialog() == true)
            {
                FonctionsNatives.load(dialog.FileName);
                loadedFile = dialog.FileName;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::InjectProperties()
        ///
        /// Permet d'injecter des propriété directement dans un noeud
        /// sans passer par les outils
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InjectProperties(NodeData data)
        {
            FonctionsNatives.setSelectedNodeData(data);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::OnObjectSelected()
        ///
        /// Événement quand des objets sont sélectionnés
        /// 
        /// @param[in] nbSelected : le nombre de noeud sélectionnés
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void OnObjectSelected(int nbSelected)
        {
            if (SelectedEvent != null)
                SelectedEvent(nbSelected);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::OnNodeChanged()
        ///
        /// Événement quand un noeud change
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void OnNodeChanged()
        {
            if (NodeChangedEvent != null)
                NodeChangedEvent();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::ShouldQuitCurrentMap()
        ///
        /// Fonction qui demande si on veut enregistrer
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public bool ShouldQuitCurrentMap()
        {
            if (isChanged)
            {
                var choice = System.Windows.MessageBox.Show("Voulez-vous enregistrer vos modifications?", "Modifications", MessageBoxButton.YesNoCancel);

                if (choice == MessageBoxResult.Cancel)
                {
                    return false;
                }

                if (choice == MessageBoxResult.Yes)
                {
                    Save();
                }
            }

            return true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void EditorController::NewMap()
        ///
        /// Fonction qui reset la map par défaut
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void NewMap()
        {
            if (ShouldQuitCurrentMap())
            {
                FonctionsNatives.resetMap();
                isChanged = false;
                loadedFile = null;
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerIn();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerOut();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void resizeGamePanel();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deleteObj();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void duplicate();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void save(string filePath);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void load(string filePath);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void preparerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initializeDuplication();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setSelectedNodeData(NodeData data);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void resetMap();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectAll();
        }
    }
}
