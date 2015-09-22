using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    abstract class Tool
    {
        private ToolContext context;

        public Tool(ToolContext c)
        {
            context = c;
        }

        public void LeftMouseClicked(MouseEventArgs e);
        public void LeftMouseReleased(MouseEventArgs e);
        public void Dragging();
    }
}
