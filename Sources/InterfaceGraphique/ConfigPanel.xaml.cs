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
        private bool shouldSave;
        private bool ShouldSave
        {
            get { return shouldSave; }
            set
            {
                shouldSave = value;

                if (value == true && SelectedItem.CompareTo(profils[0]) != 0)
                {
                    saveBtn.IsEnabled = true;
                }
                else
                {
                    saveBtn.IsEnabled = false;
                }
            }
        }

        public ConfigPanel()
        {
            InitializeComponent();
            configDataRepository = new ConfigPanelData();
            settings = configDataRepository.LoadSettings();
            keybindings = configDataRepository.LoadKeybindings();
            profils = configDataRepository.LoadProfiles();
            profileListView.ItemsSource = profils;
            ShouldSave = false;

            settings.PropertyChanged += SaveSettings;
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            Save();
        }

        private bool Save()
        {
            bool err = false;

            foreach (var profil in profils)
            {
                err |= profil.Error != "";
            }

            if (err)
            {
                System.Windows.MessageBox.Show("Il n’est pas possible d'enregistrer car tous les champs de sont pas validés: " + SelectedItem.Error, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            ShouldSave = false;
            configDataRepository.SaveProfiles(profils);

            return true;
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

            if (e.Key == Key.T)
            {
                System.Windows.MessageBox.Show("Cette touche est réservéee pour la désactivation du mode test.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                e.Handled = true;
                return;
            }

            ((TextBox)sender).Text = "";

            foreach (PropertyInfo prop in keybindings.GetType().GetProperties())
            {
                if (prop.Name != ((TextBox)sender).GetBindingExpression(TextBox.TextProperty).ResolvedSourcePropertyName && (prop.GetValue(keybindings)).ToString() == e.Key.ToString())
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
            ShouldSave = true;
            if (((Profil)o).Error != "")
            {
                saveBtn.IsEnabled = false;
                addProfilBtn.IsEnabled = false;
            }
            else if (profils[0].CompareTo(o) != 0)
            {
                saveBtn.IsEnabled = true;
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
                    saveBtn.IsEnabled = ShouldSave;
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

        private void TabControl_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            //if (ShouldSave)
            //{
            //    var choice = System.Windows.MessageBox.Show("Voulez-vous enregistrer vos modifications?", "Modifications", MessageBoxButton.YesNoCancel);
            //
            //    if (choice == MessageBoxResult.Yes)
            //    {
            //        if (!Save())
            //        {
            //            e.Handled = true;
            //            return;
            //        }
            //    }
            //}
            //
            //e.Handled = false;
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
