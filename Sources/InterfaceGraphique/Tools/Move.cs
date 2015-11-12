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
    /// @class Move
    /// @brief Représente l'outil de déplacement
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class Move : Tool
    {
        int origX = 0;
        int origY = 0;

        public Move(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            engine.setInitPos();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            engine.checkValidPos();
            engine.setInitPos();
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            // not using deltas
            // using vector
            int vectX = System.Windows.Forms.Control.MousePosition.X - origX;
            int vectY = origY - System.Windows.Forms.Control.MousePosition.Y;
            engine.translate(vectX, vectY, 0);
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        public override void esc()
        {
        }
    }
}
