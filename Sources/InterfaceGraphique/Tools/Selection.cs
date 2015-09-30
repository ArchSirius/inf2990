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
        public Selection(ToolContext context) : base(context) { }

        public override void LeftMouseClicked(MouseEventArgs e)
        {
            if (Control.ModifierKeys == Keys.Control)
                FonctionsNatives.selectObject(true);
            else
                FonctionsNatives.selectObject(false);
            FonctionsNatives.initialiserRectangleElastique();
        }
        public override void LeftMouseReleased(MouseEventArgs e)
        {
            FonctionsNatives.terminerRectangleElastique();
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
        }



    }
}
