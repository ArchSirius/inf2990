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


namespace vue {


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn VueOrbite::VueOrbite(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
    ///
    /// Constructeur d'une vue orbite.  Ne fait que cr�er les objets
    /// Projection et Camera correspondant.
    ///
    /// @param[in] camera        : Cam�ra � utiliser au d�part pour cette vue.
    /// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
    /// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
    /// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
    /// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
    /// @param[in] zAvant        : distance du plan avant (en @a z).
    /// @param[in] zArriere      : distance du plan arri�re (en @a z).
    /// @param[in] zoomInMax     : facteur de zoom in maximal.
    /// @param[in] zoomOutMax    : facteur de zoom out maximal.
    /// @param[in] incrementZoom : distance du plan arri�re (en @a z).
    /// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
    ///                            virtuelle.
    /// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
    ///                            virtuelle.
    /// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
    ///                            virtuelle.
    /// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
    ///                            virtuelle.
    /// 
    /// @return Aucune (constructeur).
    ///
    ////////////////////////////////////////////////////////////////////////
    VueOrbite::VueOrbite(Camera const& camera, ProjectionPerspective const& projection) :
        Vue{ camera },
        projection_{ projection }
    {
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn const ProjectionPerspective& VueOrbite::obtenirProjection() const
    ///
    /// Retourne la projection en perspective associ�e � cette vue.
    ///
    /// @return La projection perspective associ�e � cette vue.
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
    /// Applique la matrice de projection correspondant � cette vue.
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
    /// Applique la matrice correspondant � cette vue selon la position de
    /// la cam�ra (eventuellement un gluLookAt()).
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::appliquerCamera() const
    {
        camera_.positionner();
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
    ///
    /// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
    /// d'un redimensionnement de la fen�tre.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
    ///                       nouvelle cl�ture.
    /// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
    ///                       nouvelle cl�ture.
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
    /// Permet de faire un zoom in selon l'incr�ment de zoom.
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
    /// Permet de faire un zoom out selon l'incr�ment de zoom.
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
    /// @param[in]  deplacementX : D�placement en pourcentage de la largeur.
    /// @param[in]  deplacementY : D�placement en pourcentage de la hauteur.
    ///
    /// Permet de faire un "pan" d'un certain pourcentage.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
    {
        auto cameraPos = camera_.obtenirPosition();
        auto dimensions = (glm::dvec2)projection_.obtenirDimensionCloture();
        auto cameraVise = camera_.obtenirPointVise();
        auto zoom = projection_.getZoom();

        // Selon les donn�es entr�es en C#, soit 0.10 :
        //	PositionX += (10% * LargeurFenetre)
        //	PositionY += (10% * HauteurFenetre)
        glm::dvec3 newCameraPos = { cameraPos.x + (deplacementX * dimensions.x * zoom), cameraPos.y + (deplacementY * dimensions.y * zoom), cameraPos.z };
        glm::dvec3 newCameraVise = { newCameraPos.x, newCameraPos.y, cameraVise.z };

        camera_.assignerPosition(newCameraPos);
        camera_.assignerPointVise(newCameraVise);
        //camera_.assignerDirectionHaut(/*??*/);
    }


    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
    ///
    /// Permet de faire un "pan" �quivalent � la distance du d�placement
    /// sp�cifi� en coordonn�es de cl�ture.
    ///
    /// @param[in]  deplacement : D�placement en coordonn�es de cl�ture
    ///                           (pixels).
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
    {
        auto cameraPos = camera_.obtenirPosition();
        auto dimensions = (glm::dvec2)projection_.obtenirDimensionCloture();
        auto cameraVise = camera_.obtenirPointVise();
        auto zoom = projection_.getZoom();

        // Selon les donn�es entr�es en C#, soit 0.10 :
        //	PositionX += (10% * LargeurFenetre)
        //	PositionY += (10% * HauteurFenetre)
        glm::dvec3 newCameraPos = { cameraPos.x + (deplacement.x * dimensions.x * zoom), cameraPos.y + (deplacement.y * dimensions.y * zoom), cameraPos.z };
        glm::dvec3 newCameraVise = { newCameraPos.x, newCameraPos.y, cameraVise.z };

        camera_.assignerPosition(newCameraPos);
        camera_.assignerPointVise(newCameraVise);
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerSouris(glm::dvec3 delta)
    ///
    /// Cette fonction permet de changer la position de la vue (avec cam�ra)
    ///
    /// @param[] aucun
    ///
    /// @return Aucun
    ///
    ///////////////////////////////////////////////////////////////////////
    void VueOrbite::deplacerSouris(glm::dvec3 delta)
    {
		//////////////////////////////
		//	     y					// Pour les coordonn�es sph�riques, le
		//	 	 ^					// syst�me standard place le Z vers le haut.
		//	 	 |					// Suivant ce standard, on traite donc:
		//	 	 |					//	y comme si c'�tait z
		//	 	 |					//  x comme si c'�tait y
		//	     |____________> x	//  z comme si c'�tait x
		// 	    /					//
		// 	   /					//
		//    v						//
		//    z						//
		//   (OEIL)					//
		//////////////////////////////
		double mouseSpeed = 0.01;

		// Coordonn�es sph�riques de l'ancienne position
		auto oldPos = camera_.obtenirPosition();
		auto oldRho = sqrt(oldPos.z*oldPos.z + oldPos.x*oldPos.x + oldPos.y*oldPos.y);
		auto oldPhi = acos(oldPos.y / oldRho);
		auto oldTht = atan2(oldPos.x, oldPos.z);

		// Coordonn�es sph�riques du delta
		auto delRho = sqrt(delta.z*delta.z + delta.x*delta.x + delta.y*delta.y);
		auto delPhi = acos(delta.y / delRho);
		auto delTht = atan2(delta.x, delta.z);
		
		// Coordonn�es sph�riques de la nouvelle position
		auto newRho = oldRho;	// C'est le zoom qui change rho, pas delta
		auto newPhi = (delta.y < 0) ? (oldPhi + delPhi * mouseSpeed) : (oldPhi - delPhi * mouseSpeed);
		if (newPhi > utilitaire::PI / 2.0) newPhi = utilitaire::PI / 2;
		else if (newPhi < 2.7) newPhi = 2.7;
		//std::cout << newPhi << std::endl;
		//auto newPhi = oldPhi;
		auto newTht = oldTht + delTht * mouseSpeed;
		//auto newTht = oldTht;
		
		// Coordonn�es cart�siennes de la nouvelle position
		glm::dvec3 newPos{
			newRho * sin(newPhi) * sin(newTht),
			newRho * cos(newPhi),
			newRho * sin(newPhi) * cos(newTht)
		};

        camera_.assignerPosition(std::move(newPos));
        //camera_.assignerPointVise(camera_.obtenirPointVise() - std::move(delta));
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void VueOrbite::deplacerZ(double deplacement)
    ///
    /// Ne fait rien, car se d�placer dans l'axe de la profondeur n'a pas
    /// vraiment de signification avec une vue orthogonale.
    ///
    /// @param[in]  deplacement : D�placement selon l'axe Z.
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
    /// Permet de faire une rotation de la cam�ra autour du point vers
    /// lequel elle regarde en modifiant l'angle de rotation et l'angle
    /// d'�l�vation.
    ///
    /// Une rotation de 100% correspondant � 360 degr�s en X (angle de
    /// rotation) ou 180 degr�s en Y (angle d'�l�vation).
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
    /// Permet de faire une rotation de la cam�ra autour du point vers
    /// lequel elle regarde en modifiant l'angle de rotation et l'angle
    /// d'�l�vation.
    ///
    /// Un d�placement de la taille de la fen�tre correspond � 100%.
    ///
    /// @param[in]  rotation : Rotation en coordonn�es de clot�re (pixels).
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
    /// correspondrait � un rouli et n'est pas souhaitable pour cette vue.
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
