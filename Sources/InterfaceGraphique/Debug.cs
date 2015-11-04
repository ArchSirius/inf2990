using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace InterfaceGraphique
{
    class Debug
    {
        public static void Write(String msg, params object[] data)
        {
            if (IsDebugEnabled())
            {
                System.Console.WriteLine(msg, data);
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

        internal static void WriteLine(string msg)
        {
           
            if (IsDebugEnabled())
            {
                System.Console.WriteLine( msg);
            }

       
        }
    }
}
