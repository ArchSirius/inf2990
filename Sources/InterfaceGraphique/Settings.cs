using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class Settings
    {
        private Profil defaultProfile;

        public Profil DefaultProfile
        {
            get { return defaultProfile; }
            set { defaultProfile = value; }
        }
    }
}