using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class CreatePoteau : Tool
    {
        public const string nodeType = "cylindre";
        private ToolContext _context;

        public CreatePoteau(ToolContext context)
            : base(context)
        {
            _context = context;
        }

        public override void LeftMouseClicked(MouseEventArgs e)
        {
            /// TODO Vérifier position
            /// si position valide
            FonctionsNatives.addNode(nodeType);
            _context.resetState();
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
            
        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            
        }

        public override void MouseMove(MouseEventArgs e)
        {
            /// TODO Vérifier position
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);
        }
    }
}
