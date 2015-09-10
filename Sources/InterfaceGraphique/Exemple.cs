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
        private bool boutonSourisEnfoncee = false;

        public Exemple()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            InitializeComponent();
            InitialiserAnimation();
            this.panel1.MouseDown += new MouseEventHandler(BoutonSourisEnfonce);
            this.panel1.MouseUp += new MouseEventHandler(BoutonSourisRelache);
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
                    FonctionsNatives.animer(tempsInterAffichage);
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

        private void BoutonSourisEnfonce(Object o, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                System.Console.WriteLine("Touche enfoncée en [{0}, {1}]", MousePosition.X, MousePosition.Y);
                boutonSourisEnfoncee = true;
                System.Threading.Thread t = new System.Threading.Thread(DetecterDrag);
                t.Start();
            }
        }

        private void BoutonSourisRelache(Object o, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                boutonSourisEnfoncee = false;
                System.Console.WriteLine("Touche relachée en [{0}, {1}]" + Environment.NewLine, MousePosition.X, MousePosition.Y);
            }
        }

        private void DetecterDrag()
        {
            int x = MousePosition.X;
            int y = MousePosition.Y;

            while (boutonSourisEnfoncee)
            {
                if (positionSourisChangee(x, y, 100))
                {
                    System.Console.WriteLine("Drag & Drop en cours.");
                    while (boutonSourisEnfoncee)
                    {
                        if (positionSourisChangee(x, y, 5))
                        {
                            System.Console.WriteLine("[{0}, {1}]", MousePosition.X, MousePosition.Y);
                            x = MousePosition.X;
                            y = MousePosition.Y;
                        }
                    }
                    System.Console.WriteLine("Drag & Drop terminé.");
                }
            }

        }

        private bool positionSourisChangee(int x, int y, int delta)
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
    }
}
