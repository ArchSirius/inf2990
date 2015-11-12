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
    /// @class ZoomRectangle
    /// @brief Représente l'outil de zoom avec rectangle élastique
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class ZoomRectangle : Tool
    {
        public ZoomRectangle(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            engine.preparerRectangleElastique();
        }
        public override void LeftMouseReleased(MouseEventArgs e)
        {  
            engine.terminerRectangleElastique();

            if (Control.ModifierKeys == Keys.Alt)
                engine.zoomOutRectangle();
            else
                engine.zoomInRectangle();
                
        }
        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            if (!EditorController.dragEnter)
                engine.initialiserRectangleElastique();
            else
                engine.mettreAJourRectangleElastique();
        }
    }
}
