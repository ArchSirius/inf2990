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
using System.Windows.Threading;
using System.Windows.Interop;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class wpftest : Window
    {
        public wpftest()
        {
            InitializeComponent();
            //InitialiserAnimation();
        }

        /*public void InitialiserAnimation()
        {
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }*/

        public void FrameUpdate(double tempsInterAffichage)
        {
            try
            {
                Action action = delegate()
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                };

                Dispatcher.Invoke(DispatcherPriority.Normal, action);
            }
            catch (Exception)
            {
            }

        }

        private void GamePanel_Loaded(object sender, EventArgs e)
        {
            HwndSource source = (HwndSource)HwndSource.FromVisual((Canvas)sender);
            FonctionsNatives.initialiserOpenGL(source.Handle);
            FonctionsNatives.dessinerOpenGL();
        }
    }
}
