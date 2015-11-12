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
    /// @class CreatePoteau
    /// @brief Représente l'outil de création de poteau
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class CreatePoteau : Tool
    {
        public const string nodeType = "cylindre";
        private ToolContext _context;
        private bool _validPos;

        public CreatePoteau(ToolContext context, Engine _engine) : base(context, _engine)
        {
            _context = context;
            _validPos = true;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (_validPos)
            {
                engine.addNode(nodeType);
            }
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
            if (engine.isMouseOnTable())
            {
                _validPos = true;
                Cursor.Current = Cursors.Default;
            }
            else
            {
                _validPos = false;
                Cursor.Current = Cursors.No;
            }
        }

        public override void esc()
        {
        }
    }
}
