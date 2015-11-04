using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace InterfaceGraphique
{
    class KeyBindings
    {
        /// Touches mode de conduite manuelle.
        private Key forward = Key.W;
        private Key reverse = Key.S;
        private Key turnRight = Key.D;
        private Key turnLeft = Key.A;
        private Key toggle = Key.Space;
        private bool manualMode = false;

        public Key Forward
        {
            get { return forward; }
            set {forward = value; }
        }

        public Key Reverse
        {
            get { return reverse; }
            set { reverse = value; }
        }
        public Key TurnRight
        {
            get { return turnRight; }
            set { turnRight = value; }
        }

        public Key TurnLeft
        {
            get { return turnLeft; }
            set { turnLeft = value; }
        }
        public Key Toggle
        {
            get { return toggle; }
            set { toggle = value; }
        }
        public bool ManualMode
        {
            get { return manualMode; }
            set { manualMode = value; }
        }
    }
}
