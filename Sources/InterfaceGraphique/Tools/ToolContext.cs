using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class ToolContext
    {
        protected Tool activeTool;

        public ToolContext()
        {
            activeTool = new Selection(this);
        }

        public void ChangeState(Tool tool)
        {
            activeTool = tool;
        }

        public void LeftMouseClicked(MouseEventArgs e)
        {
            activeTool.LeftMouseClicked(e);
        }

        public void LeftMouseReleased(MouseEventArgs e)
        {
            activeTool.LeftMouseReleased(e);
        }

        public void RightMouseClicked(MouseEventArgs e)
        {
            FonctionsNatives.setViewInit();
        }

        public void Dragging(int deltaX, int deltaY, int deltaZ, bool clicIsLeft)
        {
            if (clicIsLeft)
            {
                activeTool.Dragging(deltaX, deltaY, deltaZ);
            }

            else
            {
                FonctionsNatives.deplacerXYSouris();
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXY(double deplacementX, double deplacementY);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setViewInit();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void deplacerXYSouris();
        }
    }
}
