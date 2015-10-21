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
    /// @class Scale
    /// @brief Représente l'outil de mise à l'échelle
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class Scale : Tool
    {
        public delegate void NodeChangedEventHandler();
        public event NodeChangedEventHandler NodeChangedEvent;

        int origX = 0;
        int origY = 0;

        public Scale(ToolContext context)
            : base(context)
        {

        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            FonctionsNatives.setInitScale();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.checkValidPos();
            FonctionsNatives.setInitScale();
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            int vectX = System.Windows.Forms.Control.MousePosition.X - origX;
            int vectY = origY - System.Windows.Forms.Control.MousePosition.Y;
            FonctionsNatives.scale(vectX, vectY, 0);

            if (NodeChangedEvent != null)
                NodeChangedEvent();
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        public override void esc()
        {
        }
    }
}
