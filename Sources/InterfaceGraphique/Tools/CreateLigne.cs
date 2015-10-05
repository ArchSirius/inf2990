using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique.Tools
{
    class CreateLigne : Tool
    {
        public const string nodeType = "ligne";
        private const string _lineType = "ligne";
        private const string _segmentType = "segment";
        private ToolContext _context;
        private bool _ligneStarted = false;
        private bool _validPos = true;

        public CreateLigne(ToolContext context)
            : base(context)
        {
            _context = context;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (!_validPos)
            {
                return;
            }

            // Nouvelle ligne
            if (!_ligneStarted)
            {
                _ligneStarted = true;
                Debug.Write("Nouvelle ligne\n");
                FonctionsNatives.addNode(_lineType);
                FonctionsNatives.addNode(_segmentType);
            }
            else
            {
                // Nouveau segment
                if (Control.ModifierKeys == Keys.Control)
                {
                    Debug.Write("nouveau segment\n");
                    FonctionsNatives.addNode(_segmentType);
                }
                // Terminer ligne
                else
                {
                    _ligneStarted = false;
                    Debug.Write("Fin de ligne\n");
                }
            }
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
            if (FonctionsNatives.isMouseOnTable())
            {
                _validPos = true;
                Cursor.Current = Cursors.Default;
            }
            else
            {
                _validPos = false;
                Cursor.Current = Cursors.No;
            }

            if (_ligneStarted)
               FonctionsNatives.updateNode();
        }

        public override void esc()
        {
            if (_ligneStarted)
            {
                _ligneStarted = false;
                Debug.Write("ABORT\n");
                FonctionsNatives.abortCompositeNode();
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool isMouseOnTable();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]

            public static extern void afficherFantome();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool updateNode();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool abortCompositeNode();
        }
    }
}
