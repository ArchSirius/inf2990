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
        public delegate void SelectedEventHandler(int nbSelected);
        public event SelectedEventHandler SelectedEvent;

        public Selection(ToolContext context) : base(context) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            FonctionsNatives.preparerRectangleElastique();
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.terminerRectangleElastique();
            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectMultipleObjects(true);
            else
                FonctionsNatives.selectMultipleObjects(false);

            if (SelectedEvent != null)
                SelectedEvent(FonctionsNatives.getNbNodesSelected());
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectObject(true);
            else
                FonctionsNatives.selectObject(false);

            if (SelectedEvent != null)
                SelectedEvent(FonctionsNatives.getNbNodesSelected());
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            if (!EditorController.dragEnter)
                FonctionsNatives.initialiserRectangleElastique();
            else
                FonctionsNatives.mettreAJourRectangleElastique();
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        public override void esc()
        {
        }
    }
}
