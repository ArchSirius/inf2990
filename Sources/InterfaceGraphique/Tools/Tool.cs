using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique.Tools
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Tool
    /// @brief Classe abstraite qui représente un outil comme la sélection
    ///        ou le déplacement.
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    abstract class Tool
    {
        private ToolContext context;

        public Tool(ToolContext c)
        {
            context = c;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::LeftMousePressed()
        ///
        /// Appelé quand on appuis sur le bouton gauche de la souris
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void LeftMousePressed(MouseEventArgs e)
        {

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::LeftMouseReleased()
        ///
        /// Appelé quand on relâche sur le bouton gauche de la souris
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void LeftMouseReleased(MouseEventArgs e)
        {
            
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::LeftMouseFullClicked()
        ///
        /// Appelé quand on appuis et relâche sur le bouton gauche de la souris
        /// à l'intérieur de trois pixels. Représente un click.
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void LeftMouseFullClicked(MouseEventArgs e)
        {

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::Dragging()
        ///
        /// Appelé dès qu'on bouge des éléments
        /// 
        /// @param[in] deltaX : la distance en X
        /// @param[in] deltaY : la distance en Y
        /// @param[in] deltaZ : la distance en Z
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void Dragging(int deltaX, int deltaY, int deltaZ)
        {

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::MouseMove()
        ///
        /// Appelé quand on bouge la souris
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void MouseMove(MouseEventArgs e)
        {

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Tool::esc()
        ///
        /// Appelé quand on fait escape
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void esc()
        {
            
        }
    }
}
