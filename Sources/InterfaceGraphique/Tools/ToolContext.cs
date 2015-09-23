using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Tools
{
    class ToolContext
    {
        protected Tool activeTool;

        public ToolContext()
        {
            activeTool = new Selection(this);
        }

        public void ChangeState(Tool tool)
        {
            activeTool = tool;
        }

        public void LeftMouseClicked(MouseEventArgs e)
        {
            activeTool.LeftMouseClicked(e);
        }

        public void LeftMouseReleased(MouseEventArgs e)
        {
            activeTool.LeftMouseReleased(e);
        }

        public void Dragging()
        {
            activeTool.Dragging();
        }
    }
}
