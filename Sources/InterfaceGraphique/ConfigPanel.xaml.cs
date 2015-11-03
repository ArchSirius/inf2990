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
        private ConfigPanelData configDataRepository;
        private List<Profil> profils;

        public ConfigPanel()
        {
            InitializeComponent();
            configDataRepository = new ConfigPanelData();
            profils = configDataRepository.Load();

            DataContext = profils[0];
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

        private void TitleTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Foreground == Brushes.Gray)
            {
                ((TextBox)sender).Text = "";
                ((TextBox)sender).Foreground = Brushes.Black;
            }
        }

        private void Angle_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key < Key.D0 || e.Key > Key.D9 || ((TextBox)sender).Text.Length > 3)
            {
                e.Handled = true;
                return;
            }
        }

        private void Angle_KeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                if (((TextBox)sender).Text != "")
                {
                    var angle = Int32.Parse(((TextBox)sender).Text);

                    if (angle < 0 || angle > 360)
                    {
                        ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
                        ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;

                    }
                }
            }
            catch (FormatException ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                e.Handled = true;
            }
        }

        private void Time_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key < Key.D0 || e.Key > Key.D9 || ((TextBox)sender).Text.Length > 4)
            {
                e.Handled = true;
                return;
            }
        }

        private void Time_KeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                if (((TextBox)sender).Text != "")
                {
                    var time = Int32.Parse(((TextBox)sender).Text);

                    if (time < 0 || time > 2000)
                    {
                        ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
                        ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;

                    }
                }
            }
            catch (FormatException ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                e.Handled = true;
            }
        }

        private void Distance_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key < Key.D0 || e.Key > Key.D9 || ((TextBox)sender).Text.Length > 2)
            {
                e.Handled = true;
                return;
            }
        }

        private void Distance_KeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                if (((TextBox)sender).Text != "")
                {
                    var distance = Int32.Parse(((TextBox)sender).Text);

                    if (distance < 0 || distance > 30)
                    {
                        ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
                        ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;

                    }

                    var i = VisualTreeHelper.GetChildrenCount(((TextBox)sender).Parent);
                    var sum = 0;

                    while (--i >= 0)
                    {
                        var child = VisualTreeHelper.GetChild(((TextBox)sender).Parent, i);

                        if (child is TextBox && ((TextBox)child).Text != "")
                        {
                            sum += Int32.Parse(((TextBox)child).Text);
                        }
                    }

                    if (sum > 30)
                    {
                        ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
                        ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;
                        throw new FormatException("La somme des distances ne peut pas exéder 30");
                    }
                }
            }
            catch (FormatException ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                e.Handled = true;
            }
        }
    }
}
