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
        public delegate void NodeChangedEventHandler();
        public event NodeChangedEventHandler NodeChangedEvent;

        int origX = 0;
        int origY = 0;

        public Rotation(ToolContext context)
            : base(context)
        {

        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            FonctionsNatives.setInitPos();
            FonctionsNatives.setInitAngle();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.checkValidPos();
            FonctionsNatives.setInitPos();
            FonctionsNatives.setInitAngle();
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            int vectX = System.Windows.Forms.Control.MousePosition.X - origX;
            int vectY = origY - System.Windows.Forms.Control.MousePosition.Y;
            FonctionsNatives.rotate(vectX, vectY, 0);

            if (NodeChangedEvent != null)
                NodeChangedEvent();
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void rotate(float deltaX, float deltaY, float deltaZ);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitPos();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setInitAngle();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void checkValidPos();
        }
    }
}
