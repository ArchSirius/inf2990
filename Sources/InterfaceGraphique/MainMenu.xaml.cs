using System;
using System.Collections.Generic;
using System.ComponentModel;
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
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page, Renderable
    {
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadEditor;

        public MainMenu()
        {
            InitializeComponent();
        }

        public void FrameUpdate(double time)
        {
            // There will be stuff here.
        }

        private void BtnLoadEditor_Click(object sender, RoutedEventArgs e)
        {
            if (LoadEditor != null)
                LoadEditor(this, e);
        }

        private void BtnCloseApplication_Click(object sender, RoutedEventArgs e)
        {
        //    if (CloseApplication != null)
        //        CloseApplication(this, e);
        }
    }
}
