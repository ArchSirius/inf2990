///////////////////////////////////////////////////////////////////////////////
/// @file Materiau.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERING_MATERIAU_H__
#define __RENDERING_MATERIAU_H__

#include <vector>
#include <string>

#include "glm/glm.hpp"

struct aiMaterial;

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @struct Materiau
	/// @brief Structure comprennant les divers composants d'un matériau.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	struct Materiau{
	public:
		/// Alias de type
		using VecType = glm::vec3;
		
		Materiau() = default;
		/// Constructeur à partir d'un matériau assimp
		Materiau(aiMaterial const* material);

		/// Nom du matériau
		std::string nom_;
		/// Composante diffuse
		VecType diffuse_;
		/// Composante spéculaire
		VecType speculaire_;
		/// Composante ambiante
		VecType ambiant_;
		/// Composante d'émission
		VecType emission_;
		/// Composante de transparence
		VecType transparence_;
		/// Composante d'opacité
		float opacite_					{ 0.0f };
		/// Composante de brillance
		float shininess_				{ 1.0f };
		/// Composante de force de brillance
		float shininessStrength_		{ 1.0f };
		/// Nom de la texture associée
		std::string nomTexture_;
		/// Mode de rendu (wireframe)
		bool filDeFer_					{ false };
		/// mode de culling (two-side)
		bool afficherDeuxCotes_			{ false };
	};
} /// fin de rendering

#endif /// __RENDERING_MATERIAU_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////