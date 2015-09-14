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
using Forms = System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interaction logic for wpftest.xaml
    /// </summary>
    public partial class ExempleWPF : Page, Renderable
    {
        private bool mouseClicked = false;

        public ExempleWPF()
        {
            InitializeComponent();
            InitializeGamePanel();

            // Ne pas enlever Forms : c'est pour éviter l'ambiguïté.
            KeyDown += KeyPressed;
            GamePanel.MouseDown += new Forms.MouseEventHandler(MouseButtonDown);
            GamePanel.MouseUp += new Forms.MouseEventHandler(MouseButtonUp);
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

        private void KeyPressed(object o, KeyEventArgs e)
        {
            if (e.Key == Key.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée.");
            }
            else if (e.Key == Key.A)
            {
                System.Console.WriteLine("a appuyée.");
                FonctionsNatives.deplacerXY(5.0, 5.0);
            }
        }

        private void MouseButtonDown(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                System.Console.WriteLine("Touche enfoncée en [{0}, {1}]", Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
                mouseClicked = true;
                Thread t = new Thread(DetectDrag);
                t.Start();
            }
        }

        private void MouseButtonUp(Object o, Forms.MouseEventArgs e)
        {
            if (e.Button == Forms.MouseButtons.Left)
            {
                mouseClicked = false;
                System.Console.WriteLine("Touche relachée en [{0}, {1}]" + Environment.NewLine, Forms.Control.MousePosition.X, Forms.Control.MousePosition.Y);
            }
        }

        private void DetectDrag()
        {
            int x = Forms.Control.MousePosition.X;
            int y = Forms.Control.MousePosition.Y;

            while (mouseClicked)
            {
                if (MouseMoved(x, y, 5))
                {
                    System.Console.WriteLine("Drag & Drop en cours.");
                    while (mouseClicked)
                    {
                        if (MouseMoved(x, y, 1))
                        {
                            System.Console.WriteLine("[{0}, {1}]; Bougé de {2}, {3}",
                                Forms.Control.MousePosition.X,
                                Forms.Control.MousePosition.Y,
                                Forms.Control.MousePosition.X - x,
                                Forms.Control.MousePosition.Y - y
                            );
                            x = Forms.Control.MousePosition.X;
                            y = Forms.Control.MousePosition.Y;
                        }
                    }
                    System.Console.WriteLine("Drag & Drop terminé.");
                }
            }

        }

        private bool MouseMoved(int x, int y, int delta)
        {
            return (Math.Abs(x - Forms.Control.MousePosition.X) > delta || Math.Abs(y - Forms.Control.MousePosition.Y) > delta);
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserOpenGL(IntPtr handle);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void libererOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(double temps);

             [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);
        }
    }
}
