using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
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
        public Profil SelectedItem;
        public bool isProfileFormEnabled = true;
        public KeyBindings keybindings;
        public Settings settings;

        public ConfigPanel()
        {
            InitializeComponent();
            configDataRepository = new ConfigPanelData();
            settings = configDataRepository.LoadSettings();
            keybindings = configDataRepository.LoadKeybindings();
            profils = configDataRepository.LoadProfiles();
            profileListView.ItemsSource = profils;

            settings.PropertyChanged += SaveSettings;
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            configDataRepository.SaveProfiles(profils);
        }

        private void SaveSettings(object obj, PropertyChangedEventArgs e)
        {
            configDataRepository.SaveSettings((Settings)obj);
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
            if (e.Key == Key.Escape)
            {
                e.Handled = true;
                return;
            }

            try
            {
                var letter = ((char)KeyInterop.VirtualKeyFromKey(e.Key)).ToString();
                var validate = (Key)(new KeyConverter()).ConvertFromString(letter);
            }
            catch
            {
                e.Handled = true;
                return;
            }

            ((TextBox)sender).Text = "";

            foreach (PropertyInfo prop in keybindings.GetType().GetProperties())
            {
                if (prop.Name != ((TextBox)sender).GetBindingExpression(TextBox.TextProperty).ResolvedSourcePropertyName && prop.GetValue(keybindings) == e.Key.ToString())
                {
                    System.Windows.MessageBox.Show("Cette touche est déjà utilisé pour une autre action", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                    e.Handled = true;
                    return;
                }
            }
        }

        private void KeyBinding_KeyUp(object sender, KeyEventArgs e)
        {
            ((TextBox)sender).GetBindingExpression(TextBox.TextProperty).UpdateSource();
            Keyboard.ClearFocus();

            configDataRepository.SaveKeybindings(keybindings);
        }

        private void KeyboardDefault_Click(object sender, RoutedEventArgs e)
        {
            DataContext = new KeyBindings();
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
            if (e.Key < Key.D0 || e.Key > Key.D9 || ((TextBox)sender).Text.Length > 2)
            {
                e.Handled = true;
                return;
            }
        }

        private void Time_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key < Key.D0 || e.Key > Key.D9 || ((TextBox)sender).Text.Length > 3)
            {
                e.Handled = true;
                return;
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

        private void Angle_KeyUp(object sender, KeyEventArgs e)
        {
            //try
            //{
            //    if (((TextBox)sender).Text != "")
            //    {
            //        var angle = Int32.Parse(((TextBox)sender).Text);
            //
            //        if (angle < 0 || angle > 360)
            //        {
            //            ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
            //            ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;
            //
            //        }
            //    }
            //}
            //catch (FormatException ex)
            //{
            //    System.Windows.MessageBox.Show(ex.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            //    e.Handled = true;
            //}
        }

        private void Time_KeyUp(object sender, KeyEventArgs e)
        {
            //try
            //{
            //    if (((TextBox)sender).Text != "")
            //    {
            //        var time = Int32.Parse(((TextBox)sender).Text);
            //
            //        if (time < 0 || time > 2000)
            //        {
            //            ((TextBox)sender).Text = ((TextBox)sender).Text.Substring(0, ((TextBox)sender).Text.Length - 1);
            //            ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;
            //
            //        }
            //    }
            //}
            //catch (FormatException ex)
            //{
            //    System.Windows.MessageBox.Show(ex.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            //    e.Handled = true;
            //}
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

        public void ProfilePropertyChanges(object o, EventArgs e)
        {
            if (((Profil)o).Error != "")
            {
                saveBtn.IsEnabled = false;
                deleteBtn.IsEnabled = false;
                addProfilBtn.IsEnabled = false;
            }
            else if (profils[0].CompareTo(o) != 0)
            {
                saveBtn.IsEnabled = true;
                deleteBtn.IsEnabled = true;
                addProfilBtn.IsEnabled = true;
            }
        }

        private void profileListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (((ListView)sender).SelectedItems.Count > 0)
            {
                SelectedItem = (Profil)((ListView)sender).SelectedItems[0];
                DataContext = SelectedItem;
                SelectedItem.PropertyChanged += ProfilePropertyChanges;
                profileForm.Visibility = Visibility.Visible;

                if (SelectedItem == profils[0])
                {
                    saveBtn.IsEnabled = false;
                    deleteBtn.IsEnabled = false;
                }
                else
                {
                    saveBtn.IsEnabled = true;
                    deleteBtn.IsEnabled = true;
                }
            }
            else
            {
                profileForm.Visibility = Visibility.Hidden;
            }
        }

        private void AddProfile_Click(object sender, RoutedEventArgs e)
        {
            profils.Add(new Profil() { Name = "Nom" });
            configDataRepository.SaveProfiles(profils);
            profileListView.Items.Refresh();
            profileListView.SelectedIndex = profileListView.Items.Count - 1;
        }

        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            profils.Remove(SelectedItem);
            configDataRepository.SaveProfiles(profils);
            profileListView.Items.Refresh();
        }

        private void TextBox_KeyUp(object sender, KeyEventArgs e)
        {
            profileListView.Items.Refresh();
        }

        private void TabControl_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (MainMenuTab.IsSelected && LoadMainMenu != null)
            {
                LoadMainMenu(this, e);
            }

            if (KeyBindingsTab.IsSelected)
            {
                DataContext = keybindings;
            }

            if (DebugTab != null && DebugTab.IsSelected)
            {
                DataContext = settings;
            }
        }

        private void KeybindingsTabs_Loaded(object sender, RoutedEventArgs e)
        {
            DataContext = keybindings;
        }
    }
}
