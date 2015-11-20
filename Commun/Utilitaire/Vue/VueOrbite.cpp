////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.cpp
/// @author INF2990-A15-01
/// @date 2015-11-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VueOrbite.h"
#include <iostream>
#include <algorithm>


namespace vue {


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn VueOrbite::VueOrbite(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
    ///
    /// Constructeur d'une vue orbite.  Ne fait que créer les objets
    /// Projection et Camera correspondant.
    ///
    /// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
    /// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
    /// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
    /// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
    /// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
    /// @param[in] zAvant        : distance du plan avant (en @a z).
    /// @param[in] zArriere      : distance du plan arrière (en @a z).
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
    VueOrbite::VueOrbite(Camera const& camera, ProjectionPerspective const& projection) :
        Vue{ camera },
        projection_{ projection }
    {
		camera_.setIsPolar(true);
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn const ProjectionPerspective& VueOrbite::obtenirProjection() const
    ///
    /// Retourne la projection en perspective associée à cette vue.
    ///
    /// @return La projection perspective associée à cette vue.
    ///
    ////////////////////////////////////////////////////////////////////////
    const ProjectionPerspective& VueOrbite::obtenirProjection() const
    {
        return projection_;
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::appliquerProjection() const
    ///
    /// Applique la matrice de projection correspondant à cette vue.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::appliquerProjection() const
    {
        projection_.mettreAJourProjection();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::appliquerCamera() const
    ///
    /// Applique la matrice correspondant à cette vue selon la position de
    /// la caméra (eventuellement un gluLookAt()).
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::appliquerCamera()
	{
        camera_.positionner();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
    ///
    /// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
    /// d'un redimensionnement de la fenêtre.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
    ///                       nouvelle clôture.
    /// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
    ///                       nouvelle clôture.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::redimensionnerFenetre(const glm::ivec2& coinMin,
        const glm::ivec2& coinMax)
    {
        projection_.redimensionnerFenetre(coinMin, coinMax);
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::zoomerIn()
    ///
    /// Permet de faire un zoom in selon l'incrément de zoom.
    /// 
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::zoomerIn()
    {
        projection_.zoomerIn();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::zoomerOut()
    ///
    /// Permet de faire un zoom out selon l'incrément de zoom.
    /// 
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::zoomerOut()
    {
        projection_.zoomerOut();
    }  

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
    ///
    /// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
    /// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
    ///
    /// Permet de faire un "pan" d'un certain pourcentage.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
    {   
		camera_.deplacerXY(deplacementX * 100.0, deplacementY * 100.0);
		appliquerCamera();
	}


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
    ///
    /// Permet de faire un "pan" équivalent à la distance du déplacement
    /// spécifié en coordonnées de clôture.
    ///
    /// @param[in]  deplacement : Déplacement en coordonnées de clôture
    ///                           (pixels).
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
	{
		camera_.deplacerXY(deplacement.x * 100.0, deplacement.y * 100.0);
		appliquerCamera();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerSouris(glm::dvec3 delta)
    ///
    /// Cette fonction permet de changer la position de la vue (avec caméra)
    ///
    /// @param[] aucun
    ///
    /// @return Aucun
    ///
    ///////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerSouris(glm::dvec3 delta)
    {
		camera_.deplacerXY(delta.x / 100.0, delta.y / 100.0);
		appliquerCamera();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerZ(double deplacement)
    ///
    /// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
    /// vraiment de signification avec une vue orthogonale.
    ///
    /// @param[in]  deplacement : Déplacement selon l'axe Z.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerZ(double deplacement)
    {
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::rotaterXY(double rotationX, double rotationY)
    ///
    /// Permet de faire une rotation de la caméra autour du point vers
    /// lequel elle regarde en modifiant l'angle de rotation et l'angle
    /// d'élévation.
    ///
    /// Une rotation de 100% correspondant à 360 degrés en X (angle de
    /// rotation) ou 180 degrés en Y (angle d'élévation).
    ///
    /// @param[in]  rotationX : Rotation en pourcentage de la largeur.
    /// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::rotaterXY(double rotationX, double rotationY)
    {
        camera_.tournerXY(rotationX /** 360*/, rotationY /** 180*/);
        camera_.positionner();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::rotaterXY(const glm::ivec2& rotation)
    ///
    /// Permet de faire une rotation de la caméra autour du point vers
    /// lequel elle regarde en modifiant l'angle de rotation et l'angle
    /// d'élévation.
    ///
    /// Un déplacement de la taille de la fenêtre correspond à 100%.
    ///
    /// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::rotaterXY(const glm::ivec2& rotation)
    {
        const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
        rotaterXY(rotation[0] / (double)dimensions[0],
            rotation[1] / (double)dimensions[1]);
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::rotaterZ(double rotation)
    ///
    /// Ne fait rien, car tourner autour de l'axe de la profondeur
    /// correspondrait à un rouli et n'est pas souhaitable pour cette vue.
    ///
    /// @param[in]  rotation : Rotation selon l'axe Z.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::rotaterZ(double rotation)
    {
    }


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
