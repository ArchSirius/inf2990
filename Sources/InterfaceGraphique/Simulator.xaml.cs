using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
using Forms = System.Windows.Forms;


namespace InterfaceGraphique
{
    /// <summary>
    /// Logique d'interaction pour Simulator.xaml
    /// </summary>
    /// 
    
    public partial class Simulator : Page, Renderable, Observer
    {
        private bool modeManuel = false;
        private SimulatorController controller;
        
        public static bool dragEnter = false;

        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;
        private bool simulationPaused = false;
        private bool start = true;
        private Settings settings;

        private List<Profil> profiles;
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

        internal Simulator(SimulatorController _simulator)
        {
            InitializeComponent();
            controller = _simulator;
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



        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                controller.DetectDrag();

                Action action = delegate()
                {
                    
                    FonctionsNatives.dessinerOpenGL();
                    if (start)
                    {
                        MainGrid.RowDefinitions[0].Height = new System.Windows.GridLength(0.0);
                        start = false;
                    }

                    if (!simulationPaused)
                    {
                        FonctionsNatives.animer((float)tempsInterAffichage);
                    }
                    if (modeManuel && !simulationPaused)
                    {
                        controller.DetectUserInput();
                        
                    }
                        
                     
             };

                Dispatcher.Invoke(DispatcherPriority.Normal, action);
            }
            catch (Exception e)
            {
                Debug.Write("FrameUpdate error: " + e.GetBaseException().Message);
            }
        
        }

        public void update(Observable obj)
        {


        }

        private void ResizeGamePanel(object sender, SizeChangedEventArgs e)
        {
            controller.ResizeGamePanel(GamePanel.Width, GamePanel.Height);
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

        private void Test_Loaded(object sender, RoutedEventArgs e)
        {
            controller.InitializeGamePanel(GamePanel.Handle, GamePanel.Width, GamePanel.Height);
        }

        private void Orthographique_Checked(object sender, RoutedEventArgs e)
        {
            if (MenuVueOrbite.IsChecked)
            {
                controller.SetOrthoView();
                controller.ResizeGamePanel(GamePanel.Width, GamePanel.Height);
                MenuVueOrbite.IsChecked = false;
            }
        }

        private void Orthographique_Unchecked(object sender, RoutedEventArgs e)
        {
            if (!MenuVueOrbite.IsChecked)
                MenuVueOrthographique.IsChecked = true;
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            if (MenuVueOrthographique.IsChecked)
            {
                controller.SetOrbitView();
                controller.ResizeGamePanel(GamePanel.Width, GamePanel.Height);
                MenuVueOrthographique.IsChecked = false;
            }
        }

        private void Orbite_Unchecked(object sender, RoutedEventArgs e)
        {
            if (!MenuVueOrthographique.IsChecked)
                MenuVueOrbite.IsChecked = true;
        }


        public void RestartSimulation()
        {
            FonctionsNatives.stopSimulation();
            FonctionsNatives.startSimulation();
        }

        public void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            LoadMainMenu(this, e);
            FonctionsNatives.unloadFmod();
            
        }
       
        private void Page_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Space)
            {
                if (modeManuel)
                {
                    modeManuel = false;
                  
                }
                else
                {
                    modeManuel = true;
                  
                }
            }

            if (e.Key == Key.Back)
            {
               RestartSimulation();
               e.Handled = true;
            }

            if (e.Key == Key.Escape)
            {
                if (simulationPaused)
                {
                    simulationPaused = false;
                    MainGrid.RowDefinitions[0].Height = new System.Windows.GridLength(0.0);
                    
                }
                else
                {
                    simulationPaused = true;
                    MainGrid.RowDefinitions[0].Height = System.Windows.GridLength.Auto;
                }
            }
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


        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(float temps);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void stopSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void startSimulation();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void unloadFmod(); 
        }
    }
}
