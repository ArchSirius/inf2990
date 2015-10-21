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

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for UserControl2.xaml
    /// </summary>
    /// Tiré de http://wpftutorial.net/Home.html
    public partial class DebugSelect : Window
    {
        public DebugSelect()
        {
            InitializeComponent();
        }

        private void save(object sender, RoutedEventArgs e)
        {
            if (capteur_gauche_safe_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (capteur_gauche_danger_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (capteur_centre_safe_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (capteur_centre_danger_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (capteur_droit_safe_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (capteur_droit_danger_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (balayage_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (lum_ambiante_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (lum_directionnelle_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (lum_spot_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");

            if (bandes_capteurs_true.IsChecked == true)
                Debug.Write("test");
            else
                Debug.Write("test");
        }
    }
}
