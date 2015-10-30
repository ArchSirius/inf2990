using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class ConfigPanelController
    {
       
        public void save()
        {
            JObject o = JObject.FromObject(new
            {

                KeyBinding = new
                {
                    Avancer = "Avancer",
                    Reculer = "Reculer",
                    RotationAntiHoraire = "RetAntiH",
                    RotationHoraire = "RetH",
                }

             });
            var test = o.ToString();
            // pour l'affichage a la console
            Console.WriteLine(o.ToString());


            // http://stackoverflow.com/questions/15206953/saving-a-json-file-in-a-text-file

            // pour l'ouverture de fichier

            FileStream fs = File.Open(@"X:\Documents\config.txt", FileMode.CreateNew);
            StringBuilder sb = new StringBuilder();
            JsonWriter writer = new JsonTextWriter(new StringWriter(sb));

            string path = @"X:\Documents\config.txt";

            writer.Formatting = Formatting.Indented;

            File.WriteAllText(path, "Salut");

      
        }

        public void load()
        {
           // JObject o1 = JObject.Parse(File.ReadAllText(@"c:\videogames.json");
            StreamReader file = File.OpenText(@"config.txt");
            JsonTextReader reader = new JsonTextReader(file);

        }
    }
}
