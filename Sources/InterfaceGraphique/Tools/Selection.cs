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
    /// @class Selection
    /// @brief Représente l'outil de sélection
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class Selection : Tool
    {
        public Selection(ToolContext context, Engine _engine) : base(context, _engine) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            engine.preparerRectangleElastique();
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            engine.terminerRectangleElastique();

            engine.prepareSelection();
            FonctionsNatives.dessinerOpenGL();
            
            if (Control.ModifierKeys == Keys.Control)
                engine.selectMultipleObjects(true);
            else
                engine.selectMultipleObjects(false);

        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            engine.prepareSelection();
            FonctionsNatives.dessinerOpenGL();

            if (Control.ModifierKeys == Keys.Control)
                engine.selectObject(true);
            else
                engine.selectObject(false);
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            if (!EditorController.dragEnter)
                engine.initialiserRectangleElastique();
            else
                engine.mettreAJourRectangleElastique();
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        public override void esc()
        {
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();
        }
    }
}
