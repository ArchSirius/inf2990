using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class SimulatorController
    {
        private Engine engine;
        public SimulatorController(Engine _engine)
        {
            engine = _engine;
        }

        public void InitializeGamePanel(IntPtr source, int width, int weight)
        {
            engine.initialiserOpenGL(source);
            engine.dessinerOpenGL();

            /// Pour une raison inconnue, si on fait la fonction moins de 4 fois, la
            /// fenêtre n'aura pas fait un redimensionnement suffisant. CEPENDANT, le
            /// redimensionnement OnResize est correct, puisqu'il s'appelle 60 fois/s.
            engine.redimensionnerFenetre(width, weight);
            engine.redimensionnerFenetre(width, weight);
            engine.redimensionnerFenetre(width, weight);
            engine.redimensionnerFenetre(width, weight);
            engine.redimensionnerFenetre(width, weight);

            FonctionsNatives.startSimulation();
        }
        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void startSimulation();
        }
         



    }
}
