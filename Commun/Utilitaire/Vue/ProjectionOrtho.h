////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONORTHO_H__
#define __UTILITAIRE_PROJECTIONORTHO_H__


#include "Projection.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionOrtho
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom élastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionOrtho : public Projection
	{
	public:
		/// Constructeur.
		ProjectionOrtho(int xMinCloture, int xMaxCloture,
			int yMinCloture, int yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double xMinFenetre, double xMaxFenetre,
			double yMinFenetre, double yMaxFenetre);


		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;


		/// Zoom out élastique, sur un rectangle.
		void zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2);
		/// Zoom in élatique, sur un rectangle.
		void zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2);

		/// Translater la fenêtre virtuelle d'un pourcentage en @a X ou en @a Y
		void translater(double deplacementX, double deplacementY);
		/// Translater la fenêtre virtuelle d'un vecteur
		void translater(const glm::ivec2& deplacement);
		/// Centrer la fenêtre virtuelle sur un point
		void centrerSurPoint(const glm::ivec2& pointCentre);

		/// Obtenir les coordonnées de la fenêtre virtuelle.
		inline void obtenirCoordonneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;


	private:
		/// Ajuste la fenêtre virtuelle pour respecter le rapport d'aspect.
		void ajusterRapportAspect();

		/// Borne inférieure en X de la fenêtre virtuelle.
		double xMinFenetre_;
		/// Borne supérieure en X de la fenêtre virtuelle.
		double xMaxFenetre_;
		/// Borne inférieure en Y de la fenêtre virtuelle.
		double yMinFenetre_;
		/// Borne supérieure en Y de la fenêtre virtuelle.
		double yMaxFenetre_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonnées de la fenêtre virtuelle
	/// associée à cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonnée minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonnée maximale.
	///
	/// @return Les coordonnées de la fenêtre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(
		double& xMin, double& xMax, double& yMin, double& yMax
		) const
	{
		xMin = xMinFenetre_;
		xMax = xMaxFenetre_;
		yMin = yMinFenetre_;
		yMax = yMaxFenetre_;
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
