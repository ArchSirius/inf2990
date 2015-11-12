using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    [StructLayout(LayoutKind.Sequential)]
    public struct DebugSettings
    {
        public int CONSOLE;
        public int TEST;
        public int CAPTEUR_GAUCHE_SAFE;
        public int CAPTEUR_GAUCHE_DANGER;
        public int CAPTEUR_CENTRE_SAFE;
        public int CAPTEUR_CENTRE_DANGER;
        public int CAPTEUR_DROIT_SAFE;
        public int CAPTEUR_DROIT_DANGER;
        public int BALAYAGE;
        public int LUM_AMBIANTE;
        public int LUM_DIRECTIONNELLE;
        public int LUM_SPOT;
        public int COLLISION;
        public int VISUALS;
        public int LOG;
    }

    public class Settings : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private Profil defaultProfile;
        private DebugSettings debug;

        public Settings()
        {
            defaultProfile = new Profil();
            Test = InterfaceGraphique.Debug.IsDebugEnabled();
            Console = true;
            Capteur_gauche_safe = true;
            Capteur_gauche_danger = true;
            Capteur_centre_safe = true;
            Capteur_centre_danger = true;
            Capteur_droit_safe = true;
            Capteur_droit_danger = true;
            Balayage = true;
            Lum_ambiante = true;
            Lum_directionnelle = true;
            Lum_spot = true;
            Collision = true;
            Visuals = true;
            Log = true;
        }

        public Profil DefaultProfile
        {
            get { return defaultProfile; }
            set { defaultProfile = value; }
        }


        // http://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed
        private void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
                handler(this, e);
        }

        // http://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed
        protected void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        public DebugSettings getDebugSettings()
        {
            return debug;
        }

        public bool Console
        {
            get { return int2bool(debug.CONSOLE); }
            set
            {
                if (value != int2bool(debug.CONSOLE))
                {
                    debug.CONSOLE = bool2int(value);
                    OnPropertyChanged("Console");
                }
            }
        }

        public bool Test
        {
            get { return int2bool(debug.TEST); }
            set
            {
                if (value != int2bool(debug.TEST))
                {
                    debug.TEST = bool2int(value);
                    OnPropertyChanged("Test");
                }
            }
        }

        public bool Capteur_gauche_safe
        {
            get { return int2bool(debug.CAPTEUR_GAUCHE_SAFE); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_GAUCHE_SAFE))
                {
                    debug.CAPTEUR_GAUCHE_SAFE = bool2int(value);
                    OnPropertyChanged("Capteur_gauche_safe");
                }
            }
        }

        public bool Capteur_gauche_danger
        {
            get { return int2bool(debug.CAPTEUR_GAUCHE_DANGER); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_GAUCHE_DANGER))
                {
                    debug.CAPTEUR_GAUCHE_DANGER = bool2int(value);
                    OnPropertyChanged("Capteur_gauche_danger");
                }
            }
        }

        public bool Capteur_centre_safe
        {
            get { return int2bool(debug.CAPTEUR_CENTRE_SAFE); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_CENTRE_SAFE))
                {
                    debug.CAPTEUR_CENTRE_SAFE = bool2int(value);
                    OnPropertyChanged("Capteur_centre_safe");
                }
            }
        }

        public bool Capteur_centre_danger
        {
            get { return int2bool(debug.CAPTEUR_CENTRE_DANGER); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_CENTRE_DANGER))
                {
                    debug.CAPTEUR_CENTRE_DANGER = bool2int(value);
                    OnPropertyChanged("Capteur_centre_danger");
                }
            }
        }

        public bool Capteur_droit_safe
        {
            get { return int2bool(debug.CAPTEUR_DROIT_SAFE); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_DROIT_SAFE))
                {
                    debug.CAPTEUR_DROIT_SAFE = bool2int(value);
                    OnPropertyChanged("Capteur_droit_safe");
                }
            }
        }

        public bool Capteur_droit_danger
        {
            get { return int2bool(debug.CAPTEUR_DROIT_DANGER); }
            set
            {
                if (value != int2bool(debug.CAPTEUR_DROIT_DANGER))
                {
                    debug.CAPTEUR_DROIT_DANGER = bool2int(value);
                    OnPropertyChanged("Capteur_droit_danger");
                }
            }
        }

        public bool Balayage
        {
            get { return int2bool(debug.BALAYAGE); }
            set
            {
                if (value != int2bool(debug.BALAYAGE))
                {
                    debug.BALAYAGE = bool2int(value);
                    OnPropertyChanged("Balayage");
                }
            }
        }

        public bool Lum_ambiante
        {
            get { return int2bool(debug.LUM_AMBIANTE); }
            set
            {
                if (value != int2bool(debug.LUM_AMBIANTE))
                {
                    debug.LUM_AMBIANTE = bool2int(value);
                    OnPropertyChanged("Lum_ambiante");
                }
            }
        }

        public bool Lum_directionnelle
        {
            get { return int2bool(debug.LUM_DIRECTIONNELLE); }
            set
            {
                if (value != int2bool(debug.LUM_DIRECTIONNELLE))
                {
                    debug.LUM_DIRECTIONNELLE = bool2int(value);
                    OnPropertyChanged("Lum_directionnelle");
                }
            }
        }

        public bool Lum_spot
        {
            get { return int2bool(debug.LUM_SPOT); }
            set
            {
                if (value != int2bool(debug.LUM_SPOT))
                {
                    debug.LUM_SPOT = bool2int(value);
                    OnPropertyChanged("Lum_spot");
                }
            }
        }

        public bool Collision
        {
            get { return int2bool(debug.COLLISION); }
            set
            {
                if (value != int2bool(debug.COLLISION))
                {
                    debug.COLLISION = bool2int(value);
                    OnPropertyChanged("Collision");
                }
            }
        }

        public bool Visuals
        {
            get { return int2bool(debug.VISUALS); }
            set
            {
                if (value != int2bool(debug.VISUALS))
                {
                    debug.VISUALS = bool2int(value);
                    OnPropertyChanged("Visuals");
                }
            }
        }

        public bool Log
        {
            get { return int2bool(debug.LOG); }
            set
            {
                if (value != int2bool(debug.LOG))
                {
                    debug.LOG = bool2int(value);
                    OnPropertyChanged("Log");
                }
            }
        }

        private bool int2bool(int i)
        {
            return i == 0 ? false : true;
        }

        private int bool2int(bool b)
        {
            return b ? 1 : 0;
        }

    }
}