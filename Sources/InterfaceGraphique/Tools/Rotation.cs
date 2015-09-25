using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class Rotation : Tool
    {
        public Rotation(ToolContext context)
            : base(context)
        {

        }

        public override void LeftMouseClicked(MouseEventArgs e)
        {

        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {

        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            FonctionsNatives.rotate();
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void rotate();
        }
    }
}
