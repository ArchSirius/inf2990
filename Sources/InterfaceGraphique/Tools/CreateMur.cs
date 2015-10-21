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
    /// @class CreateMur
    /// @brief Représente l'outil de création de murs
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class CreateMur : Tool
    {
        public const string nodeType = "mur";
        private bool _murStarted = false;
        private bool _validPos = true;

        public CreateMur(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            // Outil agit seulement au clic complet
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            // Outil agit seulement au clic complet
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (!_validPos)
                return;
            // Nouveau mur
            if (!_murStarted)
                engine.addNode(nodeType);
            // Si le mur est commencé, ça termine, sinon, ça le commence
            _murStarted = !_murStarted;
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            // Rien à faire
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
            if (_murStarted)
                engine.updateNode();
        }

        public override void esc()
        {
            if (_murStarted)
            {
                _murStarted = false;
                engine.abortTerminalNode();
            }
        }
    }
}
