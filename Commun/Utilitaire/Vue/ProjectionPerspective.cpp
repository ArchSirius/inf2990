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
    /// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture. (left)
    /// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture. (right)
    /// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture. (bottom)
    /// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture. (top)
    /// @param[in] zAvant        : distance du plan avant (en @a z).          (near)
    /// @param[in] zArriere      : distance du plan arrière (en @a z).        (far)
    /// @param[in] zoomInMax     : facteur de zoom in maximal.
    /// @param[in] zoomOutMax    : facteur de zoom out maximal.
    /// @param[in] incrementZoom : distance du plan arrière (en @a z).
    /// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
    ///                            virtuelle.
    /// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
    ///                            virtuelle.
    /// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
    ///                            virtuelle.
    /// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
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
    /// Permet de faire un zoom in selon l'incrément de zoom.
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
    /// Permet de faire un zoom out selon l'incrément de zoom.
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
    /// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
    /// d'un redimensionnement de la fenêtre.
    ///
    /// L'agrandissement de la fenêtre virtuelle est proportionnel à
    /// l'agrandissement de la clotûre afin que les objets gardent la même
    /// grandeur apparente lorsque la fenêtre est redimensionnée.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
    ///                       nouvelle clôture
    /// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
    ///                       nouvelle clôture
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
    /// Cette fonction permet d'appliquer la fenêtre virtuelle en appelant les
    /// fonctions d'OpenGL selon le type de projection et les propriétés de la
    /// fenêtre.
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
    /// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
    /// de la clôture de façon à ce que le rapport d'aspect soit respecté.
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

