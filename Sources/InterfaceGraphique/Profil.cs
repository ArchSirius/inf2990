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
    struct ProfileData
    {
        /// Etat suivant FollowLine
        public int followLineNextState;

        /// Etat suivant SearchLine
        public int searchLineNextState;

        /// Angle de rotation et Etat suivant DiviationLeft
        public int deviationLeftNextState;
        public float deviationLeftAngle;

        /// Angle de rotation et Etat suivant DeviationRight
        public int deviationRightNextState;
        public float deviationRightAngle;

        /// Angle, duree, et Etat suivant AvoidLeft
        public int avoidLeftNextState;
        public float avoidLeftAngle;
        public double avoidLeftTime;

        /// Angle, duree, et Etat suivant AvoidRight
        public int avoidRightNextState;
        public float avoidRightAngle;
        public double avoidRightTime;

        /// Capteurs --- enabled / disabled
        public int leftDistanceSensor;
        public int rightDistanceSensor;
        public int centerDistanceSensor;
        public int capteurLigne;

        /// Capteurs --- ligne + distances
        public int leftSensorDangerState;
        public int leftSensorSafeState;
        public int centerSensorDangerState;
        public int centerSensorSafeState;
        public int rightSensorDangerState;
        public int rightSensorSafeState;
    }

    class Profil : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string name;
        private ProfileData data;

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

        public int FollowLineNextState
        {
            get { return data.followLineNextState; }
            set
            {
                if (value != data.followLineNextState)
                {
                    data.followLineNextState = value;
                    OnPropertyChanged("FollowLineNextState");
                }
            }
        }

        public int SearchLineNextState
        {
            get { return data.searchLineNextState; }
            set
            {
                if (value != data.searchLineNextState)
                {
                    data.searchLineNextState = value;
                    OnPropertyChanged("SearchLineNextState");
                }
            }
        }

        public int DeviationLeftNextState
        {
            get { return data.deviationLeftNextState; }
            set
            {
                if (value != data.deviationLeftNextState)
                {
                    data.deviationLeftNextState = value;
                    OnPropertyChanged("DeviationLeftNextState");
                }
            }
        }

        public float DeviationLeftAngle
        {
            get { return data.deviationLeftAngle; }
            set
            {
                if (value != data.deviationLeftAngle)
                {
                    data.deviationLeftAngle = value;
                    OnPropertyChanged("DeviationLeftAngle");
                }
            }
        }

        public int DeviationRightNextState
        {
            get { return data.deviationRightNextState; }
            set
            {
                if (value != data.deviationRightNextState)
                {
                    data.deviationRightNextState = value;
                    OnPropertyChanged("DeviationRightNextState");
                }
            }
        }

        public float DeviationRightAngle
        {
            get { return data.deviationRightAngle; }
            set
            {
                if (value != data.deviationRightAngle)
                {
                    data.deviationRightAngle = value;
                    OnPropertyChanged("DeviationRightAngle");
                }
            }
        }

        public int AvoidLeftNextState
        {
            get { return data.avoidLeftNextState; }
            set
            {
                if (value != data.avoidLeftNextState)
                {
                    data.avoidLeftNextState = value;
                    OnPropertyChanged("AvoidLeftNextState");
                }
            }
        }

        public float AvoidLeftAngle
        {
            get { return data.avoidLeftAngle; }
            set
            {
                if (value != data.avoidLeftAngle)
                {
                    data.avoidLeftAngle = value;
                    OnPropertyChanged("AvoidLeftAngle");
                }
            }
        }

        public double AvoidLeftTime
        {
            get { return data.avoidLeftTime; }
            set
            {
                if (value != data.avoidLeftTime)
                {
                    data.avoidLeftTime = value;
                    OnPropertyChanged("AvoidLeftTime");
                }
            }
        }

        public int AvoidRightNextState
        {
            get { return data.avoidRightNextState; }
            set
            {
                if (value != data.avoidRightNextState)
                {
                    data.avoidRightNextState = value;
                    OnPropertyChanged("AvoidRightNextState");
                }
            }
        }

        public float AvoidRightAngle
        {
            get { return data.avoidRightAngle; }
            set
            {
                if (value != data.avoidRightAngle)
                {
                    data.avoidRightAngle = value;
                    OnPropertyChanged("AvoidRightAngle");
                }
            }
        }

        public double AvoidRightTime
        {
            get { return data.avoidRightTime; }
            set
            {
                if (value != data.avoidRightTime)
                {
                    data.avoidRightTime = value;
                    OnPropertyChanged("AvoidRightTime");
                }
            }
        }

        public int LeftSensorDangerState
        {
            get { return data.leftSensorDangerState; }
            set
            {
                if (value != data.leftSensorDangerState)
                {
                    data.leftSensorDangerState = value;
                    OnPropertyChanged("LeftSensorDangerState");
                }
            }
        }

        public int LeftSensorSafeState
        {
            get { return data.leftSensorSafeState; }
            set
            {
                if (value != data.leftSensorSafeState)
                {
                    data.leftSensorSafeState = value;
                    OnPropertyChanged("LeftSensorSafeState");
                }
            }
        }

        public int CenterSensorDangerState
        {
            get { return data.centerSensorDangerState; }
            set
            {
                if (value != data.centerSensorDangerState)
                {
                    data.centerSensorDangerState = value;
                    OnPropertyChanged("CenterSensorDangerState");
                }
            }
        }

        public int CenterSensorSafeState
        {
            get { return data.centerSensorSafeState; }
            set
            {
                if (value != data.centerSensorSafeState)
                {
                    data.centerSensorSafeState = value;
                    OnPropertyChanged("CenterSensorSafeState");
                }
            }
        }

        public int RightSensorDangerState
        {
            get { return data.rightSensorDangerState; }
            set
            {
                if (value != data.rightSensorDangerState)
                {
                    data.rightSensorDangerState = value;
                    OnPropertyChanged("RightSensorDangerState");
                }
            }
        }

        public int RightSensorSafeState
        {
            get { return data.rightSensorSafeState; }
            set
            {
                if (value != data.rightSensorSafeState)
                {
                    data.rightSensorSafeState = value;
                    OnPropertyChanged("RightSensorSafeState");
                }
            }
        }

        public bool LeftDistanceSensor
        {
            get { return data.leftDistanceSensor == 1; }
            set
            {
                if (value != (data.leftDistanceSensor == 1))
                {
                    data.leftDistanceSensor = value ? 1 : 0;
                    OnPropertyChanged("LeftDistanceSensor");
                }
            }
        }

        public bool RightDistanceSensor
        {
            get { return data.rightDistanceSensor == 1; }
            set
            {
                if (value != (data.rightDistanceSensor == 1))
                {
                    data.rightDistanceSensor = value ? 1 : 0;
                    OnPropertyChanged("RightDistanceSensor");
                }
            }
        }

        public bool CenterDistanceSensor
        {
            get { return data.centerDistanceSensor == 1; }
            set
            {
                if (value != (data.centerDistanceSensor == 1))
                {
                    data.centerDistanceSensor = value ? 1 : 0;
                    OnPropertyChanged("CenterDistanceSensor");
                }
            }
        }

        public bool CapteurLigne
        {
            get { return data.capteurLigne == 1; }
            set
            {
                if (value != (data.capteurLigne == 1))
                {
                    data.capteurLigne = value ? 1 : 0;
                    OnPropertyChanged("CapteurLigne");
                }
            }
        }
    }

}
