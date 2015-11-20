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
    /// @author INF2990-A15-01
    /// @date 2015-11-16
    ////////////////////////////////////////////////////////////////////////
    class VueOrbite : public Vue
    {
    public:
        // Constructeur.
        VueOrbite(Camera const& camera, ProjectionPerspective const& projection);

        /// Obtention de la projection.
        const ProjectionPerspective& obtenirProjection() const override;
        /// Application de la projection.
        void appliquerProjection() const override;
        /// Application de la caméra.
        void appliquerCamera() const override;

        /// Modification de la clotûre.
        void redimensionnerFenetre(const glm::ivec2& coinMin,
            const glm::ivec2& coinMax) override;

        /// Zoom in, c'est-à-dire un agrandissement.
        void zoomerIn() override;
        /// Zoom out, c'est-à-dire un rapetissement.
        void zoomerOut() override;

		/// Zoom in élastique
		void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) override {}
		/// Zoom out élastique
		void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) override {}

        /// Déplacement dans le plan XY par rapport à la vue.
        void deplacerXY(double deplacementX, double deplacementY) override;
        /// Déplacement dans le plan XY par rapport à la vue.
		void deplacerXY(const glm::ivec2& deplacement) override;
        /// Déplacement à l'aide de la souris
        void deplacerSouris(glm::dvec3 delta) override;
        /// Déplacement selon l'axe des Z par rapport à la vue.
		void deplacerZ(double deplacement) override;
        /// Rotation selon les axes des X et des Y par rapport à la vue.
		void rotaterXY(double rotationX, double rotationY) override;
        /// Rotation selon les axes des X et des Y par rapport à la vue.
		void rotaterXY(const glm::ivec2& rotation) override;
        /// Rotation selon l'axe des Z par rapport à la vue.
		void rotaterZ(double rotation) override;


    private:
        /// Projection utilisée pour cette vue.
        ProjectionPerspective projection_;
    };

    ////////////////////////////////////////////////////////////////////////
    /// @class SphericCoords
    /// @brief Struct de coordonnées sphériques
    ///
    /// Cette struct représente les coordonnées sphériques d'un objet
    ///
    /// @author INF2990-A15-01
    /// @date 2015-11-16
    ////////////////////////////////////////////////////////////////////////
    struct SphericCoords {

        SphericCoords(double rho, double phi, double theta) 
        : Rho(std::move(rho)), Phi(std::move(phi)), Theta(std::move(theta)) {}

        SphericCoords(glm::dvec3 xyz) {
            Rho = sqrt(xyz.z*xyz.z + xyz.x*xyz.x + xyz.y*xyz.y);
            Phi = acos(xyz.y / Rho);
            Theta = atan2(xyz.x, xyz.z);
        }

        double Rho;     // sqrt(x*x + y*y + z*z)
        double Phi;     // acos(y / Rho)
        double Theta;   // atan2(x / z)
    };

}; // Fin de l'espace de nom vue.

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
