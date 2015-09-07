///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Nuanceur.h
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __OPENGL_NUANCEUR_H__
#define __OPENGL_NUANCEUR_H__

#include <filesystem>
#include <string>

#include "gl\glew.h"

namespace opengl{
	////////////////////////////////////////////////////////////////////////////////
	///
	/// @class OpenGL::Nuanceur
	/// @brief Encapsule un nuanceur OpenGL pour les types suivants :
	///				- Vertex shader
	///				- Fragment shader
	///
	/// @author Martin Paradis
	/// @date 2014-08-28
	////////////////////////////////////////////////////////////////////////////////
	class Nuanceur {
	public:
		using Path = std::tr2::sys::path;

		/// Types de nuanceur
		enum class Type : int {
			NUANCEUR_INVALIDE = 0,
			NUANCEUR_VERTEX = GL_VERTEX_SHADER,
			NUANCEUR_FRAGMENT = GL_FRAGMENT_SHADER
		};

		Nuanceur() = default;
		/// Constructeur par transfert ("move") pour éviter de relâcher le nuanceur
		/// sur la destruction
		Nuanceur(Nuanceur&& nuanceur);
		/// Copie par transfert ("move") pour éviter de relâcher le nuanceur
		/// sur la destruction
		Nuanceur& operator=(Nuanceur&& nuanceur);

		Nuanceur(Nuanceur const&) = delete;
		Nuanceur& operator=(Nuanceur const&) = delete;

		/// Destructeur
		~Nuanceur();

		/// obtient un identifiant opengl et compile le nuanceur contenu dans le
		/// fichier passé en paramètre
		void initialiser(Type typeNuanceur, Path fichierSource);

		/// Récupérer le nom
		inline const std::string  obtenirNom()    const;
		/// Récupérer le texte du nuanceur
		inline const std::string& obtenirSource() const;
		/// Récupérer le type du nuanceur
		inline const Type		  obtenirType()   const;
		/// Récupérer l'identifiant opengl du nuanceur
		inline		 GLuint		  obtenirHandle() const;

		/// Vérifie qu'un identifiant opengl a été assigné
		inline bool estInitialise()	  const;
		/// Vérifie si le code source du nuanceur est chargé
		inline bool sourceEstCharge() const;
		/// Vérifie que le code source a été compilé
		inline bool estCompile()      const;

		/// Récupérer une chaine de caractère représentant l'état du nuanceur
		std::string serialiser() const;

	private:
		/// Identifiant invalide d'un nuanceur
		static const GLint NUANCEUR_INVALIDE{ 0 };

		/// identifiant opengl
		GLuint		handle_{ 0 };
		/// Type du nuanceur
		Type		type_{ Type::NUANCEUR_INVALIDE };
		/// Nom du nuanceur (obtenu à partir du nom du fichier)
		std::string nom_;
		/// Code source du nuanceur
		std::string source_;
		/// Drapeaux de l'état du nuanceur
		struct Drapeau{
			bool estInitialise{ false };
			bool sourceEstCharge{ false };
			bool estCompile{ false };
		} flags;

		/// Permet de créer un identifiant opengl
		void creer(Type typeNuanceur);
		/// Permet de charger le code source sur la carte graphique
		void chargerSource(Path fichierSource);
		/// Permet de compiler le code source sur la carte graphique
		void compiler();
		/// Permet de relâcher l'identifiant opengl
		void relacher();
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const std::string Nuanceur::obtenirNom() const
	///
	/// Cette fonction retourne le nom du nuanceur, obtenu à partir du nom
	/// de fichier contenant le code source.
	///
	/// @return Le nom du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const std::string Nuanceur::obtenirNom() const
	{
		return nom_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const Nuanceur::Type Nuanceur::obtenirType() const
	///
	/// Cette fonction retourne le type du nuanceur, soit un nuanceur de 
	/// sommets ou un nuanceur de fragments.
	///
	/// @return Le type du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const Nuanceur::Type Nuanceur::obtenirType() const
	{
		return type_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline GLuint Nuanceur::obtenirHandle() const
	///
	/// Cette fonction retourne l'identifiant opengl du nuanceur.
	///
	/// @return L'identifiant opengl du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline GLuint Nuanceur::obtenirHandle() const
	{
		return handle_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const std::string& Nuanceur::obtenirSource() const
	///
	/// Cette fonction retourne la chaine de caractères contenant le code 
	/// source du nuanceur.
	///
	/// @return Le code source du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const std::string& Nuanceur::obtenirSource() const
	{
		return source_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::estInitialise() const
	///
	/// Cette fonction permet de savoir si un identifiant opengl a été
	/// généré pour le présent nuanceur.
	///
	/// @return Vrai si un identifiant existe, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::estInitialise() const
	{
		return flags.estInitialise;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::sourceEstCharge() const
	///
	/// Cette fonction permet de savoir si le code source du nuanceur a été
	/// chargé sur la carte graphique.
	///
	/// @return Vrai si le code source a été chargé, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::sourceEstCharge() const
	{
		return flags.sourceEstCharge;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::estCompile() const
	///
	/// Cette fonction permet de savoir si le code source du nuanceur a été
	/// compilé.
	///
	/// @return Vrai si le code source a été compilé, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::estCompile() const
	{
		return flags.estCompile;
	}


	namespace debug{
		/// Affiche les info de débug
		void afficherDebugInfo(const Nuanceur& nuanceur);
	}
}
#endif // __OPENGL_NUANCEUR_H__

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
