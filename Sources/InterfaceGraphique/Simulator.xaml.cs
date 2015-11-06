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

namespace InterfaceGraphique
{
    /// <summary>
    /// Logique d'interaction pour Simulator.xaml
    /// </summary>
     
    public partial class Simulator : Page, Renderable, Observer
    {
        private Engine engine;
        private bool modeSimulation = true;
        private SimulatorController controller;
        private bool isChanged = false;

        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;
        private bool simulationPaused = false;

        internal Simulator(SimulatorController _simulator)
        {
            InitializeComponent();
            controller = _simulator;
         
        }

        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                Action action = delegate()
                {
                    FonctionsNatives.dessinerOpenGL();
                    if (modeSimulation)
                    {
                        MainGrid.RowDefinitions[0].Height = new System.Windows.GridLength(0.0);

                    }
                     
                    if (!simulationPaused)
                    {
                        modeSimulation = false; 
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

        public void update(Observable obj)
        {

        }

        private void Test_Loaded(object sender, RoutedEventArgs e)
        {
            controller.InitializeGamePanel(GamePanel.Handle, GamePanel.Width, GamePanel.Height);
        }

        private void Orthographique_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrbite.IsChecked = false;
        }

        private void Orbite_Checked(object sender, RoutedEventArgs e)
        {
            MenuVueOrthographique.IsChecked = false;
        }


        public void RestartSimulation()
        {
            FonctionsNatives.stopSimulation();
            FonctionsNatives.startSimulation();
            
        }

        public bool IsSimulationEnabled()
        {
            return modeSimulation;
        }

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
                   ///// Save();
                }
            }

            return true;
        }

        private void BtnLoadMainMenu_Click(object sender, RoutedEventArgs e)
        {
            if (ShouldQuitCurrentMap() && LoadMainMenu != null)
                LoadMainMenu(this, e);
        }

        private void Page_KeyDown(object sender, KeyEventArgs e)
        {
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

            
        }
    }
}
