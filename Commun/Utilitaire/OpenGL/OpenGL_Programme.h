///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Programme.h
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __GLSL_PROGRAM_H__
#define __GLSL_PROGRAM_H__

#include <string>
#include <map>
#include <vector>

#include "gl\glew.h"

#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace opengl {
	class Nuanceur;

	////////////////////////////////////////////////////////////////////////////////
	///
	/// @class OpenGL::Programme
	/// @brief Encapsule un programme OpenGL
	///
	/// @author Martin Paradis
	/// @date 2014-08-28
	////////////////////////////////////////////////////////////////////////////////
	class Programme{
	public:
		Programme() = default;

		/// Constructeur par transfert ("move") pour éviter de relâcher le programme
		/// sur la destruction
		Programme(Programme&& programme);
		/// Copie par transfert ("move") pour éviter de relâcher le programme sur la
		/// destruction
		Programme& operator=(Programme&& programme);

		/// Destructeur
		~Programme();

		/// Ajoute une uniforme au programme en cachant la location dans une map
		template <class T> inline void assignerUniforme(std::string const& nomUniforme, T const& valeurUniforme);

		/// Crée le programme
		void initialiser();

		/// Attacher un nuanceur
		void attacherNuanceur(opengl::Nuanceur const& nuanceur);
		/// Détacher un nuanceur
		void detacherNuanceur(opengl::Nuanceur const& nuanceur);

		/// Permet de savoir si au moins un nuanceur est attaché
		inline bool possedeNuanceur() const;
		/// Permet de savoir si le programme est valide
		inline bool estValide() const;
		/// Permet de savoir si le programme est initialisé
		inline bool estInitialise() const;
		/// Permet de savoir si le programme a été linké
		inline bool estLie() const;

		/// Récupérer l'identifiant du programme
		inline GLuint obtenirHandle() const;

		/// Récupérer une chaine de caractère représentant l'état du programme
		std::string serialiser() const;

		/// Commencer l'utilisation d'un programme
		static void Start(Programme & programme);
		/// Cesser l'utilisation d'un programme
		static void Stop(Programme const& programme);

		/// Assigner le nom du programme
		inline void assignerNom(std::string const& name);
		/// Obtenir le nom du programme
		inline std::string obtenirNom() const;

	private:
		/// Name
		std::string nom_;
		/// uniform location, by uniform name
		std::map<std::string, GLint> mapUniforme;
		/// names of attached shaders
		std::vector<std::string> nuanceursAttaches;
		/// OpenGL handle
		unsigned int handle_{ PROGRAMME_INVALIDE };
		/// state flags
		struct Drapeau{
			bool estInitialise{ false };
			bool estLie{ false };
			bool estValide{ false };
		} flags;

		/// get uniform location
		bool recupererLocationUniforme(std::string nomUniforme);

		/// bind uniform data to the OpenGL program
		template <class T> inline void lierUniforme(std::string nomUniforme, T const& valeurUniforme);

		/// Permet de linker le programme
		void lier();
		/// Permet de valider le programme
		void valider();
		/// Permet de relâcher l'identifiant du programme
		void relacher();

		/// static variables
		static const GLuint PROGRAMME_INVALIDE{ 0 };
		static		 GLuint programmeActif;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline GLuint Programme::obtenirHandle() const
	///
	/// Cette fonction retourne l'identifiant du programme.
	///
	/// @return L'identifiant du programme.
	///
	////////////////////////////////////////////////////////////////////////
	inline GLuint Programme::obtenirHandle() const
	{
		return handle_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Programme::possedeNuanceur() const
	///
	/// Cette fonction indique s'il y a des nuanceurs attachés au programme.
	///
	/// @return Vrai si au moins un nuanceur est attaché, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Programme::possedeNuanceur() const
	{
		return !nuanceursAttaches.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Programme::estInitialise() const
	///
	/// Cette fonction indique si l'identifiant du programme a été généré.
	///
	/// @return Vrai si l'identifiant a été généré, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Programme::estInitialise() const
	{
		return flags.estInitialise;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Programme::estLie() const
	///
	/// Cette fonction indique si le programme a été linké.
	///
	/// @return Vrai si le programme a été linké, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Programme::estLie() const
	{
		return flags.estLie;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Programme::estValide() const
	///
	/// Cette fonction indique si le programme a été validé.
	///
	/// @return Vrai si le programme a été validé, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Programme::estValide() const
	{
		return flags.estValide;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Programme::assignerNom(std::string name)
	///
	/// Cette fonction assigne le nom au programme.
	///
	/// @param[in] nom : le nom du programme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Programme::assignerNom(std::string const& nom)
	{
		nom_ = nom;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline std::string Programme::obtenirNom() const
	///
	/// Cette fonction retourne le nom du programme.
	///
	/// @return Le nom du programme.
	///
	////////////////////////////////////////////////////////////////////////
	inline std::string Programme::obtenirNom() const
	{
		return nom_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <class T> inline void Programme::assignerUniforme(std::string nomUniforme, T const& valeurUniforme)
	///
	/// Cette fonction récupère la location de l'uniforme et lie l'uniforme
	/// au programme.
	///
	/// @param[in] nomUniforme : Une chaine de caractère représentant le nom
	/// de l'uniforme.
	/// @param[in] const& valeurUniforme : L'uniforme à lier au programme.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	template <class T>
	inline void Programme::assignerUniforme(std::string const& nomUniforme, T const& valeurUniforme)
	{
		if (recupererLocationUniforme(nomUniforme))
		{
			lierUniforme(nomUniforme, const& valeurUniforme);
		}
	}

	////////////////////////////////////
	/// Liaison des uniformes OpenGL ///
	////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <class T> inline void Programme::lierUniforme(std::string nomUniforme, T const& valeurUniforme)
	///
	/// Cette fonction empêche de lier un type non-supporté.
	///
	/// @param[in] nomUniforme : Une chaine de caractère représentant le nom
	/// de l'uniforme.
	/// @param[in] valeurUniforme : L'uniforme à lier au programme.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	template <class T>
	inline void Programme::lierUniforme(std::string nomUniforme, T const& valeurUniforme)
	{
		static_assert(false, "OpenGL_Programme : un type d'uniforme non-supporte a ete utilise.  Seuls les types fondamentaux, les vecteurs et les matrices glm sont supportes.");
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, int const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, int const& uniform_value)
	{
		glProgramUniform1i(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec2 const& uniform_vector)
	{
		glProgramUniform2iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec3 const& uniform_vector)
	{
		glProgramUniform3iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec4 const& uniform_vector)
	{
		glProgramUniform4iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, unsigned int const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, unsigned int const& uniform_value)
	{
		glProgramUniform1ui(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec2 const& uniform_vector)
	{
		glProgramUniform2uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec3 const& uniform_vector)
	{
		glProgramUniform3uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec4 const& uniform_vector)
	{
		glProgramUniform4uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, float const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, float const& uniform_value)
	{
		glProgramUniform1f(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec2 const& uniform_vector)
	{
		glProgramUniform2fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec3 const& uniform_vector)
	{
		glProgramUniform3fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec4 const& uniform_vector)
	{
		glProgramUniform4fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, double const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, double const& uniform_value)
	{
		glProgramUniform1d(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec2 const& uniform_vector)
	{
		glProgramUniform2dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec3 const& uniform_vector)
	{
		glProgramUniform3dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec4 const& uniform_vector)
	{
		glProgramUniform4dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2 const& uniform_matrix)
	{
		glProgramUniformMatrix2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x3 const& uniform_matrix)
	{
		glProgramUniformMatrix2x3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x4 const& uniform_matrix)
	{
		glProgramUniformMatrix2x4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3 const& uniform_matrix)
	{
		glProgramUniformMatrix3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x2 const& uniform_matrix)
	{
		glProgramUniformMatrix3x2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x4 const& uniform_matrix)
	{
		glProgramUniformMatrix3x4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4 const& uniform_matrix)
	{
		glProgramUniformMatrix4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x2 const& uniform_matrix)
	{
		glProgramUniformMatrix4x2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name,, glm::mat4x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x3 const& uniform_matrix)
	{
		glProgramUniformMatrix4x3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2 const& uniform_matrix)
	{
		glProgramUniformMatrix2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x3 const& uniform_matrix)
	{
		glProgramUniformMatrix2x3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x4 const& uniform_matrix)
	{
		glProgramUniformMatrix2x4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3 const& uniform_matrix)
	{
		glProgramUniformMatrix3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x2 const& uniform_matrix)
	{
		glProgramUniformMatrix3x2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x4 const& uniform_matrix)
	{
		glProgramUniformMatrix3x4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4 const& uniform_matrix)
	{
		glProgramUniformMatrix4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x2 const& uniform_matrix)
	{
		glProgramUniformMatrix4x2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x3 const& uniform_matrix)
	{
		glProgramUniformMatrix4x3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}


	namespace debug{
		/// Affiche les info de débug
		void afficherDebugInfo(const Programme& programme);
	}
}

#endif /// __GLSL_PROGRAM_H__

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
