////////////////////////////////////////////////////////////////////////////////////
/// @file Camera.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_CAMERA_H__
#define __UTILITAIRE_CAMERA_H__

#include "glm/glm.hpp"

namespace vue {


	///////////////////////////////////////////////////////////////////////////
	/// @class Camera
	/// @brief Classe représentant une caméra dans le monde en 3D.
	///
	/// Cette camera encapsule les différentes opérations qu'il est possible 
	/// de faire pour déplacer le point de vue de l'observateur à l'intérieur
	/// de la scène en 3D.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	///////////////////////////////////////////////////////////////////////////
	class Camera
	{
	public:
		/// Constructeur à partir des coordonnées cartésiennes.
		Camera(const glm::dvec3& position,
			const glm::dvec3& pointVise,
			const glm::dvec3& directionHautCamera,
			const glm::dvec3& directionHautMonde);

		/// Destructeur virtuel vide.
		virtual ~Camera() {}

		/// Assigner la position de la caméra.
		inline void assignerPosition(const glm::dvec3& position);
		/// Assigner le point visé de la caméra.
		inline void assignerPointVise(const glm::dvec3& pointVise);
		/// Assigner la direction du haut de la caméra.
		inline void assignerDirectionHaut(const glm::dvec3& directionHaut);


		/// Obtenir la position de la caméra.
		inline const glm::dvec3& obtenirPosition() const;
		/// Obtenir le point visé de la caméra.
		inline const glm::dvec3& obtenirPointVise() const;
		/// Obtenir la direction du haut de la caméra.
		inline const glm::dvec3& obtenirDirectionHaut() const;

		/// Déplacement dans le plan perpendiculaire à la direction visée.
		void deplacerXY(double deplacementX, double deplacementY);
		/// Déplacement dans l'axe de la direction visée.
		void deplacerZ(double deplacement, bool bougePointVise);
		/// Rotation de la caméra autour de sa position.
		void tournerXY(double rotationX, double rotationY, bool empecheInversion = true);
		/// Rotation de la position de la caméra autour de son point de visé.
		void orbiterXY(double rotationX, double rotationY, bool empecheInversion = true);



		/// Positionner la caméra (appel à gluLookAt).
		void positionner() const;


	private:
		/// La position de la caméra.
		glm::dvec3 position_;
		/// La position du point visé par la caméra.
		glm::dvec3 pointVise_;
		/// La direction du haut de la caméra.
		glm::dvec3 directionHaut_;
		/// La direction du haut du monde de la caméra.
		const glm::dvec3 directionHautMonde_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPosition(const glm::dvec3& position)
	///
	/// Cette fonction permet d'assigner la position de la caméra.
	///
	/// @param[in] position : La nouvelle position de la caméra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPosition(const glm::dvec3& position)
	{
		position_ = position;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	///
	/// Cette fonction permet d'assigner le point de visé de la caméra.
	///
	/// @param[in] pointVise : Le nouveau point de visé de la caméra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	{
		pointVise_ = pointVise;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	///
	/// Cette fonction permet d'assigner la direction du haut de la caméra.
	///
	/// @param[in] directionHaut : La nouvelle direction du haut de la caméra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	{
		directionHaut_ = directionHaut;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPosition() const
	///
	/// Cette fonction permet d'obtenir la position de la caméra.
	///
	/// @return La position de la caméra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPosition() const
	{
		return position_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPointVise() const
	///
	/// Cette fonction permet d'obtenir le point de visé de la caméra.
	///
	/// @return Le point de visé de la caméra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPointVise() const
	{
		return pointVise_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	///
	/// Cette fonction permet d'obtenir la direction du haut de la caméra.
	///
	/// @return La direction du haut de la caméra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	{
		return directionHaut_;
	}


} // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_CAMERA_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
