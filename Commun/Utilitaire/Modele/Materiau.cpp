///////////////////////////////////////////////////////////////////////////////
/// @file Materiau.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Materiau.h"

#include "scene.h"
#include "utilitaire.h"

namespace modele{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Materiau::Materiau(aiMaterial const* material)
	///
	/// Construit un matériau à partir d'un matériau assimp
	///
	/// @param[in] materiau : le materiau de assimp
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Materiau::Materiau(aiMaterial const* materiau)
	{
		/// Nom du materiau
		aiString nom;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_NAME, nom))
			nom_ = nom.data;
		else
			nom_ = "";

		/// Composante diffuse
		aiColor3D diffuse;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse))
			diffuse_ = utilitaire::ai_To_glm(diffuse);
		else
			diffuse_ = VecType{ 0.0f, 0.0f, 0.0f };

		/// Composante spéculaire
		aiColor3D speculaire;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_COLOR_SPECULAR, speculaire))
			speculaire_ = utilitaire::ai_To_glm(speculaire);
		else
			speculaire_ = VecType{ 0.0f, 0.0f, 0.0f };

		/// Composante ambiante
		aiColor3D ambiant;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_COLOR_AMBIENT, ambiant))
			ambiant_ = utilitaire::ai_To_glm(ambiant);
		else
			ambiant_ = VecType{ 0.0f, 0.0f, 0.0f };

		/// Composante d'émission
		aiColor3D emission;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_COLOR_EMISSIVE, emission))
			emission_ = utilitaire::ai_To_glm(emission);
		else
			emission_ = VecType{ 0.0f, 0.0f, 0.0f };

		/// Composante de transparence
		aiColor3D transparence;
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_COLOR_TRANSPARENT, transparence))
			transparence_ = utilitaire::ai_To_glm(transparence);
		else
			transparence_ = VecType{ 0.0f, 0.0f, 0.0f };

		/// Composante d'opacité
		float opacite{ 1.0f };
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_OPACITY, opacite))
			opacite_ = opacite;
		else
			opacite_ = 1.0f;

		/// Composante de brillance
		float shininess{ 0.0f };
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_SHININESS, shininess))
		{
			shininess_ = utilitaire::borne(shininess, 0.0f, 128.0f);
		}
		else
			shininess_ = 0.0f;

		/// Composante de force de brillance
		float shininessStrength{ 1.0f };
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength))
			shininessStrength_ = shininessStrength;
		else
			shininessStrength_ = 1.0f;

		/// Affichage en fil de fer
		bool filDeFer{ false };
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_ENABLE_WIREFRAME, filDeFer))
			filDeFer_ = filDeFer;
		else
			filDeFer_ = false;

		/// Culling
		bool afficherDeuxCotes{ false };
		if (aiReturn_SUCCESS == materiau->Get(AI_MATKEY_TWOSIDED, afficherDeuxCotes))
			afficherDeuxCotes_ = afficherDeuxCotes;
		else
			afficherDeuxCotes_ = false;

		/// Le nom de la texture
		aiString nomTexture{ "" };
		if (aiReturn_SUCCESS == materiau->GetTexture(aiTextureType_DIFFUSE, 0, &nomTexture))
			nomTexture_ = nomTexture.data;
		else
			nomTexture = "";
	}
} /// fin de rendering