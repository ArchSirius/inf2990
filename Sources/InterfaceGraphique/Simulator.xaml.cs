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
        private SimulatorController controller;

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

                    if (!simulationPaused)
                    {
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

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(float temps);
        }
    }
}
