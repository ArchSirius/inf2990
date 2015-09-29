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
            controller = new EditorController();
  
            // Ne pas enlever Forms : c'est pour éviter l'ambiguïté.
            KeyDown += controller.KeyPressed;
            GamePanel.MouseDown += new Forms.MouseEventHandler(controller.MouseButtonDown);
            GamePanel.MouseUp += new Forms.MouseEventHandler(controller.MouseButtonUp);
            GamePanel.MouseEnter += new EventHandler(GamePanel_MouseEnter);
            GamePanel.MouseLeave -= new EventHandler(GamePanel_MouseExit);
            GamePanel.MouseWheel += new Forms.MouseEventHandler(controller.RouletteSouris);
            GamePanel.Resize += new EventHandler(controller.resizeGamePanel);

        }

        private void GamePanel_MouseEnter(object sender, EventArgs e)
        {
            if (!GamePanel.Focused)
                GamePanel.Focus();
        }

        private void GamePanel_MouseExit(object sender, EventArgs e)
        {
            if (GamePanel.Focused)
                GamePanel.Parent.Focus();
        }
        

        private void Test_Loaded(object sender, EventArgs e)
        {
            InitializeGamePanel();
        }


        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
                Action action = delegate()
                {
                    FonctionsNatives.dessinerOpenGL();
                };

                Dispatcher.Invoke(DispatcherPriority.Normal, action);
            }
            catch (Exception e)
            {
                Debug.Write("FrameUpdate error: " + e.GetBaseException().Message);
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

        private void translate(object sender, RoutedEventArgs e)
        {
            Debug.Write("Translation");
             controller.translate();
        }

        private void select(object sender, RoutedEventArgs e)
        {
            Debug.Write("Sélection");
            controller.select();
        }

        private void rotate(object sender, RoutedEventArgs e)
        {
            Debug.Write("Rotation");
            controller.rotate();
        }

        private void scale(object sender, RoutedEventArgs e)
        {
            Debug.Write("Mise à l'échelle");
            controller.scale();
        }

        private void duplicate(object sender, RoutedEventArgs e)
        {
            Debug.Write("Duplication");
            controller.duplicate();
        }

        private void deleteObj(object sender, RoutedEventArgs e)
        {
            Debug.Write("Suppression");
            controller.deleteObj();
        }

        private void SaveAs_Click(object sender, RoutedEventArgs e)
        {
            Debug.Write("Save as");
            controller.SaveAs();
        }

        private void OpenFile_Click(object sender, RoutedEventArgs e)
        {
            Debug.Write("Save as");
            controller.OpenFile();
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
    }
}
