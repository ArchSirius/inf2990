using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    public interface Observable
    {
        void subscribe(Observer o);
        void unsubscribe(Observer o);
    }
}
