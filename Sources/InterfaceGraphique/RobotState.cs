using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    public class RobotStateList : List<RobotState>
    {
        public RobotStateList()
        {

        }
    }

    public class RobotState : IComparable
    {
        private string _code;
        private string _name;

        public RobotState(string code, string name)
        {
            _code = code;
            _name = name;
        }

        public string Code
        {
            get { return _code; }
            set { _code = value; }
        }

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public int CompareTo(RobotState obj)
        {
            return Code.CompareTo(obj.Code);
        }
    }
}
