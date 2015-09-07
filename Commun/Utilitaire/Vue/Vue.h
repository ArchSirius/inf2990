//////////////////////////////////////////////////////////////////////////////
/// @file Vue.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUE_H__
#define __UTILITAIRE_VUE_H__


#include "Camera.h"

namespace math {
	class Plan3D;
}


namespace vue {


	class Projection;


	////////////////////////////////////////////////////////////////////////
	/// @class Vue
	/// @brief Classe présentant l'interface commune à toutes les vues.
	///
	/// Cette classe définit l'interface que devront implanter chacune des
	/// vues, c'est-à-dire comme réagir à certains événements pour modifier
	/// la vue.  Chaque vue concrète sera généralement composée d'une caméra
	/// (classe Camera) et d'une projection (classe Projection).
	///
	/// Elle offre également certaines fonctionnalités communes à toutes les
	/// vues, comme la possibilité de trouver à quel point correspond, en
	/// coordonnées virtuelles, un point donné en coordonnées de clôture.
	///
	/// @author Martin Bisson
	/// @date 2006-12-16
	////////////////////////////////////////////////////////////////////////
	class Vue
	{
	public:
		/// Constructeur à partir d'une caméra
		Vue(const Camera& camera);
		/// Destructeur virtuel vide.
		virtual ~Vue() {}

		/// Conversion de coordonnées de clôture à coordonnées virtuelles
		bool convertirClotureAVirtuelle(int x, int y, glm::dvec3& point) const;
		/// Conversion de coordonnées de clôture à coordonnées virtuelles sur un plan donné
		bool convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, glm::dvec3& point) const;

		/// Obtient la caméra associée à cette vue.
		inline Camera& obtenirCamera();
		/// Obtient la caméra associée à cette vue (version constante).
		inline const Camera& obtenirCamera() const;


		// Obtention de la projection
		virtual const Projection& obtenirProjection() const = 0;
		/// Application de la projection
		virtual void appliquerProjection() const = 0;
		/// Application de la caméra
		virtual void appliquerCamera() const = 0;

		/// Modification de la clotûre
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax) = 0;

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn() = 0;
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut() = 0;
		/// Zoom in élastique
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) = 0;
		/// Zoom out élastique
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2) = 0;

		/// Déplacement dans le plan XY par rapport à la vue
		virtual void deplacerXY(double deplacementX, double deplacementY) = 0;
		/// Déplacement dans le plan XY par rapport à la vue
		virtual void deplacerXY(const glm::ivec2& deplacement) = 0;
		/// Déplacement selon l'axe des Z par rapport à la vue
		virtual void deplacerZ(double deplacement) = 0;
		/// Rotation selon les axes des X et des Y par rapport à la vue
		virtual void rotaterXY(double rotationX, double rotationY) = 0;
		/// Rotation selon les axes des X et des Y par rapport à la vue
		virtual void rotaterXY(const glm::ivec2& rotation) = 0;
		/// Rotation selon l'axe des Z par rapport à la vue
		virtual void rotaterZ(double rotation) = 0;

		/// Animation de la vue en fonction du temps
		virtual void animer(double temps);


	protected:
		/// Caméra utilisée pour cette vue
		Camera camera_;

	};


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Camera& Vue::obtenirCamera()
	///
	/// Cette fonction retourne la caméra associée à cette vue.
	///
	/// @return La caméra associée à cet objet.
	///
	////////////////////////////////////////////////////////////////////////
	inline Camera& Vue::obtenirCamera()
	{
		return camera_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const Camera& Vue::obtenirCamera() const
	///
	/// Cette fonction retourne la caméra associée à cette vue (version
	/// constante).
	///
	/// @return La caméra associée à cet objet.
	///
	////////////////////////////////////////////////////////////////////////
	inline const Camera& Vue::obtenirCamera() const
	{
		return camera_;
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
