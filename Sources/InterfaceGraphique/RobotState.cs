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
            Add(new RobotState(0, "Défaut"));
            Add(new RobotState(1, "Suivis de ligne"));
            Add(new RobotState(2, "Balayage sur 180 degrés"));
            Add(new RobotState(3, "Déviation vers la gauche"));
            Add(new RobotState(4, "Déviation vers la droite"));
            Add(new RobotState(5, "Évitement vers la gauche"));
            Add(new RobotState(6, "Évitement vers la droite"));
        }
    }

    public class RobotState : IComparable
    {
        private int _code;
        private string _name;

        public RobotState(int code, string name)
        {
            _code = code;
            _name = name;
        }

        public int Code
        {
            get { return _code; }
            set { _code = value; }
        }

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public int CompareTo(object obj)
        {
            return Code.CompareTo(((RobotState)obj).Code);
        }
    }
}
