using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace InterfaceGraphique
{
    public partial class Exemple : Form
    {
        private bool MouseClicked = false;

        public Exemple()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            InitializeComponent();
            InitialiserAnimation();
            this.panel1.MouseDown += new MouseEventHandler(MouseButtonDown);
            this.panel1.MouseUp += new MouseEventHandler(MouseButtonUp);
        }

        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    //FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                });
            }
            catch (Exception)
            {
            }
            
        }

        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée.");
            }
        }

        private void MouseButtonDown(Object o, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                System.Console.WriteLine("Touche enfoncée en [{0}, {1}]", MousePosition.X, MousePosition.Y);
                MouseClicked = true;
                System.Threading.Thread t = new System.Threading.Thread(DetectDrag);
                t.Start();
            }
        }

        private void MouseButtonUp(Object o, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseClicked = false;
                System.Console.WriteLine("Touche relachée en [{0}, {1}]" + Environment.NewLine, MousePosition.X, MousePosition.Y);
            }
        }

        private void DetectDrag()
        {
            int x = MousePosition.X;
            int y = MousePosition.Y;

            while (MouseClicked)
            {
                if (MouseMoved(x, y, 5))
                {
                    System.Console.WriteLine("Drag & Drop en cours.");
                    while (MouseClicked)
                    {
                        if (MouseMoved(x, y, 1))
                        {
                            System.Console.WriteLine("[{0}, {1}]; Bougé de {2}, {3}", MousePosition.X, MousePosition.Y, MousePosition.X - x, MousePosition.Y - y);
                            FonctionsNatives.translate(MousePosition.X - x, MousePosition.Y - y, 0);
                            x = MousePosition.X;
                            y = MousePosition.Y;
                        }
                    }
                    System.Console.WriteLine("Drag & Drop terminé.");
                }
            }

        }

        private bool MouseMoved(int x, int y, int delta)
        {
            return (Math.Abs(x - MousePosition.X) > delta || Math.Abs(y - MousePosition.Y) > delta);
        }


        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Console.WriteLine("Nouveau");            
        }
        
        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Console.WriteLine("Quitter");
        }

        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock(Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }
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
        public static extern void translate(int x, int y, int z);
    }
}
