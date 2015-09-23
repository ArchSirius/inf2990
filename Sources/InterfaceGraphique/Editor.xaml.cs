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
using System.Threading;
using Forms = System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class Editor : Page, Renderable
    {
        private EditorController controller;
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;


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
            controller = new EditorController(this);
  
            // Ne pas enlever Forms : c'est pour éviter l'ambiguïté.

            KeyDown += controller.KeyPressed;
            GamePanel.MouseDown += new Forms.MouseEventHandler(controller.MouseButtonDown);
            GamePanel.MouseUp += new Forms.MouseEventHandler(controller.MouseButtonUp);
            GamePanel.MouseWheel += new Forms.MouseEventHandler(controller.RouletteSouris);
            GamePanel.Resize += new EventHandler(controller.resizeGamePanel);

        }

        private void Test_Loaded(object sender, EventArgs e)
        {
            InitializeGamePanel();
        }


        public void FrameUpdate(double tempsInterAffichage)
        {
            /*
            if (resize_)
            {
                resize_ = false;
                FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            }*/

            try
            {
                //FonctionsNatives.resizeGamePanel();
                FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
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
            
            //resize_ = true;
            IntPtr source = GamePanel.Handle;
            FonctionsNatives.initialiserOpenGL(source);
            FonctionsNatives.dessinerOpenGL();
        }

        private void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            if (LoadMainMenu != null)
                LoadMainMenu(this, e);
        }

        private void Orthographique_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrbite.IsChecked = false;
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrthographique.IsChecked = false;
        }

        public void ZoomIn_Click(object sender, RoutedEventArgs e)
        {
            controller.ZoomIn();
        }

        private void ZoomOut_Click(object sender, RoutedEventArgs e)
        {
            controller.ZoomOut();
        }

        private void MenuAddPoteau_Click(object sender, RoutedEventArgs e)
        {
            controller.addingNode = true;
            controller.nodeType = NOM_CYLINDRE;
        }

        private void MenuAddLigne_Click(object sender, RoutedEventArgs e)
        {

        }

        private void MenuAddMur_Click(object sender, RoutedEventArgs e)
        {
            controller.addingNode = true;
            controller.nodeType = NOM_MUR;
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
            public static extern void redimensionnerFenetre(int largeur, int hauteur);
        }

        private void translate(object sender, RoutedEventArgs e)
        {
             controller.translate();
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
