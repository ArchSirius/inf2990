using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class Duplicate : Tool
    {
        private ToolContext _context;
        private bool _validPos;

        public Duplicate(ToolContext context)
            : base(context)
        {
            _context = context;
            _validPos = true;
            FonctionsNatives.setInitPos();
        }

        ~Duplicate()
        {
            FonctionsNatives.endDuplication();
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            FonctionsNatives.endDuplication();
            _context.resetState();
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

            FonctionsNatives.updateDuplication();
        }

        public override void esc()
        {
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void duplicate();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitPos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool isMouseOnTable();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool updateDuplication();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool endDuplication();
        }
    }
}
