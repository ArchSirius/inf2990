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
        private string savePath;

        public ConfigPanelData()
        {
            var exePath = System.Reflection.Assembly.GetEntryAssembly().Location;
            savePath = exePath.Substring(0, exePath.Length - 22) + "config.json";
        }

        public void Save(List<Profil> profiles)
        {
            var output = JsonConvert.SerializeObject(profiles.Skip(1).ToList<Profil>());

            File.WriteAllText(savePath, output);
        }

        public List<Profil> Load()
        {
            var list = new List<Profil>();

            // Default profile
            list.Add(new Profil()
            {
                Name = "Default",
                FollowLineNextState = 0
            });

            if (File.Exists(savePath))
            {
                list.AddRange(JsonConvert.DeserializeObject<List<Profil>>(File.ReadAllText(savePath)));
            }

            return list;
        }
    }
}
