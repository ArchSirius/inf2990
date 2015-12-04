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
    /// @class CreateLigne
    /// @brief Représente l'outil de création de lignes
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class CreateLigne : Tool
    {
        public const string nodeType = "ligne";
        private const string _lineType = "ligne";
        private const string _segmentType = "segment";
        private bool _ligneStarted = false;
        private bool _validPos = true;

        public CreateLigne(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (!_validPos)
            {
                return;
            }
            
            // Nouvelle ligne
            if (!_ligneStarted)
            {
                _ligneStarted = true;
                engine.addNode(_lineType);
                engine.addNode(_segmentType);
            }
            else
            {
                // Nouveau segment
                if (Control.ModifierKeys == Keys.Control)
                {
                    engine.addNode(_segmentType);
                }
                // Terminer ligne
                else
                {
                    _ligneStarted = false;
                }
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

            if (_ligneStarted)
               engine.updateNode();
        }

        public override void esc()
        {
            if (_ligneStarted)
            {
                _ligneStarted = false;
                engine.abortCompositeNode();
            }
        }
    }
}
