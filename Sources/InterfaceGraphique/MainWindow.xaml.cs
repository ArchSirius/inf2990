﻿using System;
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
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, Renderable
    {
        Renderable actualPage;

        public MainWindow()
        {
            InitializeComponent();

            // Le menu principal (escalope de veau, canard laqué aux arachide, jarret d'agneau aux canneberges)
            LoadMainMenu(this, new EventArgs());
        }

        public void FrameUpdate(double time)
        {
            actualPage.FrameUpdate(time);
        }

        private void LoadMainMenu(object sender, EventArgs e)
        {
            actualPage = new MainMenu();
            ((MainMenu)actualPage).LoadSimulator += LoadSimulator;
            ((MainMenu)actualPage).LoadConfigPanel += LoadConfigPanel;
            ((MainMenu)actualPage).LoadEditor += LoadEditor;
            ((MainMenu)actualPage).CloseApplication += CloseApplication;
            content.Navigate(actualPage);
        }

        private void LoadSimulator(object sender, EventArgs e)
        {
            var model = new Engine();
            var controller = new SimulatorController(model);
            actualPage = new Simulator(controller);
            model.subscribe((Observer)actualPage);
            ((Simulator)actualPage).LoadMainMenu += LoadMainMenu;
            content.Navigate(actualPage);
        }

        private void LoadConfigPanel(object sender, EventArgs e)
        {
            actualPage = new ConfigPanel();
            ((ConfigPanel)actualPage).LoadMainMenu += LoadMainMenu;
            content.Navigate(actualPage);
        }

        private void LoadEditor(object sender, EventArgs e)
        {
            var model = new Engine();
            var controller = new EditorController(model);
            actualPage = new Editor(controller);
            model.subscribe((Observer)actualPage);
            ((Editor)actualPage).LoadMainMenu += LoadMainMenu; 
            content.Navigate(actualPage);
        }

        private void CloseApplication(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"fmodL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserFMOD(IntPtr handle);
    }
}
