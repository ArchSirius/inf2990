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
            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectObject(true);
            else
                FonctionsNatives.selectObject(false);

            //FonctionsNatives.initialiserRectangleElastique();

            if (SelectedEvent != null)
                SelectedEvent(FonctionsNatives.getNbNodesSelected());

        }
        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.terminerRectangleElastique();
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            // Juste pour ne pas briser implementation actuelle
            // Apres amelioration du rectangle elastique, cette
            // fonction ne sera plus a utiliser dans LeftMouseFullClicked,
            // car un rectangle elastique ne sera cree uniquement en cas de drag
            // et pas au mousePressed. :P
            FonctionsNatives.terminerRectangleElastique();
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectObject(bool keepOthers);

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
