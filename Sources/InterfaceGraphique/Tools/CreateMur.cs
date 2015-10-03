using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class CreateMur : Tool
    {
        public const string nodeType = "mur";
        private ToolContext _context;
        private bool _ghostStarted;

        public CreateMur(ToolContext context)
            : base(context)
        {
            _context = context;
            _ghostStarted = false;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            /// Premier clic
            /// TODO Vérifier position
            /// si position valide
            _ghostStarted = true;
            /// TODO Créer mur fantôme
            FonctionsNatives.addNode(nodeType);

            /// Deuxième clic
            /// TODO Vérifier position; si valide, créer vrai mur
            _ghostStarted = false;
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
            /// TODO Actualiser le mur fantôme
            /// TODO Vérifier position
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);
        }
    }
}
