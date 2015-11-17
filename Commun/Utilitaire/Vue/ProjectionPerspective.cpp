////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspective.cpp
/// @author INF2990-A15-01
/// @date 2015-11-13
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionPerspective.h"
#include <iostream>

namespace vue {

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn ProjectionPerspective::ProjectionPerspective(
    ///     int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, 
    ///     double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, 
    ///     double incrementZoom, double xMinFenetre, double xMaxFenetre, 
    ///     double yMinFenetre, double yMaxFenetre)
    ///
    /// Constructeur d'une projection en perspective. Ne fait qu'assigner les
    /// variables membres et ajuste ensuite le rapport d'aspect.
    ///
    /// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture. (left)
    /// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture. (right)
    /// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture. (bottom)
    /// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture. (top)
    /// @param[in] zAvant        : distance du plan avant (en @a z).          (near)
    /// @param[in] zArriere      : distance du plan arri�re (en @a z).        (far)
    /// @param[in] zoomInMax     : facteur de zoom in maximal.
    /// @param[in] zoomOutMax    : facteur de zoom out maximal.
    /// @param[in] incrementZoom : distance du plan arri�re (en @a z).
    /// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
    ///                            virtuelle.
    /// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
    ///                            virtuelle.
    /// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
    ///                            virtuelle.
    /// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
    ///                            virtuelle.
    /// 
    /// @return Aucune (constructeur).
    ///
    ////////////////////////////////////////////////////////////////////////
    ProjectionPerspective::ProjectionPerspective(
        int xMinCloture, int xMaxCloture,
        int yMinCloture, int yMaxCloture,
        double zAvant, double zArriere,
        double zoomInMax, double zoomOutMax,
        double incrementZoom,
        double xMinFenetre, double xMaxFenetre,
        double yMinFenetre, double yMaxFenetre) :
        Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
        zAvant, zArriere,
        zoomInMax, zoomOutMax, incrementZoom, false }
    {
        xMinFenetre_ = xMinFenetre;
        xMaxFenetre_ = xMaxFenetre;
        yMinFenetre_ = yMinFenetre;
        yMaxFenetre_ = yMaxFenetre;
        zoom_ = 0.1;
        ajusterRapportAspect();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::zoomerIn()
    ///
    /// Permet de faire un zoom in selon l'incr�ment de zoom.
    /// 
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void ProjectionPerspective::zoomerIn()
    {
        Projection::zoomerIn();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::zoomerOut()
    ///
    /// Permet de faire un zoom out selon l'incr�ment de zoom.
    ///
    /// @return Aucune.
    ///
    //////////////////////////////////////////////////////////////////////// 
    void ProjectionPerspective::zoomerOut()
    {
        Projection::zoomerOut();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
    ///
    /// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
    /// d'un redimensionnement de la fen�tre.
    ///
    /// L'agrandissement de la fen�tre virtuelle est proportionnel �
    /// l'agrandissement de la clot�re afin que les objets gardent la m�me
    /// grandeur apparente lorsque la fen�tre est redimensionn�e.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
    ///                       nouvelle cl�ture
    /// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
    ///                       nouvelle cl�ture
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void ProjectionPerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
        const glm::ivec2& coinMax)
    {
        Projection::redimensionnerFenetre(coinMin, coinMax);
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::appliquer() const
    ///
    /// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
    /// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
    /// fen�tre.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void ProjectionPerspective::appliquer() const
    {
        gluPerspective(25.0 + 100 * (zoom_), (xMaxFenetre_ - xMinFenetre_) / (yMaxFenetre_ - yMinFenetre_), 0.1, 1000.0);
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::ajusterRapportAspect()
    ///
    /// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
    /// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void ProjectionPerspective::ajusterRapportAspect()
    {
        Projection::ajusterRapportAspect();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void ProjectionPerspective::getZoom()
    ///
    /// Permet d'obtenir le niveau du zoom.
    ///
    /// @return double zoom.
    ///
    ////////////////////////////////////////////////////////////////////////
    double ProjectionPerspective::getZoom() const
    {
        return Projection::getZoom();
    }

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////

