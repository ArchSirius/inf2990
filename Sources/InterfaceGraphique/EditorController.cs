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
        private bool mouseClicked = false;
        private Tools.ToolContext toolContext;
        private bool dragEnter = false;
        private bool clicIsLeft;

        int xPos = Forms.Control.MousePosition.X;
        int yPos = Forms.Control.MousePosition.Y;

        public void resizeGamePanel(object sender, EventArgs e)
        {
           // FonctionsNatives.resizeGamePanel();
            toolContext = new Tools.ToolContext();
        }

        public void KeyPressed(object o, KeyEventArgs e)
        {

            if (e.Key == Key.Left)
            {
                Debug.Write("Deplacement camera gauche");

                FonctionsNatives.deplacerXY(-0.10, 0);

            }
            else if (e.Key == Key.Right)
            {
                Debug.Write("Deplacement camera droite");
                FonctionsNatives.deplacerXY(0.10, 0);

            }
            else if (e.Key == Key.Up)
            {
                Debug.Write("Deplacement camera haut");

                FonctionsNatives.deplacerXY(0, 0.1);

            }
            else if (e.Key == Key.Down)
            {
                Debug.Write("Deplacement camera bas");

                FonctionsNatives.deplacerXY(0, -0.10);

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
            else if (e.Key == Key.Delete)
            {
                FonctionsNatives.deleteObj();
            }
        }

        public void MouseButtonDown(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                clicIsLeft = true;

                toolContext.LeftMouseClicked(e);

                Debug.Write("Touche gauche enfoncée en [{0}, {1}]", Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);

                mouseClicked = true;
                DetectDrag();


            }
            else if (e.Button == Forms.MouseButtons.Right)
            {
                clicIsLeft = false;
                Debug.Write("Touche droite enfoncée en [{0}, {1}]", Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);

                toolContext.RightMouseClicked(e);

                mouseClicked = true;
                DetectDrag();
            }
        }

        public void MouseButtonUp(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left || e.Button == Forms.MouseButtons.Right)
            {
                if (e.Button == Forms.MouseButtons.Left)
                    toolContext.LeftMouseReleased(e);

                mouseClicked = false;
                dragEnter = false;
                Debug.Write("Touche relachée en [{0}, {1}]" + Environment.NewLine, Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
            }
        }

        public void MouseMove(Object o, Forms.MouseEventArgs e)
        {
            toolContext.MouseMove(e);
        }

        public void RouletteSouris(Object o, Forms.MouseEventArgs e)
        {
            System.Console.WriteLine("RouletteSouris");
            if (e.Delta > 0)
            {
                System.Console.WriteLine("zoomerIn (e.Delta > 0)");
                FonctionsNatives.zoomerIn();
            }
            else if (e.Delta < 0)
            {
                System.Console.WriteLine("zoomerOut(e.Delta < 0)");
                FonctionsNatives.zoomerOut();
            }

        }

        public void DetectDrag()
        {
            if (mouseClicked)
            {
                if (MouseMoved(xPos, yPos, 4) || dragEnter)
                {
                    dragEnter = true;
                    if (mouseClicked)
                    {
                        int origX = Forms.Control.MousePosition.X;
                        int origY = Forms.Control.MousePosition.Y;

                        if (MouseMoved(xPos, yPos, 1))
                        {
                            Debug.Write("[{0}, {1}]; Bougé de {2}, {3}",
                                Forms.Control.MousePosition.X,
                                Forms.Control.MousePosition.Y,
                                Forms.Control.MousePosition.X - xPos,
                                Forms.Control.MousePosition.Y - yPos
                            );
                            toolContext.Dragging(Forms.Control.MousePosition.X - origX, origY - Forms.Control.MousePosition.Y, 0, clicIsLeft);
                            xPos = Forms.Control.MousePosition.X;
                            yPos = Forms.Control.MousePosition.Y;
                        }
                    }
                    else
                    {
                        Debug.Write("Drag & Drop terminé.");
                    }
                }
            }

        }

        private bool MouseMoved(int x, int y, int delta)
        {
            return (Math.Abs(x - Forms.Control.MousePosition.X) >= delta || Math.Abs(y - Forms.Control.MousePosition.Y) >= delta);
        }

        public void ZoomIn()
        {
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
        }

        public void ZoomOut()
        {
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
        }

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
        }

        public void translate()
        {
            toolContext.ChangeState(new Tools.Move(toolContext));
        }

        public void select()
        {
            toolContext.ChangeState(new Tools.Selection(toolContext));
        }

        public void rotate()
        {
            toolContext.ChangeState(new Tools.Rotation(toolContext));
        }

        public void scale()
        {
            toolContext.ChangeState(new Tools.Scale(toolContext));
        }

        public void duplicate()
        {
            toolContext.ChangeState(new Tools.Duplicate(toolContext));
        }

        public void deleteObj()
        {
            FonctionsNatives.deleteObj();
        }

        public void SaveAs()
        {
            var dialog = new SaveFileDialog();

            if (dialog.ShowDialog() == true)
            {
                if (dialog.FileName.Contains("Default.scene"))
                {
                    System.Windows.MessageBox.Show("Il n’est pas possible de modifier la zone de simulation par défaut.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else
                {
                    FonctionsNatives.save(dialog.FileName);
                }
            }
        }

        public void OpenFile()
        {
            var dialog = new OpenFileDialog();

            if (dialog.ShowDialog() == true)
            {
                FonctionsNatives.load(dialog.FileName);
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
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();
        }
    }
}
