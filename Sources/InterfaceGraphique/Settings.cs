using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    public struct DebugSettings
    {
        public bool CONSOLE;
        public bool TEST;
        public bool CAPTEUR_GAUCHE_SAFE;
        public bool CAPTEUR_GAUCHE_DANGER;
        public bool CAPTEUR_CENTRE_SAFE;
        public bool CAPTEUR_CENTRE_DANGER;
        public bool CAPTEUR_DROIT_SAFE;
        public bool CAPTEUR_DROIT_DANGER;
        public bool BALAYAGE;
        public bool LUM_AMBIANTE;
        public bool LUM_DIRECTIONNELLE;
        public bool LUM_SPOT;
        public bool COLLISION;
        public bool VISUALS;
        public bool LOG;
    }

    public class Settings : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private Profil defaultProfile;
        private DebugSettings debug;

        public Settings()
        {
            Test = InterfaceGraphique.Debug.IsDebugEnabled();
        }

        public Settings()
        {
            defaultProfile = new Profil();
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

        public bool Console
        {
            get { return debug.CONSOLE; }
            set
            {
                if (value != debug.CONSOLE)
                {
                    debug.CONSOLE = value;
                    OnPropertyChanged("Console");
                }
            }
        }

        public bool Test
        {
            get { return debug.TEST; }
            set
            {
                if (value != debug.TEST)
                {
                    debug.TEST = value;
                    OnPropertyChanged("Test");
                }
            }
        }

        public bool Capteur_gauche_safe
        {
            get { return debug.CAPTEUR_GAUCHE_SAFE; }
            set
            {
                if (value != debug.CAPTEUR_GAUCHE_SAFE)
                {
                    debug.CAPTEUR_GAUCHE_SAFE = value;
                    OnPropertyChanged("Capteur_gauche_safe");
                }
            }
        }

        public bool Capteur_gauche_danger
        {
            get { return debug.CAPTEUR_GAUCHE_DANGER; }
            set
            {
                if (value != debug.CAPTEUR_GAUCHE_DANGER)
                {
                    debug.CAPTEUR_GAUCHE_DANGER = value;
                    OnPropertyChanged("Capteur_gauche_danger");
                }
            }
        }

        public bool Capteur_centre_safe
        {
            get { return debug.CAPTEUR_CENTRE_SAFE; }
            set
            {
                if (value != debug.CAPTEUR_CENTRE_SAFE)
                {
                    debug.CAPTEUR_CENTRE_SAFE = value;
                    OnPropertyChanged("Capteur_centre_safe");
                }
            }
        }

        public bool Capteur_centre_danger
        {
            get { return debug.CAPTEUR_CENTRE_DANGER; }
            set
            {
                if (value != debug.CAPTEUR_CENTRE_DANGER)
                {
                    debug.CAPTEUR_CENTRE_DANGER = value;
                    OnPropertyChanged("Capteur_centre_danger");
                }
            }
        }

        public bool Capteur_droit_safe
        {
            get { return debug.CAPTEUR_DROIT_SAFE; }
            set
            {
                if (value != debug.CAPTEUR_DROIT_SAFE)
                {
                    debug.CAPTEUR_DROIT_SAFE = value;
                    OnPropertyChanged("Capteur_droit_safe");
                }
            }
        }

        public bool Capteur_droit_danger
        {
            get { return debug.CAPTEUR_DROIT_DANGER; }
            set
            {
                if (value != debug.CAPTEUR_DROIT_DANGER)
                {
                    debug.CAPTEUR_DROIT_DANGER = value;
                    OnPropertyChanged("Capteur_droit_danger");
                }
            }
        }

        public bool Balayage
        {
            get { return debug.BALAYAGE; }
            set
            {
                if (value != debug.BALAYAGE)
                {
                    debug.BALAYAGE = value;
                    OnPropertyChanged("Balayage");
                }
            }
        }

        public bool Lum_ambiante
        {
            get { return debug.LUM_AMBIANTE; }
            set
            {
                if (value != debug.LUM_AMBIANTE)
                {
                    debug.LUM_AMBIANTE = value;
                    OnPropertyChanged("Lum_ambiante");
                }
            }
        }

        public bool Lum_directionnelle
        {
            get { return debug.LUM_DIRECTIONNELLE; }
            set
            {
                if (value != debug.LUM_DIRECTIONNELLE)
                {
                    debug.LUM_DIRECTIONNELLE = value;
                    OnPropertyChanged("Lum_directionnelle");
                }
            }
        }

        public bool Lum_spot
        {
            get { return debug.LUM_SPOT; }
            set
            {
                if (value != debug.LUM_SPOT)
                {
                    debug.LUM_SPOT = value;
                    OnPropertyChanged("Lum_spot");
                }
            }
        }

        public bool Collision
        {
            get { return debug.COLLISION; }
            set
            {
                if (value != debug.COLLISION)
                {
                    debug.COLLISION = value;
                    OnPropertyChanged("Collision");
                }
            }
        }

        public bool Visuals
        {
            get { return debug.VISUALS; }
            set
            {
                if (value != debug.VISUALS)
                {
                    debug.VISUALS = value;
                    OnPropertyChanged("Visuals");
                }
            }
        }

        public bool Log
        {
            get { return debug.LOG; }
            set
            {
                if (value != debug.LOG)
                {
                    debug.LOG = value;
                    OnPropertyChanged("Log");
                }
            }
        }

    }
}