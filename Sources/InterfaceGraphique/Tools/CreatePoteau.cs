using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class CreatePoteau : Tool
    {
        public const string nodeType = "cylindre";
        private ToolContext _context;
        private bool _validPos;

        public CreatePoteau(ToolContext context)
            : base(context)
        {
            _context = context;
            _validPos = true;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (_validPos)
            {
                FonctionsNatives.addNode(nodeType);
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
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool isMouseOnTable();
        }
    }
}
