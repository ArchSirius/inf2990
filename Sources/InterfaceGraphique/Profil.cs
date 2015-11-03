using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class Profil : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string name;
        private string suivisLigneEtatSuivant;

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

        public string Name
        {
            get { return name; }
            set
            {
                if (value != name)
                {
                    name = value;
                    OnPropertyChanged("Name");
                }
            }
        }

        public string SuivisLigneEtatSuivant
        {
            get { return suivisLigneEtatSuivant; }
            set
            {
                if (value != suivisLigneEtatSuivant)
                {
                    suivisLigneEtatSuivant = value;
                    OnPropertyChanged("SuivisLigneEtatSuivant");
                }
            }
        }
    }

}
