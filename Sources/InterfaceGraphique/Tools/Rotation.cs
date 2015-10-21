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
    /// @class Rotation
    /// @brief Représente l'outil de rotation
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class Rotation : Tool
    {
        public delegate void NodeChangedEventHandler();
        public event NodeChangedEventHandler NodeChangedEvent;

        int origX = 0;
        int origY = 0;

        public Rotation(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            engine.setInitPos();
            engine.setInitAngle();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            engine.checkValidPos();
            engine.setInitPos();
            engine.setInitAngle();
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            int vectX = System.Windows.Forms.Control.MousePosition.X - origX;
            int vectY = origY - System.Windows.Forms.Control.MousePosition.Y;
            engine.rotate(vectX, vectY, 0);

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
