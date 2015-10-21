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
    /// @class Duplicate
    /// @brief Représente l'outil de duplication
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class Duplicate : Tool
    {
        public Duplicate(ToolContext context, Engine _engine) : base(context, _engine)
        {
            engine.setInitPos();
            engine.initializeDuplication();
        }

        ~Duplicate()
        {
            engine.endDuplication();
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            engine.endDuplication();
            context.resetState();
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
            if (engine.isMouseOnTable())
            {
                Cursor.Current = Cursors.Default;
            }
            else
            {
                Cursor.Current = Cursors.No;
            }

            engine.updateDuplication();
        }

        public override void esc()
        {
        }
    }
}
