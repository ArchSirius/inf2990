using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class Selection : Tool
    {
        public delegate void SelectedEventHandler(int nbSelected);
        public event SelectedEventHandler SelectedEvent;

        public Selection(ToolContext context) : base(context) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            FonctionsNatives.preparerRectangleElastique();

            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectObject(true);
            else
                FonctionsNatives.selectObject(false);

            if (SelectedEvent != null)
                SelectedEvent(FonctionsNatives.getNbNodesSelected());

        }
        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.terminerRectangleElastique();
            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectMultipleObjects(true);
            else
                FonctionsNatives.selectMultipleObjects(false);
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {

        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            if (!EditorController.dragEnter)
                FonctionsNatives.initialiserRectangleElastique();
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectObject(bool keepOthers);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectMultipleObjects(bool keepOthers);
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void preparerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int getNbNodesSelected();
        }



    }
}
