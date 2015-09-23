using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class Move : Tool
    {
        public Move(ToolContext context)
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
            FonctionsNatives.translate(deltaX, deltaY, deltaZ);
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void translate(float deltaX, float deltaY, float deltaZ);
        }
    }
}
