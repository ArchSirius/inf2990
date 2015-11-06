using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace InterfaceGraphique
{
    public class KeyBindings
    {
        /// Touches mode de conduite manuelle.
        private Key forward = Key.W;
        private Key reverse = Key.S;
        private Key turnRight = Key.D;
        private Key turnLeft = Key.A;
        private Key toggle = Key.Space;

        public String Forward
        {
            get { return forward.ToString(); }
            set { forward = getKeyFromValue(value); }
        }

        public String Reverse
        {
            get { return reverse.ToString(); }
            set { reverse = getKeyFromValue(value); }
        }

        public String TurnRight
        {
            get { return turnRight.ToString(); }
            set { turnRight = getKeyFromValue(value); }
        }

        public String TurnLeft
        {
            get { return turnLeft.ToString(); }
            set { turnLeft = getKeyFromValue(value); }
        }

        public String Toggle
        {
            get { return toggle.ToString(); }
            set { toggle = getKeyFromValue(value); }
        }

        private Key getKeyFromValue(String value)
        {
            if (value == " ")
            {
                return Key.Space;
            }

            return (Key)(new KeyConverter()).ConvertFromString(value);
        }
    }
}
