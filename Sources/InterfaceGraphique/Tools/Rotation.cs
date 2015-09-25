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
        int origX = 0;
        int origY = 0;

        public Rotation(ToolContext context)
            : base(context)
        {

        }

        public override void LeftMouseClicked(MouseEventArgs e)
        {
            FonctionsNatives.setInitPos();
            FonctionsNatives.setInitAngle();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {

        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            int vectX = System.Windows.Forms.Control.MousePosition.X - origX;
            int vectY = origY - System.Windows.Forms.Control.MousePosition.Y;
            FonctionsNatives.rotate(vectX, vectY, 0);
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void rotate(float deltaX, float deltaY, float deltaZ);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitPos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitAngle();
        }
    }
}
