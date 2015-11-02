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
    class ConfigPanelController
    {

        struct SuivisLigne
        {
        public string EtatSuivant { get; set; }
        }
        struct Balayage180Deg
        {
            public string EtatSuivant { get; set; }
        }
        struct DeviationGauche
        {
            public string EtatSuivant { get; set; }
            public string AngleDeviation { get; set; }
        }
        struct DeviationDroite
        {
            public string EtatSuivant { get; set; }
            public string AngleDeviation { get; set; }
        }
        struct EvitementGauche
        {
            public string AngleRotation { get; set; }
            public string TempsReculer { get; set; }
            public string EtatSuivant { get; set; }
        }
        struct EvitementDroite
        {
            public string AngleDeviation { get; set; }
            public string TempsReculer { get; set; }
            public string EtatSuivant { get; set; }
        }

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
                },
                Comportement = new
                {
                    SuivisDeLigne = new
                    {
                        EtatSuivant = " Teste ",
                    },

                    Balayage180Deg = new
                    {
                        EtatSuivant = " Teste ",
                    },

                    DeviationGauche = new
                    {
                        AngleDeviation = " Teste ",
                        EtatSuivant = " Teste ",
                    },

                    DeviationDroite = new
                    {
                        AngleDeviation = "Teste",
                        EtatSuivant = "Teste ",
                    },
                    EvitementGauche = new
                    {
                        AngleRotation = "Teste",
                        TempsReculer = "Teste",
                        EtatSuivant = " Teste ",
                    },
                    EvitementDroite = new
                    {
                        AngleRotation = "Teste",
                        TempsReculer = "Teste",
                        EtatSuivant = "Teste ",
                    },
                },
                Capteurs = new
                {
                    EtatSuivant = "Teste ",
                },

             });

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
        private void KeyboardDefault_Click(object sender, RoutedEventArgs e)
        {
            save();
        }

    }
}
