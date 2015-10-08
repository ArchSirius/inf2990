using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class CreateMur
    /// @brief Représente l'outil de création de murs
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class CreateMur : Tool
    {
        public const string nodeType = "mur";
        private ToolContext _context;
        private bool _murStarted = false;
        private bool _validPos = true;

        public CreateMur(ToolContext context)
            : base(context)
        {
            _context = context;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            // Outil agit seulement au clic complet
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            // Outil agit seulement au clic complet
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (!_validPos)
                return;
            // Nouveau mur
            if (!_murStarted)
                FonctionsNatives.addNode(nodeType);
            // Si le mur est commencé, ça termine, sinon, ça le commence
            _murStarted = !_murStarted;
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            // Rien à faire
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
            if (_murStarted)
                FonctionsNatives.updateNode();
        }

        public override void esc()
        {
            if (_murStarted)
            {
                _murStarted = false;
                FonctionsNatives.abortTerminalNode();
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool isMouseOnTable();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool updateNode();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool abortTerminalNode();
        }
    }
}
