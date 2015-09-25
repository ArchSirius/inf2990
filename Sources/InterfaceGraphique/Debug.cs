using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace InterfaceGraphique
{
    class Debug
    {
        public static void Write(String msg)
        {
            if (IsDebugEnabled())
            {
                System.Console.WriteLine(msg);
            }
        }

        public static bool IsDebugEnabled()
        {
            #if DEBUG
            return true;
            #else 
            return false;
            #endif
        }
    }
}
