////////////////////////////////////////////////////////////////////////////////////
/// @file Projection.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "Projection.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Projection::Projection(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, bool estPerspective)
	///
	/// Constructeur d'une projection.  Ne fait qu'assigner les variables
	/// membres.
	///
	/// @param[in] xMinCloture    : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture    : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture    : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture    : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant         : distance du plan avant (en @a z).
	/// @param[in] zArriere       : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax      : facteur de zoom in maximal.
	/// @param[in] zoomOutMax     : facteur de zoom out maximal.
	/// @param[in] incrementZoom  : distance du plan arrière (en @a z).
	/// @param[in] estPerspective : vrai si la projection est perspective.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	Projection::Projection(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom, bool estPerspective) :
		xMinCloture_{ xMinCloture },
		xMaxCloture_{ xMaxCloture },
		yMinCloture_{ yMinCloture },
		yMaxCloture_{ yMaxCloture },
		zAvant_{ zAvant },
		zArriere_{ zArriere },
		zoomInMax_{ zoomInMax },
		zoomOutMax_{ zoomOutMax },
		incrementZoom_{ incrementZoom },
		estPerspective_{ estPerspective }
	{
	}

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void Projection::zoomerIn()
    ///
    /// Permet de faire un zoom in selon l'incrément de zoom.
    /// 
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void Projection::zoomerIn()
    {
        if (zoom_ > zoomInMax_)
            zoom_ -= incrementZoom_;

        appliquer();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void Projection::zoomerOut()
    ///
    /// Permet de faire un zoom out selon l'incrément de zoom.
    ///
    /// @return Aucune.
    ///
    //////////////////////////////////////////////////////////////////////// 
    void Projection::zoomerOut()
    {
        if (zoom_ < zoomOutMax_)
            zoom_ += incrementZoom_;

        appliquer();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void Projection::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
    ///
    /// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
    /// d'un redimensionnement de la fenêtre.
    ///
    /// L'agrandissement de la fenêtre virtuelle est proportionnel à
    /// l'agrandissement de la clotûre afin que les objets gardent la même
    /// grandeur apparente lorsque la fenêtre est redimensionnée.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
    ///                       nouvelle clôture
    /// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
    ///                       nouvelle clôture
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void Projection::redimensionnerFenetre(const glm::ivec2& coinMin,
        const glm::ivec2& coinMax)
    {
        // ajuster la fenetre
        xMinFenetre_ -= ((coinMax.x - coinMin.x) - (xMaxFenetre_ - xMinFenetre_)) / 2.0;
        xMaxFenetre_ += ((coinMax.x - coinMin.x) - (xMaxFenetre_ - xMinFenetre_)) / 2.0;
        yMinFenetre_ -= ((coinMax.y - coinMin.y) - (yMaxFenetre_ - yMinFenetre_)) / 2.0;
        yMaxFenetre_ += ((coinMax.y - coinMin.y) - (yMaxFenetre_ - yMinFenetre_)) / 2.0;

        // aspect ratio...?


        // donner la bonne grandeur a la cloture
        xMinCloture_ = coinMin.x;
        xMaxCloture_ = coinMax.x;
        yMinCloture_ = coinMin.y;
        yMaxCloture_ = coinMax.y;

        appliquer();
        ajusterRapportAspect();
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void Projection::ajusterRapportAspect()
    ///
    /// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
    /// de la clôture de façon à ce que le rapport d'aspect soit respecté.
    ///
    /// @return Aucune.
    ///
    ////////////////////////////////////////////////////////////////////////
    void Projection::ajusterRapportAspect()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, (GLsizei)(xMaxFenetre_ - xMinFenetre_), (GLsizei)(yMaxFenetre_ - yMinFenetre_));
        glMatrixMode(GL_MODELVIEW);
    }


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Projection::mettreAJourCloture() const
	///
	/// Spécifie la clôture de la fenêtre à l'aide de la fonction glViewport()
	/// dans la machine à états d'OpenGL.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Projection::mettreAJourCloture() const
	{
		glViewport(xMinCloture_,
			yMinCloture_,
			GLint{ xMaxCloture_ - xMinCloture_ },
			GLint{ yMaxCloture_ - yMinCloture_ });
	}

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn void Projection::getZoom()
    ///
    /// Permet d'obtenir le niveau du zoom.
    ///
    /// @return double zoom.
    ///
    ////////////////////////////////////////////////////////////////////////
    double Projection::getZoom() const
    {
        return zoom_;
    }

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Projection::mettreAJourProjection() const
	///
	/// Spécifie la matrice de projection dans la machine à états d'OpenGL.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Projection::mettreAJourProjection() const
	{

		// Sauvegarde du mode courant de matrice.
		GLint mode;
		glGetIntegerv(GL_MATRIX_MODE, &mode);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Application de la projection.
		appliquer();

		glMatrixMode(mode);
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
