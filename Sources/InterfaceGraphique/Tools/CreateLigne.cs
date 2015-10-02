using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique.Tools
{
    class CreateLigne : Tool
    {
        public const string nodeType = "ligne";
        private ToolContext _context;
        private bool _ghostStarted;
        private bool _validPos;

        public CreateLigne(ToolContext context)
            : base(context)
        {
            _context = context;
            _ghostStarted = false;
           
            _validPos = true;
        }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            
        }

        public override void LeftMouseReleased(MouseEventArgs e)
        {
        }

        public override void LeftMouseFullClicked(MouseEventArgs e)
        {
            _ghostStarted = true;
            /// Premier clic
            /// Vérifier position
            /// si position valide
            /// 
            while (_ghostStarted)
            {
                 FonctionsNatives.addNode(nodeType);
                 //FonctionsNatives.afficherFantome();
                //_context.resetState();
            } 
            
            /// TODO Créer ligne fantôme

            /// Si CTRL enfoncé
            /// TODO Vérifier position
            /// Actualiser ligne fantôme
            /// TODO Créer ligne fantôme

            /// Si CTRL relâché
            /// TODO Vérifier position; si valide, créer vraie ligne
            _ghostStarted = false;

            // Après le dernier clic
            _context.resetState();


        }

        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
        }

        public override void MouseMove(MouseEventArgs e)
        {
            /// TODO Actualiser la ligne fantôme
            /// TODO Vérifier position
           
            if (FonctionsNatives.isMouseOnTable())
            {
                _validPos = true;
                Cursor.Current = Cursors.Default;
            }
            else
            {
                _validPos = false;
                Cursor.Current = Cursors.No;
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void addNode(string type);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool isMouseOnTable();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void afficherFantome();
        }

    }
}