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

        public virtual void LeftMousePressed(MouseEventArgs e)
        {

        }

        public virtual void LeftMouseReleased(MouseEventArgs e)
        {
            
        }

        public virtual void LeftMouseFullClicked(MouseEventArgs e)
        {

        }

        public virtual void Dragging(int deltaX, int deltaY, int deltaZ)
        {

        }

        public virtual void MouseMove(MouseEventArgs e)
        {

        }
        public virtual void buttonAltDown()
        {

        }
        public virtual void buttonAltUp()
        {

        } 
    }
}
