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
    [StructLayout(LayoutKind.Sequential)]
    struct NodeData
    {
        public float pos_x, pos_y, scale_x, scale_y, angle;
    }

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
        private const string NOM_LIGNE = "ligne";

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
            GamePanel.MouseMove += new Forms.MouseEventHandler(controller.MouseMove);
            /// Resize on resize only
            Application.Current.MainWindow.SizeChanged += new SizeChangedEventHandler(ResizeGamePanel);

            controller.SelectedEvent += OnObjectSelected;
            controller.NodeChangedEvent += OnNodeChanged;
        }

        private void UpdatePropertyForm()
        {
            if (IndvPropsForm.IsEnabled)
            {
                var data = new NodeData();
                FonctionsNatives.getSelectedNodeData(out data);

                txtPosX.Text = data.pos_x.ToString();
                txtPosY.Text = data.pos_y.ToString();
                txtScaleX.Text = data.scale_x.ToString();
                txtScaleY.Text = data.scale_y.ToString();
                txtAngle.Text = data.angle.ToString();
            }
        }

        private void OnObjectSelected(int nbObject)
        {
            if (nbObject > 0)
            {
                deleting.IsEnabled = true;
            }
            else
            {
                deleting.IsEnabled = false;
            }

            if (nbObject == 1)
            {
                IndvPropsForm.IsEnabled = true;
                UpdatePropertyForm();
            }
            else
            {
                IndvPropsForm.IsEnabled = false;
                txtPosX.Text = "";
                txtPosY.Text = "";
                txtScaleX.Text = "";
                txtScaleY.Text = "";
                txtAngle.Text = "";
            }
        }

        private void OnNodeChanged()
        {
            UpdatePropertyForm();
        }

        private void GamePanel_MouseEnter(object sender, EventArgs e)
        {
            if (!GamePanel.Focused && Window.GetWindow(this).IsActive)
                GamePanel.Focus();
        }

        private void GamePanel_MouseExit(object sender, EventArgs e)
        {
            if (GamePanel.Focused && Window.GetWindow(this).IsActive)
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
                controller.DetectDrag();
                //Need to  be removed for new elastic rectangle
                //FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
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

        private void ResizeGamePanel(object sender, SizeChangedEventArgs e)
        {
            /// Si on met ça ici, et dans InitializeGamePanel, on peut retirer celui
            /// de FrameUpdate. PAR CONTRE, le premier resize est étrange.
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
        }

        private void InitializeGamePanel()
        {
            IntPtr source = GamePanel.Handle;            
            FonctionsNatives.initialiserOpenGL(source);
            FonctionsNatives.dessinerOpenGL();

            /// Pour une raison inconnue, si on fait la fonction moins de 4 fois, la
            /// fenêtre n'aura pas fait un redimensionnement suffisant. CEPENDANT, le
            /// redimensionnement OnResize est correct, puisqu'il s'appelle 60 fois/s.
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
            FonctionsNatives.redimensionnerFenetre(GamePanel.Width, GamePanel.Height);
        }

        private void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            if (controller.ShouldQuitCurrentMap() && LoadMainMenu != null)
                LoadMainMenu(this, e);
        }

        private void Zoom_Click(object sender, RoutedEventArgs e)
        {
            controller.zoomRectangle();
            zooming.IsChecked = true;
        }

        private void Aide_Click(object sender, RoutedEventArgs e)
        {
            var window = new HelpWindow();
            window.Show();
        }

        private void MenuAbout_Click(object sender, RoutedEventArgs e)
        {
            var window = new AboutWindow();
            window.Show();
        }

        private void Orthographique_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrbite.IsChecked = false;
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrthographique.IsChecked = false;
        }

        public void Zoom_Rectangle(object sender, RoutedEventArgs e)
        {
            controller.zoomRectangle();
        }
        private void MenuAddPoteau_Click(object sender, RoutedEventArgs e)
        {
            controller.create(Tools.CreatePoteau.nodeType);
            addingPoteau.IsChecked = true;
        }

        private void MenuAddLigne_Click(object sender, RoutedEventArgs e)
        {
            controller.create(Tools.CreateLigne.nodeType);
            addingLigne.IsChecked = true;
        }


        private void MenuAddMur_Click(object sender, RoutedEventArgs e)
        {
            controller.create(Tools.CreateMur.nodeType);
            addingMur.IsChecked = true;
        }

        private void translate(object sender, RoutedEventArgs e)
        {
            translating.IsChecked = true;
            controller.translate();
        }

        private void select(object sender, RoutedEventArgs e)
        {
            selecting.IsChecked = true;
            controller.select();
        }

        private void rotate(object sender, RoutedEventArgs e)
        {
            rotating.IsChecked = true;
            controller.rotate();
        }

        private void scale(object sender, RoutedEventArgs e)
        {
            scaling.IsChecked = true;
            controller.scale();
        }

        private void duplicate(object sender, RoutedEventArgs e)
        {
            duplicating.IsChecked = true;
            controller.duplicate();
        }

        private void deleteObj(object sender, RoutedEventArgs e)
        {
            deleting.IsEnabled = false;
            controller.deleteObj();
        }

        private void SaveAs_Click(object sender, RoutedEventArgs e)
        {
            controller.SaveAs();
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            controller.Save();
        }

        private void OpenFile_Click(object sender, RoutedEventArgs e)
        {
            controller.OpenFile();
        }

        private void NodeProperties_Changed(object sender, RoutedEventArgs e)
        {
            Debug.Write("Inject Node Properties");
            var properties = new NodeData();

            try
            {
                properties.pos_y = float.Parse(txtPosY.Text);
                properties.scale_x = float.Parse(txtScaleX.Text);
                properties.scale_y = float.Parse(txtScaleY.Text);
                properties.angle = float.Parse(txtAngle.Text);
                properties.pos_x = float.Parse(txtPosX.Text);
            
                controller.InjectProperties(properties);
                UpdatePropertyForm();
            }
            catch (FormatException exeption)
            {
                System.Windows.MessageBox.Show(exeption.Message, exeption.GetType().ToString(), MessageBoxButton.OK, MessageBoxImage.Error);

            }
        }

        private void NodeProperties_Keydown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                NodeProperties_Changed(sender, e);
            }
        }

        private void Nouveau_Click(object sender, RoutedEventArgs e)
        {
            controller.NewMap();
            OnObjectSelected(0);
        }

        private void Page_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.D)
            {
                translate(sender, e);
            }
            if (e.Key == Key.S)
            {
                select(sender, e);
            }
            if (e.Key == Key.R)
            {
                rotate(sender, e);
            }
            if (e.Key == Key.E)
            {
                scale(sender, e);
            }
            if (e.Key == Key.C)
            {
                duplicate(sender, e);
            }
            if (e.Key == Key.Z)
            {
                Zoom_Click(sender, e);
            }
        }
    }
}
