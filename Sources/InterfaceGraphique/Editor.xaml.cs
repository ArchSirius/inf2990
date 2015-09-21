using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Interop;
using Forms = System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class Editor : Page, Renderable
    {
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;
        private bool mouseClicked = false;
        private bool addingNode = false;
        private string nodeType;

        /// Les chaînes représentant les types de noeuds
        private const string NOM_ARAIGNEE = "araignee";
        private const string NOM_CONECUBE = "conecube";
        private const string NOM_ROBOT = "robot";
        private const string NOM_TABLE = "table";
        private const string NOM_CYLINDRE = "cylindre";
        private const string NOM_MUR = "mur";

        public Editor()
        {
            InitializeComponent();
  
            // Ne pas enlever Forms : c'est pour éviter l'ambiguïté.
            KeyDown += KeyPressed;
            GamePanel.MouseDown += new Forms.MouseEventHandler(MouseButtonDown);
            GamePanel.MouseUp += new Forms.MouseEventHandler(MouseButtonUp);
            GamePanel.MouseWheel += new Forms.MouseEventHandler(RouletteSouris);
            GamePanel.Resize += new EventHandler(resizeGamePanel);
        }

        private void Test_Loaded(object sender, EventArgs e)
        {
            InitializeGamePanel();
        }

        private void resizeGamePanel(object sender, EventArgs e)
        {
            FonctionsNatives.resizeGamePanel();
        }

        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                Action action = delegate()
                {
                    FonctionsNatives.dessinerOpenGL();
                    
                };

                Dispatcher.Invoke(DispatcherPriority.Normal, action);
            }
            catch (Exception)
            {
            }
        }

        private void InitializeGamePanel()
        {
            IntPtr source = GamePanel.Handle;
            FonctionsNatives.initialiserOpenGL(source);
            FonctionsNatives.dessinerOpenGL();
        }

        private void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            if (LoadMainMenu != null)
                LoadMainMenu(this, e);
        }

        private void KeyPressed(object o, KeyEventArgs e)
        {
       
            if (e.Key == Key.Left)
            {
                System.Console.WriteLine("Deplacement camera gauche");
                FonctionsNatives.deplacerXY(0.01, 0);
            }
            else if (e.Key == Key.Right)
            {
                System.Console.WriteLine("Deplacement camera droite");
                FonctionsNatives.deplacerXY(-0.01, 0);
            }
            else if (e.Key == Key.Up)
            {
                System.Console.WriteLine("Deplacement camera haut");
                FonctionsNatives.deplacerXY(0, -0.01);
            }
            else if (e.Key == Key.Down)
            {
                System.Console.WriteLine("Deplacement camera bas");
                FonctionsNatives.deplacerXY(0, 0.01);
            }
            else if (e.Key == Key.OemMinus)
            {
                System.Console.WriteLine("ZoomOut");
                FonctionsNatives.zoomerOut();
            }
            else if (e.Key == Key.OemPlus)
            {
                System.Console.WriteLine("ZoomIN");
                FonctionsNatives.zoomerIn();
            }
        }

        private void MouseButtonDown(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                int x = Forms.Control.MousePosition.X;
                int y = Forms.Control.MousePosition.Y;
/*
                if(  x > Forms.Control.MousePosition.X)
                {
                    FonctionsNatives.deplacerXY(0.1, 0);
                }
                if (x < Forms.Control.MousePosition.X)
                {
                    FonctionsNatives.deplacerXY(-0.1, 0);
                }
                if (x < Forms.Control.MousePosition.Y)
                {
                    FonctionsNatives.deplacerXY(0, 0.1);
                }
                if (x > Forms.Control.MousePosition.Y)
                {
                    FonctionsNatives.deplacerXY(0, -0.1);
                }
*/
                System.Console.WriteLine("Touche enfoncée en [{0}, {1}]", Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
                mouseClicked = true;
                Thread t = new Thread(DetectDrag);
                t.Start();

                // <f3.2.3_ajoutPoteaux>
                if (addingNode)
                {
                    FonctionsNatives.addNode(nodeType);
                    addingNode = false;
                }
                // </>
            }
        }

        private void MouseButtonUp(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                mouseClicked = false;
                System.Console.WriteLine("Touche relachée en [{0}, {1}]" + Environment.NewLine, Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
            }
        }

        private void RouletteSouris(Object o, Forms.MouseEventArgs e)
        { 
            if(e.Delta> 0){
                FonctionsNatives.zoomerIn();
            }

            else if (e.Delta < 0) {
                FonctionsNatives.zoomerOut();
            }
            
        }

        private void DetectDrag()
        {
            int x = Forms.Control.MousePosition.X;
            int y = Forms.Control.MousePosition.Y;

            while (mouseClicked)
            {
                if (MouseMoved(x, y, 5))
                {
                    System.Console.WriteLine("Drag & Drop en cours.");
                    while (mouseClicked)
                    {
                        if (MouseMoved(x, y, 1))
                        {
                            System.Console.WriteLine("[{0}, {1}]; Bougé de {2}, {3}",
                                Forms.Control.MousePosition.X,
                                Forms.Control.MousePosition.Y,
                                Forms.Control.MousePosition.X - x,
                                Forms.Control.MousePosition.Y - y
                            );
                            x = Forms.Control.MousePosition.X;
                            y = Forms.Control.MousePosition.Y;
                        }
                    }
                    System.Console.WriteLine("Drag & Drop terminé.");
                }
            }

        }

        private bool MouseMoved(int x, int y, int delta)
        {
            return (Math.Abs(x - Forms.Control.MousePosition.X) > delta || Math.Abs(y - Forms.Control.MousePosition.Y) > delta);
        }

        private void Orthographique_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrbite.IsChecked = false;
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrthographique.IsChecked = false;
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserOpenGL(IntPtr handle);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void libererOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(double temps);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
             public static extern void zoomerIn();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
             public static extern void zoomerOut();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void translate();

             // <f3.2.3_ajoutPoteaux>
             [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
             public static extern void addNode(string type);
             // </>

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void resizeGamePanel();
        }

        private void ZoomIn_Click(object sender, RoutedEventArgs e)
        {
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
            FonctionsNatives.zoomerIn();
        }

        private void ZoomOut_Click(object sender, RoutedEventArgs e)
        {
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
            FonctionsNatives.zoomerOut();
        }

        private void MenuAddPoteau_Click(object sender, RoutedEventArgs e)
        {
            addingNode = true;
            nodeType = NOM_CYLINDRE;
        }

        private void MenuAddLigne_Click(object sender, RoutedEventArgs e)
        {

        }

        private void MenuAddMur_Click(object sender, RoutedEventArgs e)
        {
            addingNode = true;
            nodeType = NOM_MUR;
        }

        private void translate(object sender, RoutedEventArgs e)
        {
            // test
            System.Console.WriteLine("Translation");
            FonctionsNatives.translate();
        }

        private void rotate(object sender, RoutedEventArgs e)
        {
            // test
            System.Console.WriteLine("Rotation");
        }

        private void scale(object sender, RoutedEventArgs e)
        {
            // test
            System.Console.WriteLine("Mise à l'échelle");
        }

        private void duplicate(object sender, RoutedEventArgs e)
        {
            // test
            System.Console.WriteLine("Duplication");
        }
    }
}
