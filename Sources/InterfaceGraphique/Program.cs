using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Runtime.InteropServices;
using System.Windows.Threading;
using System.Windows.Interop;
using System.Windows.Media;
using System.Globalization;

namespace InterfaceGraphique
{
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60;

        public static Object unLock = new Object();
        public static bool peutAfficher = true;

        private static MainWindow window;
        private static TimeSpan dernierTemps;
        private static TimeSpan tempsAccumule;
        private static Stopwatch chrono = Stopwatch.StartNew();
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);
        
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary> 
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    if (FonctionsNatives.executerTests())
                        Debug.Write("Échec d'un ou plusieurs tests.");
                    else
                        Debug.Write("Tests réussis.");

                    return;
                } 

            chrono.Start();

            // Tiré de http://stackoverflow.com/questions/15811215/convert-number-in-textbox-to-float-c-sharp
            System.Threading.Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");

            Application app = new Application();
            var timer = new DispatcherTimer (
                TimeSpan.FromMilliseconds(1),
                DispatcherPriority.ApplicationIdle,
                (s, e) => ExecuterQuandInactif(s, e),
                app.Dispatcher
            );
            window = new MainWindow();

            app.Run(window);
        }

        static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;

            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                TimeSpan currentTime = chrono.Elapsed;
                TimeSpan elapsedTime = currentTime - dernierTemps;
                dernierTemps = currentTime;

                tempsAccumule += elapsedTime;

                if (tempsAccumule >= tempsEcouleVoulu)
                {
                    lock (unLock)
                    {
                        if (window != null && peutAfficher)
                            window.FrameUpdate((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
        }


        static partial class FonctionsNatives
        {
            [StructLayout(LayoutKind.Sequential)]
            public struct Message
            {
                public IntPtr hWnd;
                public uint Msg;
                public IntPtr wParam;
                public IntPtr lParam;
                public uint Time;
                public System.Drawing.Point Point;
            }

            [DllImport("User32.dll")]
            [return: MarshalAs(UnmanagedType.Bool)]
            public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool executerTests();

            
        }
    }
}
