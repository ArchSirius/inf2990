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
using System.Windows.Threading;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page, Renderable
    {
        // Inspiré de https://msdn.microsoft.com/en-us/library/edzehd2t(v=vs.110).aspx
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadEditor;
        public event ClickEventHandler CloseApplication;

        public MainMenu()
        {
            InitializeComponent();
        }

        public void FrameUpdate(double time)
        {
            try
            {
                Action action = delegate()
                {
                    System.Threading.Thread.Sleep(1);
                };

                Dispatcher.Invoke(DispatcherPriority.Normal, action);
            }
            catch (Exception e)
            {
                Debug.Write("FrameUpdate error: " + e.GetBaseException().Message);
            }
        }

        private void BtnLoadEditor_Click(object sender, RoutedEventArgs e)
        {
            if (LoadEditor != null)
                LoadEditor(this, e);
        }

        private void BtnCloseApplication_Click(object sender, RoutedEventArgs e)
        {
            if (CloseApplication != null)
                CloseApplication(this, e);
        }

        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            //video.Stop();
        }
    }
}
