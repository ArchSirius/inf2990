using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique.Tools
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ZoomRectangle
    /// @brief Représente l'outil de zoom avec rectangle élastique
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class ZoomRectangle : Tool
    {
        public ZoomRectangle(ToolContext context) : base(context) { }

        public override void LeftMousePressed(MouseEventArgs e)
        {
            FonctionsNatives.preparerRectangleElastique();
        }
        public override void LeftMouseReleased(MouseEventArgs e)
        {  
            FonctionsNatives.terminerRectangleElastique();
            if (Control.ModifierKeys == Keys.Alt)
                FonctionsNatives.zoomOutRectangle();
                
            else
                FonctionsNatives.zoomInRectangle();
                
        }
        public override void Dragging(int deltaX, int deltaY, int deltaZ)
        {
            if (!EditorController.dragEnter)
                FonctionsNatives.initialiserRectangleElastique();
            else
                FonctionsNatives.mettreAJourRectangleElastique();
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void preparerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void mettreAJourRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void terminerRectangleElastique();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomOutRectangle();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void zoomInRectangle();
            
        }



    }
}
