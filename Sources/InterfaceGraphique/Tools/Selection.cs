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
        public Selection(ToolContext context)
            : base(context)
        {

        }

        public override void LeftMouseClicked(MouseEventArgs e)
        {
            FonctionsNatives.selectObject(false);
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {

        }

        public override void Dragging()
        {

        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void selectObject(bool keepOthers);
        }
    }
}
