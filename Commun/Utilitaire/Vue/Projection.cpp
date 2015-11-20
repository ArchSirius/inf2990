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
	/// @param[in] xMinCloture    : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture    : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture    : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture    : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant         : distance du plan avant (en @a z).
	/// @param[in] zArriere       : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax      : facteur de zoom in maximal.
	/// @param[in] zoomOutMax     : facteur de zoom out maximal.
	/// @param[in] incrementZoom  : distance du plan arri�re (en @a z).
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
    /// Permet de faire un zoom in selon l'incr�ment de zoom.
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
    /// Permet de faire un zoom out selon l'incr�ment de zoom.
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
    /// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
    /// d'un redimensionnement de la fen�tre.
    ///
    /// L'agrandissement de la fen�tre virtuelle est proportionnel �
    /// l'agrandissement de la clot�re afin que les objets gardent la m�me
    /// grandeur apparente lorsque la fen�tre est redimensionn�e.
    ///
    /// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
    ///                       nouvelle cl�ture
    /// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
    ///                       nouvelle cl�ture
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
    /// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
    /// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
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
	/// Sp�cifie la cl�ture de la fen�tre � l'aide de la fonction glViewport()
	/// dans la machine � �tats d'OpenGL.
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
	/// Sp�cifie la matrice de projection dans la machine � �tats d'OpenGL.
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
