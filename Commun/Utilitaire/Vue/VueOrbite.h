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
    /// @brief Classe concrète de vue orbite.
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
        /// Application de la caméra.
        virtual void appliquerCamera() const;

        /// Modification de la clotûre.
        virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
            const glm::ivec2& coinMax);

        /// Zoom in, c'est-à-dire un agrandissement.
        virtual void zoomerIn();
        /// Zoom out, c'est-à-dire un rapetissement.
        virtual void zoomerOut();

        /// Déplacement dans le plan XY par rapport à la vue.
        virtual void deplacerXY(double deplacementX, double deplacementY);
        /// Déplacement dans le plan XY par rapport à la vue.
        virtual void deplacerXY(const glm::ivec2& deplacement);
        /// Déplacement selon l'axe des Z par rapport à la vue.
        virtual void deplacerZ(double deplacement);
        /// Rotation selon les axes des X et des Y par rapport à la vue.
        virtual void rotaterXY(double rotationX, double rotationY);
        /// Rotation selon les axes des X et des Y par rapport à la vue.
        virtual void rotaterXY(const glm::ivec2& rotation);
        /// Rotation selon l'axe des Z par rapport à la vue.
        virtual void rotaterZ(double rotation);


    private:
        /// Projection utilisée pour cette vue.
        ProjectionPerspective projection_;
    };


}; // Fin de l'espace de nom vue.

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
