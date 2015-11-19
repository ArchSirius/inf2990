//////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORTHO_H__
#define __UTILITAIRE_VUEORTHO_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionOrtho.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrtho
	/// @brief Classe concrète de vue orthogonale.
	///
	/// Cette classe implante le comportement attendu d'une vue orthogonale.
	///
	/// @author Martin Bisson
	/// @date 2006-12-16
	////////////////////////////////////////////////////////////////////////
	class VueOrtho : public Vue
	{
	public:
		// Constructeur.
        VueOrtho(Camera const& camera, ProjectionOrtho const& projection);

		/// Obtention de la projection.
        virtual const ProjectionOrtho& obtenirProjection() const;
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
		/// Zoom in élastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out élastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

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
        ProjectionOrtho projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
