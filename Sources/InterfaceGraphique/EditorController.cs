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
using InterfaceGraphique;

namespace InterfaceGraphique
{
    class EditorController
    {
        private bool mouseClicked = false;
        public string nodeType;
        public bool addingNode = false;
        private Tools.ToolContext toolContext;
        private bool dragEnter = false;

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
                FonctionsNatives.deplacerXY(-0.01, 0);
            }
            else if (e.Key == Key.Right)
            {
                Debug.Write("Deplacement camera droite");
                FonctionsNatives.deplacerXY(0.01, 0);
            }
            else if (e.Key == Key.Up)
            {
                Debug.Write("Deplacement camera haut");
                FonctionsNatives.deplacerXY(0, 0.01);
            }
            else if (e.Key == Key.Down)
            {
                Debug.Write("Deplacement camera bas");
                FonctionsNatives.deplacerXY(0, -0.01);
            }
            else if (e.Key == Key.OemMinus)
            {
                Debug.Write("ZoomOut");
                FonctionsNatives.zoomerOut();
            }
            else if (e.Key == Key.OemPlus)
            {
                Debug.Write("ZoomIN");
                FonctionsNatives.zoomerIn();
            }
        }

        public void MouseButtonDown(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                // <f3.2.3_ajoutPoteaux>
                if (addingNode)
                {
                    FonctionsNatives.addNode(nodeType);
                    addingNode = false;
                }

                toolContext.LeftMouseClicked(e);

                Debug.Write("Touche enfoncée en [{0}, {1}]", Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);

                mouseClicked = true;
                Thread t = new Thread(DetectDrag);
                t.Start();


            }
        }

        public void MouseButtonUp(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                toolContext.LeftMouseReleased(e);
                mouseClicked = false;
                dragEnter = false;
                Debug.Write("Touche relachée en [{0}, {1}]" + Environment.NewLine, Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
            }
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
            int x = Forms.Control.MousePosition.X;
            int y = Forms.Control.MousePosition.Y;

            while (mouseClicked)
            {
                if (MouseMoved(x, y, 5) || dragEnter)
                {
                    Debug.Write("Drag & Drop en cours.");
                    dragEnter = true;
                    while (mouseClicked)
                    {
                        int origX = Forms.Control.MousePosition.X;
                        int origY = Forms.Control.MousePosition.Y;

                        if (MouseMoved(x, y, 1))
                        {
                            Debug.Write("[{0}, {1}]; Bougé de {2}, {3}",
                                Forms.Control.MousePosition.X,
                                Forms.Control.MousePosition.Y,
                                Forms.Control.MousePosition.X - x,
                                Forms.Control.MousePosition.Y - y
                            );
                            toolContext.Dragging(Forms.Control.MousePosition.X - origX, origY - Forms.Control.MousePosition.Y, 0);
                            x = Forms.Control.MousePosition.X;
                            y = Forms.Control.MousePosition.Y;
                        }
                    }
                    Debug.Write("Drag & Drop terminé.");
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

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerIn();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomerOut();

            // <f3.2.3_ajoutPoteaux>
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);
            // </>

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void resizeGamePanel();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deleteObj();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void duplicate();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();




        }
    }
}
