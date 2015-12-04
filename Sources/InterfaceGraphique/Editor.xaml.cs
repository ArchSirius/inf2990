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
using Newtonsoft.Json.Linq;


namespace InterfaceGraphique
{
    [StructLayout(LayoutKind.Sequential)]
    struct NodeData
    {
        public float pos_x, pos_y, scale_x, scale_y, angle;
        public String type;
    }

    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class Editor : Page, Renderable, Observer
    {
        private EditorController controller;
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;
        private bool simulationPaused = false;
        private List<Profil> profiles;
        private Settings settings;
        private bool vueMode = false; // false = ortho, true = orbite
        private Profil selectedProfile;
        private Profil SelectedProfile
        {
            get { return selectedProfile; }
            set
            {
                selectedProfile = value;
                settings.DefaultProfile = value;
                controller.ChangeProfile(value);
                (new ConfigPanelData()).SaveSettings(settings);
            }
        }

        private bool VueMode
        {
            get { return vueMode; }
            set
            {
                if (controller == null)
                    return;

                controller.ResizeGamePanel(GamePanel.Width, GamePanel.Height);
                controller.select();
                selecting.IsChecked = true;
                zooming.IsEnabled = value; // Zoom elastique
                zoomingMenu.IsEnabled = value;

                vueMode = value;
            }
        }

        private bool VueOrtho
        {
            get { return VueMode == true; }
            set
            {
                if (controller == null)
                    return;

                if (value)
                {
                    controller.SetOrthoView();
                }

                VueMode = value;
            }
        }

        private bool VueOrbite
        {
            get { return VueMode == false; }
            set
            {
                if (controller == null)
                    return;

                if (value)
                {
                    controller.SetOrbitView();
                }

                VueMode = !value;
            }
        }

        /// Les chaînes représentant les types de noeuds
        private const string NOM_ARAIGNEE = "araignee";
        private const string NOM_CONECUBE = "conecube";
        private const string NOM_ROBOT = "robot";
        private const string NOM_TABLE = "table";
        private const string NOM_LIGNE = "ligne";

        internal Editor(EditorController _controller)
        {
            InitializeComponent();
            controller = _controller;
  
            // Ne pas enlever Forms : c'est pour éviter l'ambiguïté.
            KeyDown += controller.KeyPressed;
            KeyUp += controller.KeyUnPressed;
            GamePanel.MouseDown += new Forms.MouseEventHandler(controller.MouseButtonDown);
            GamePanel.MouseUp += new Forms.MouseEventHandler(controller.MouseButtonUp);
            GamePanel.MouseEnter += new EventHandler(GamePanel_MouseEnter);
            GamePanel.MouseLeave -= new EventHandler(GamePanel_MouseExit);
            GamePanel.MouseWheel += new Forms.MouseEventHandler(controller.RouletteSouris);
            GamePanel.MouseMove += new Forms.MouseEventHandler(controller.MouseMove);
            /// Resize on resize only
            Application.Current.MainWindow.SizeChanged += new SizeChangedEventHandler(ResizeGamePanel);

            settings = (new ConfigPanelData()).LoadSettings();
            profiles = (new ConfigPanelData()).LoadProfiles();

            var defaultProfile = profiles.Where(x => settings != null && x.CompareTo(settings.DefaultProfile) == 0);

            if (defaultProfile.Count() > 0)
            {
                selectedProfile = defaultProfile.First();
                controller.ChangeProfile(selectedProfile);
            }
            else
            {
                selectedProfile = profiles[0];
                controller.ChangeProfile(selectedProfile);
            }
        }

        public void update(Observable obj)
        {
            var engine = (Engine)obj;
            var nbObject = engine.getNbNodesSelected();

            deleting.IsEnabled = (nbObject > 0);

            if (nbObject == 1)
            {
                IndvPropsForm.IsEnabled = true;
                var data = new NodeData();
                engine.getSelectedNodeData(out data);

                txtPosX.Text = data.pos_x.ToString();
                txtPosY.Text = data.pos_y.ToString();
                txtScaleX.Text = data.scale_x.ToString();
                txtScaleY.Text = data.scale_y.ToString();
                txtAngle.Text = data.angle.ToString();
            }
            else
            {
                IndvPropsForm.IsEnabled = false;
                txtPosX.Text = txtPosY.Text = txtScaleX.Text = txtScaleY.Text = txtAngle.Text = "";
            }
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
            controller.InitializeGamePanel(GamePanel.Handle, GamePanel.Width, GamePanel.Height);
        }


        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                controller.DetectDrag();

                Action action = delegate()
                {
                    FonctionsNatives.dessinerOpenGL();

                    if (!simulationPaused)
                    {
                        controller.DetectUserInput();
                        FonctionsNatives.animer((float)tempsInterAffichage);
                    }
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
            // Don't break the fixes
            for (int i = 0; i < 30; i++)
                controller.ResizeGamePanel(GamePanel.Width, GamePanel.Height);
        }

        private void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            if (controller.ShouldQuitCurrentMap() && LoadMainMenu != null)
                LoadMainMenu(this, e);
            FonctionsNatives.unloadFmod();
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
            VueOrtho = true;
            MenuVueOrthographique.IsChecked = true;
            MenuVueOrbite.IsChecked = false;

            if (TestVueOrthographique != null)
            {
                TestVueOrthographique.IsChecked = true;
                TestVueOrbite.IsChecked = false;
            } 
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            VueOrbite = true;
            MenuVueOrthographique.IsChecked = false;
            MenuVueOrbite.IsChecked = true;

            if (TestVueOrthographique != null)
            {
                TestVueOrthographique.IsChecked = false;
                TestVueOrbite.IsChecked = true;
            }
        }

