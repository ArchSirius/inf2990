//////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.h
/// @author INF2990-A15-01
/// @date 2015-11-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspective.h"

namespace vue {


    ////////////////////////////////////////////////////////////////////////
    /// @class VueOrbite
    /// @brief Classe concr�te de vue orbite.
    ///
    /// Cette classe implante le comportement attendu d'une vue orbite.
    ///
    /// @author Martin Bisson
    /// @date 2006-12-16
    ////////////////////////////////////////////////////////////////////////
    class VueOrbite : public Vue
    {
    public:
        // Constructeur.
        VueOrbite(Camera const& camera, ProjectionPerspective const& projection);

        /// Obtention de la projection.
        virtual const ProjectionPerspective& obtenirProjection() const;
        /// Application de la projection.
        virtual void appliquerProjection() const;
        /// Application de la cam�ra.
        virtual void appliquerCamera() const;

        /// Modification de la clot�re.
        virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
            const glm::ivec2& coinMax);

        /// Zoom in, c'est-�-dire un agrandissement.
        virtual void zoomerIn();
        /// Zoom out, c'est-�-dire un rapetissement.
        virtual void zoomerOut();

        /// D�placement dans le plan XY par rapport � la vue.
        virtual void deplacerXY(double deplacementX, double deplacementY);
        /// D�placement dans le plan XY par rapport � la vue.
        virtual void deplacerXY(const glm::ivec2& deplacement);
        /// D�placement selon l'axe des Z par rapport � la vue.
        virtual void deplacerZ(double deplacement);
        /// Rotation selon les axes des X et des Y par rapport � la vue.
        virtual void rotaterXY(double rotationX, double rotationY);
        /// Rotation selon les axes des X et des Y par rapport � la vue.
        virtual void rotaterXY(const glm::ivec2& rotation);
        /// Rotation selon l'axe des Z par rapport � la vue.
        virtual void rotaterZ(double rotation);


    private:
        /// Projection utilis�e pour cette vue.
        ProjectionPerspective projection_;
    };


}; // Fin de l'espace de nom vue.

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
