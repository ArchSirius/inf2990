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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, Renderable
    {
        Renderable actualPage;

        public MainWindow()
        {
            InitializeComponent();

            // Le menu principal (escalope de veau, canard laqué aux arachide, jarret d'agneau aux canneberges)
            actualPage = new MainMenu();
            ((MainMenu)actualPage).LoadEditor += LoadEditor;
            ((MainMenu)actualPage).CloseApplication += CloseApplication;
            content.Navigate(actualPage);
        }

        public void FrameUpdate(double time)
        {
            actualPage.FrameUpdate(time);
        }

        private void LoadEditor(object sender, EventArgs e)
        {
            actualPage = new Editor();
            content.Navigate(actualPage);
        }

        private void CloseApplication(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
