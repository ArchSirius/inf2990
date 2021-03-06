////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspective.h
/// @author INF2990-A15-01
/// @date 2015-11-13
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Projection.h"

namespace vue {


    ////////////////////////////////////////////////////////////////////////
    /// @class ProjectionPerspective
    /// @brief Classe implantant une projection en perspective.
    ///
    /// Cette classe implante l'interface de projection d�finie par la
    /// classe de base Projection et ajoute certaines fonctionnalit�es
    /// sp�cifiques � la projection en perspective, comme le zoom autour d'un
    /// point en particulier et le zoom �lastique.
    ///
    /// @author INF2990-A15-01
    /// @date 2015-11-13
    ////////////////////////////////////////////////////////////////////////
    class ProjectionPerspective : public Projection
    {
    public:
        // Constructeur
        ProjectionPerspective(
            int xMinCloture, int xMaxCloture,
            int yMinCloture, int yMaxCloture,
            double zAvant, double zArriere,
            double zoomInMax, double zoomOutMax,
            double incrementZoom,
            double xMinFenetre, double xMaxFenetre,
            double yMinFenetre, double yMaxFenetre);

        /// Zoom in, c'est-�-dire un agrandissement.
        virtual void zoomerIn();
        /// Zoom out, c'est-�-dire un rapetissement.
        virtual void zoomerOut();
        /// Modification de la cl�ture.
        virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
            const glm::ivec2& coinMax);
        /// Application de la projection.
        virtual void appliquer() const;

        /// Zoom out �lastique, sur un rectangle.
		void zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2) override {}
        /// Zoom in �latique, sur un rectangle.
		void zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2) override {}

        /// Translater la fen�tre virtuelle d'un pourcentage en @a X ou en @a Y
        void translater(double deplacementX, double deplacementY);
        /// Translater la fen�tre virtuelle d'un vecteur
        void translater(const glm::ivec2& deplacement);
        /// Centrer la fen�tre virtuelle sur un point
        void centrerSurPoint(const glm::ivec2& pointCentre);

        /// Obtenir les coordonn�es de la fen�tre virtuelle.
        inline void obtenirCoordonneesFenetreVirtuelle(
            double& xMin, double& xMax, double& yMin, double& yMax
            ) const;
        /// Obtenir le centre de la fenetre virtuelle
        inline glm::ivec2 getCenter();

        /// Obtenir le niveau de zoom
        double getZoom() const override;
    protected:
        void ajusterRapportAspect() override;
    };

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn inline void ProjectionPerspective::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
    ///
    /// Cette fonction retourne les coordonn�es de la fen�tre virtuelle
    /// associ�e � cette projection.
    ///
    /// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
    /// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
    /// @param[out]  yMin : La variable qui contiendra l'ordonn�e minimale.
    /// @param[out]  yMax : La variable qui contiendra l'ordonn�e maximale.
    ///
    /// @return Les coordonn�es de la fen�tre virtuelle.
    ///
    ////////////////////////////////////////////////////////////////////////
    inline void ProjectionPerspective::obtenirCoordonneesFenetreVirtuelle(
        double& xMin, double& xMax, double& yMin, double& yMax
        ) const
    {
        xMin = xMinFenetre_;
        xMax = xMaxFenetre_;
        yMin = yMinFenetre_;
        yMax = yMaxFenetre_;
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn inline glm::ivec2 ProjectionPerspective::getCenter()
    ///
    /// Cette fonction retourne les coordonn�es du centre de la fen�tre
    /// virtuelle.
    ///
    /// @return Les coordonn�es du centre de la fen�tre virtuelle.
    ///
    ////////////////////////////////////////////////////////////////////////
    inline glm::ivec2 ProjectionPerspective::getCenter()
    {
        return{ (xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2 };
    }

}; // Fin de l'espace de nom vue.

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