        private void TestOrthographique_Checked(object sender, RoutedEventArgs e)
        {
            VueOrtho = true;
            TestVueOrthographique.IsChecked = true;
            TestVueOrbite.IsChecked = false;
            MenuVueOrthographique.IsChecked = true;
            MenuVueOrbite.IsChecked = false;
        }

        private void TestOrbite_Checked(object sender, RoutedEventArgs e)
        {
            VueOrbite = true;
            TestVueOrthographique.IsChecked = false;
            TestVueOrbite.IsChecked = true;
            MenuVueOrthographique.IsChecked = false;
            MenuVueOrbite.IsChecked = true;
        }

        private void Orthographique_Unchecked(object sender, RoutedEventArgs e)
        {
            if (VueOrtho)
                ((MenuItem)sender).IsChecked = true;
        }

        private void Orbite_Unchecked(object sender, RoutedEventArgs e)
        {
            if (VueOrbite)
                ((MenuItem)sender).IsChecked = true;
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
            var properties = new NodeData();

            try
            {
                properties.pos_y = float.Parse(txtPosY.Text);
                properties.scale_x = float.Parse(txtScaleX.Text);
                properties.scale_y = float.Parse(txtScaleY.Text);
                properties.angle = float.Parse(txtAngle.Text);
                properties.pos_x = float.Parse(txtPosX.Text);
            
                controller.InjectProperties(properties);
            }
            catch (FormatException exeption)
            {
                System.Windows.MessageBox.Show(exeption.Message, exeption.GetType().ToString(), MessageBoxButton.OK, MessageBoxImage.Error);

            }
        }

        private void EnableModeTest_Click(object sender, RoutedEventArgs e)
        {
            controller.SetModeTestEnabled(true);
            MainGrid.ColumnDefinitions[1].Width = new System.Windows.GridLength(0.0);
            MainGrid.RowDefinitions[0].Height = new System.Windows.GridLength(0.0);

        }

        private void DisableModeTest_Click(object sender, RoutedEventArgs e)
        {
            controller.SetModeTestEnabled(false);
            MainGrid.RowDefinitions[1].Height = new System.Windows.GridLength(0.0);
            MainGrid.RowDefinitions[0].Height = System.Windows.GridLength.Auto;
            MainGrid.ColumnDefinitions[1].Width = new System.Windows.GridLength(150.0);
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
        }

        private void Page_KeyDown(object sender, KeyEventArgs e)
        {
            if (!controller.isModeTestEnabled())
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
                if (e.Key == Key.Z && !MenuVueOrbite.IsChecked)
                {
                    Zoom_Click(sender, e);
                }
            }

            if (e.Key == Key.Back)
            {
                if (controller.IsModeTestEnabled())
                {
                    FonctionsNatives.unloadFmod();
                    controller.RestartSimulation();
                }

                e.Handled = true;
            }
            if (e.Key == Key.T)
            {
                if (controller.IsModeTestEnabled())
                {
                    DisableModeTest_Click(sender, e);
                    simulationPaused = false;
                    /// On remet le mode selection (defaut)
                    controller.select();
                    selecting.IsChecked = true;
                }
                else
                {
                    EnableModeTest_Click(sender, e);
                }
            }
            if (e.Key == Key.Escape && controller.IsModeTestEnabled())
            {
                if (simulationPaused)
                {
                    simulationPaused = false;
                    MainGrid.RowDefinitions[1].Height = new System.Windows.GridLength(0.0);
                }
                else
                {
                    simulationPaused = true;
                    MainGrid.RowDefinitions[1].Height = System.Windows.GridLength.Auto;
                }
            } 

        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(float temps);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void unloadFmod(); 
        }

        private void ProfilesMenu_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (var profile in profiles.Skip(1))
            {
                var item = new MenuItem();
                item.Header = profile.Name;
                item.IsCheckable = true;
                item.Click += MenuItemProfile_Click;

                if (profile == SelectedProfile)
                {
                    item.IsChecked = true;
                    ((MenuItem)ProfilesMenu.Items[0]).IsChecked = false;
                }

                ((MenuItem)sender).Items.Add(item);
            }
        }

        private void MenuItemProfile_Click(object sender, RoutedEventArgs e)
        {
            var i = 0;
            foreach (MenuItem item in ProfilesMenu.Items)
            {
                if (item != sender)
                {
                    item.IsChecked = false;
                }
                else
                {
                    SelectedProfile = profiles[i];
                }
                i++;
            }
        }
    }
}
