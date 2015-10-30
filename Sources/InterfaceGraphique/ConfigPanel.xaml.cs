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

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for ConfigPanel.xaml
    /// </summary>
    public partial class ConfigPanel : Page, Renderable
    {
        public delegate void ClickEventHandler(object sender, EventArgs e);
        public event ClickEventHandler LoadMainMenu;
        private ConfigPanelController controller;

        public ConfigPanel()
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

        private void KeyBinding_KeyDown(object sender, KeyEventArgs e)
        {
            Keyboard.ClearFocus();

            var i = VisualTreeHelper.GetChildrenCount(KeyboardConfigGroup);

            while (--i >= 0)
            {
                var child = VisualTreeHelper.GetChild(KeyboardConfigGroup, i);

                if (child is TextBox && child != sender && ((TextBox)child).Text == e.Key.ToString())
                {
                    System.Windows.MessageBox.Show("Cette touche est déjà utilisé pour une autre action", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                    e.Handled = true;
                    return;
                }
            }

            if (e.Key != Key.Escape)
            {
                var text = e.Key.ToString();

                if (e.Key == Key.Space)
                {
                    text = "Space";
                }

                ((TextBox)sender).Text = text;
            }

            Keyboard.ClearFocus();
        }

        private void KeyboardDefault_Click(object sender, RoutedEventArgs e)
        {
            KeyAvancer.Text = "W";
            KeyReculer.Text = "S";
            KeyRotationH.Text = "A";
            KeyRotationAH.Text = "D";
            KeyManuel.Text = "Space";
        }
    }
}
