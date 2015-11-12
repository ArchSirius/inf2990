using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace InterfaceGraphique
{
    class ConfigPanelData
    {
        private string profilesPath;
        private string keyBindingPath;
        private string settingsPath;

        public ConfigPanelData()
        {
            var exePath = System.Reflection.Assembly.GetEntryAssembly().Location;
            profilesPath = exePath.Substring(0, exePath.Length - 22) + "Données/profiles.json";
            keyBindingPath = exePath.Substring(0, exePath.Length - 22) + "Données/keybindings.json";
            settingsPath = exePath.Substring(0, exePath.Length - 22) + "Données/settings.json";
        }

        public Settings LoadSettings()
        {
            return Load<Settings>(settingsPath);
        }

        public void SaveSettings(Settings settings)
        {
            Save(settings, settingsPath);
        }

        public KeyBindings LoadKeybindings()
        {
            return Load<KeyBindings>(keyBindingPath);
        }

        public void SaveKeybindings(KeyBindings keys)
        {
            Save(keys, keyBindingPath);
        }

        public void SaveProfiles(List<Profil> profiles)
        {
            // Remove default profile
            Save(profiles.Skip(1).ToList<Profil>(), profilesPath);
        }

        public List<Profil> LoadProfiles()
        {
            var list = new List<Profil>();

            // Default profile
            list.Add(new Profil()
            {
                Name = "Default",
                FollowLineNextState = 0,
                SearchLineNextState = 0,

                LeftDistanceSensor = true,
                RightDistanceSensor = true,
                CenterDistanceSensor = true,
                CapteurLigne = true,

                DeviationLeftNextState = 0,
                DeviationLeftAngle = 20,

                DeviationRightNextState = 0,
                DeviationRightAngle = 21,

                AvoidLeftNextState = 0,
                AvoidLeftAngle = 45,
                AvoidLeftTime = 2,

                AvoidRightNextState = 0,
                AvoidRightAngle = 45,
                AvoidRightTime = 1.0,

                CenterSensorDangerLenght = 2,
                CenterSensorDangerState = 6,
                CenterSensorSafeLenght = 3,
                CenterSensorSafeState = 3,

                LeftSensorDangerLenght = 1.5,
                LeftSensorDangerState = 6,
                LeftSensorSafeLenght = 2,
                LeftSensorSafeState = 4,

                RightSensorDangerLenght = 1.5,
                RightSensorDangerState = 5,
                RightSensorSafeLenght = 2,
                RightSensorSafeState = 3,



            });

            list.AddRange(Load<List<Profil>>(profilesPath));

            return list;
        }

        private void Save<T>(T data, string file)
        {
            File.WriteAllText(file, JsonConvert.SerializeObject(data));
        }

        private T Load<T>(string file) where T : new()
        {
            T data = new T();

            if (File.Exists(file))
            {
                var fileData = JsonConvert.DeserializeObject<T>(File.ReadAllText(file));
                if (fileData != null)
                {
                    data = fileData;
                }
            }

            return data;
        }
    }
}
