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
    /// @class ToolContext
    /// @brief Classe qui implémente les Tools comme étant des états.
    /// 
    ///        Cette classe contient les informations sur les états actifs
    ///
    /// @author INF2990-A15-01
    /// @date 2015-10-01
    ///////////////////////////////////////////////////////////////////////////
    class ToolContext
    {
        protected Tool activeTool;
        protected Tool defaultTool;
        protected Engine engine;
        int origX = 0;
        int origY = 0;

        public ToolContext(Tool tool, Engine _engine)
        {
            defaultTool = tool;
            engine = _engine;
            resetState();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::ChangeState()
        ///
        /// Permet de changer l'outil sélectionné
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void ChangeState(Tool tool)
        {
            if (activeTool != null)
                activeTool.esc();
            activeTool = tool;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::resetState()
        ///
        /// Remet l'outil par défaut
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void resetState()
        {
            ChangeState(defaultTool);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::LeftMousePressed()
        ///
        /// Fait suivre l'événement LeftMousePressed
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void LeftMousePressed(MouseEventArgs e)
        {
            if (activeTool != null)
                activeTool.LeftMousePressed(e);
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::LeftMouseReleased()
        ///
        /// Fait suivre l'événement LeftMouseReleased
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void LeftMouseReleased(MouseEventArgs e)
        {
            if (activeTool != null)
                activeTool.LeftMouseReleased(e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::LeftMouseFullClicked()
        ///
        /// Fait suivre l'événement LeftMouseFullClicked
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual void LeftMouseFullClicked(MouseEventArgs e)
        {
            if (activeTool != null)
                activeTool.LeftMouseFullClicked(e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::RightMouseClicked()
        ///
        /// Fait suivre l'événement RightMouseClicked
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RightMouseClicked(MouseEventArgs e)
        {
            engine.saveMousePos();
            origX = System.Windows.Forms.Control.MousePosition.X;
            origY = System.Windows.Forms.Control.MousePosition.Y;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::Dragging()
        ///
        /// Fait suivre l'événement Dragging
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Dragging(int deltaX, int deltaY, int deltaZ, bool clicIsLeft)
        {
            if (clicIsLeft)
            {
                if (activeTool != null)
                    activeTool.Dragging(deltaX, deltaY, deltaZ);
            }
            else
            {
                engine.moveCameraMouse(System.Windows.Forms.Control.MousePosition.X - origX, System.Windows.Forms.Control.MousePosition.Y - origY);
                origX = System.Windows.Forms.Control.MousePosition.X;
                origY = System.Windows.Forms.Control.MousePosition.Y;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::MouseMove()
        ///
        /// Fait suivre l'événement MouseMove
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MouseMove(MouseEventArgs e)
        {
            if (activeTool != null)
                activeTool.MouseMove(e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToolContext::esc()
        ///
        /// Fait suivre l'événement esc
        /// 
        /// @param[in] e : les informations sur l'événement
        /// 
        /// @return Aucun
        ///
        ////////////////////////////////////////////////////////////////////////
        public void esc()
        {
            if (activeTool != null)
                activeTool.esc();
        }
    }
}
