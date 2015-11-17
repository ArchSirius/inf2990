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
        const ProjectionPerspective& obtenirProjection() const override;
        /// Application de la projection.
        void appliquerProjection() const override;
        /// Application de la cam�ra.
        void appliquerCamera() const override;

        /// Modification de la clot�re.
        void redimensionnerFenetre(const glm::ivec2& coinMin,
            const glm::ivec2& coinMax) override;

        /// Zoom in, c'est-�-dire un agrandissement.
        void zoomerIn() override;
        /// Zoom out, c'est-�-dire un rapetissement.
        void zoomerOut() override;

		/// Zoom in �lastique
		void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) override {}
		/// Zoom out �lastique
		void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) override {}

        /// D�placement dans le plan XY par rapport � la vue.
        void deplacerXY(double deplacementX, double deplacementY) override;
        /// D�placement dans le plan XY par rapport � la vue.
		void deplacerXY(const glm::ivec2& deplacement) override;
        /// D�placement selon l'axe des Z par rapport � la vue.
		void deplacerZ(double deplacement) override;
        /// Rotation selon les axes des X et des Y par rapport � la vue.
		void rotaterXY(double rotationX, double rotationY) override;
        /// Rotation selon les axes des X et des Y par rapport � la vue.
		void rotaterXY(const glm::ivec2& rotation) override;
        /// Rotation selon l'axe des Z par rapport � la vue.
		void rotaterZ(double rotation) override;


    private:
        /// Projection utilis�e pour cette vue.
        ProjectionPerspective projection_;
    };


}; // Fin de l'espace de nom vue.

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
