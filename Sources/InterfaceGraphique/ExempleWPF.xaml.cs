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
using System.Windows.Interop;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class ExempleWPF : Window
    {
        public ExempleWPF()
        {
            InitializeComponent();
            InitializeGamePanel();
        }

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

        private void InitializeGamePanel()
        {
            GamePanel.Size = new System.Drawing.Size(623, 428);

            IntPtr source = GamePanel.Handle;
            FonctionsNatives.initialiserOpenGL(source);
            FonctionsNatives.dessinerOpenGL();
        }
    }
}
