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
    public struct ProfileData
    {
        public int followLineNextState;

        public int searchLineNextState;

        public int deviationLeftNextState;
        public float deviationLeftAngle;

        public int deviationRightNextState;
        public float deviationRightAngle;

        public int avoidLeftNextState;
        public float avoidLeftAngle;
        public double avoidLeftTime;

        public int avoidRightNextState;
        public float avoidRightAngle;
        public double avoidRightTime;

        public int leftDistanceSensor;
        public int rightDistanceSensor;
        public int centerDistanceSensor;
        public int leftSensorDangerState;
        public int LeftSensorSafeState;
        public int rightSensorDangerState;
        public int rightSensorSafeState;
        public int centerSensorDangerState;
        public int centerSensorSafeState;

        public double leftSensorSafeLenght;
        public double leftSensorDangerLenght;
        public double rightSensorSafeLenght;
        public double rightSensorDangerLenght;
        public double centerSensorSafeLenght;
        public double centerSensorDangerLenght;

        public int capteurLigne;
        public String profileName;

    }

    public class Profil : INotifyPropertyChanged, IComparable, IDataErrorInfo
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string name;
        private ProfileData data;
        private String id;
        private SortedList<String,String> erreurs_;

        public Profil()
        {
            id = Guid.NewGuid().ToString();
            erreurs_ = new SortedList<String,String>();
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

        public override string ToString()
        {
            return Name;
        }

        public ProfileData GetData()
        {
            return data;
        }

        public int CompareTo(object obj)
        {
            return ((Profil)obj).Id.CompareTo(id);
        }


        #region IDataErrorInfo Members
 
        public string Error
        {
            get
            {
                string result = "";

                foreach (var err in erreurs_)
                {
                    result += err.Value.Trim();
                }

                return result;
            }
        }
 
        public string this[string columnName]
        {
            get
            {
                if (erreurs_.ContainsKey(columnName) && erreurs_[columnName] != "")
                {
                    return erreurs_[columnName];
                }

                return null;
            }
        }

        #endregion

        public string Name
        {
            get { return name; }
            set
            {
                if (value != name)
                {
                    name = value;
                    data.profileName = value;
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
                    if (value < 0 || value > 360)
                    {
                        erreurs_["DeviationLeftAngle"] = "Angle DeviationLeftAngle invalide";
                    }
                    else
                    {
                        erreurs_["DeviationLeftAngle"] = "";
                    }

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
                    if (value < 0 || value > 360)
                    {
                        erreurs_["DeviationRightAngle"] = "Angle DeviationRightAngle invalide";
                    }
                    else
                    {
                        erreurs_["DeviationRightAngle"] = "";
                    }

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
                    if (value < 0 || value > 360)
                    {
                        erreurs_["AvoidLeftAngle"] = "Angle AvoidLeftAngle invalide";
                    }
                    else
                    {
                        erreurs_["AvoidLeftAngle"] = "";
                    }

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
                    if (value < 0 || value > 2000)
                    {
                        erreurs_["AvoidLeftTime"] = "Temps AvoidLeftTime invalide";
                    }
                    else
                    {
                        erreurs_["AvoidLeftTime"] = "";
                    }

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
                    if (value < 0 || value > 360)
                    {
                        erreurs_["AvoidRightAngle"] = "Angle AvoidRightAngle invalide";
                    }
                    else
                    {
                        erreurs_["AvoidRightAngle"] = "";
                    }

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
                    if (value < 0 || value > 2000)
                    {
                        erreurs_["AvoidRightTime"] = "Temps AvoidRightTime invalide";
                    }
                    else
                    {
                        erreurs_["AvoidRightTime"] = "";
                    }

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
            get { return data.LeftSensorSafeState; }
            set
            {
                if (value != data.LeftSensorSafeState)
                {
                    data.LeftSensorSafeState = value;
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

        public double LeftSensorSafeLenght
        {
            get { return data.leftSensorSafeLenght; }
            set
            {
                if (value != data.leftSensorSafeLenght)
                {
                    data.leftSensorSafeLenght = value;
                    OnPropertyChanged("LeftSensorSafeLenght");
                }
            }
        }

        public double LeftSensorDangerLenght
        {
            get { return data.leftSensorDangerLenght; }
            set
            {
                if (value != data.leftSensorDangerLenght)
                {
                    data.leftSensorDangerLenght = value;
                    OnPropertyChanged("LeftSensorDangerLenght");
                }
            }
        }

        public double RightSensorSafeLenght
        {
            get { return data.rightSensorSafeLenght; }
            set
            {
                if (value != data.rightSensorSafeLenght)
                {
                    data.rightSensorSafeLenght = value;
                    OnPropertyChanged("RightSensorSafeLenght");
                }
            }
        }

        public double RightSensorDangerLenght
        {
            get { return data.rightSensorDangerLenght; }
            set
            {
                if (value != data.rightSensorDangerLenght)
                {
                    data.rightSensorDangerLenght = value;
                    OnPropertyChanged("RightSensorDangerLenght");
                }
            }
        }

        public double CenterSensorSafeLenght
        {
            get { return data.centerSensorSafeLenght; }
            set
            {
                if (value != data.centerSensorSafeLenght)
                {
                    data.centerSensorSafeLenght = value;
                    OnPropertyChanged("CenterSensorSafeLenght");
                }
            }
        }

        public double CenterSensorDangerLenght
        {
            get { return data.centerSensorDangerLenght; }
            set
            {
                if (value != data.centerSensorDangerLenght)
                {
                    data.centerSensorDangerLenght = value;
                    OnPropertyChanged("CenterSensorDangerLenght");
                }
            }
        }


        public String Id
        {
            get { return id; }
            set { id = value; }
        }
    }

}
