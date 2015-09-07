///////////////////////////////////////////////////////////////////////////////
/// @file Noeud.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Noeud.h"
#include "scene.h"			// Structure de données de sortie "assimp"
#include "Utilitaire.h"		// ai_To_glm

namespace modele{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Noeud::Noeud(aiScene const* scene, aiNode const* noeud)
	///
	/// Construit un noeud à partir d'une scène et d'un noeud assimp.
	///
	/// @param[in] scene : Scene assimp contenant le modèle chargé
	/// @param[in] noeud : Le noeud de la scène à charger
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Noeud::Noeud(aiScene const* scene, aiNode const* noeud)
	{
		if (scene == nullptr || noeud == nullptr)
			return;

		/// Conserver le nom du noeud
		nom_ = noeud->mName.data;

		/// Convertir la matrice assimp en matrice glm
		transform_ = utilitaire::ai_To_glm(noeud->mTransformation);

		/// Pour éviter les multiples allocations de mémoire
		meshes_.reserve(noeud->mNumMeshes);

		/// Ajouter et constuire toutes les meshes du noeud courant
		for (size_t mesh_index{ 0 }; mesh_index < noeud->mNumMeshes; ++mesh_index)
		{
			meshes_.emplace_back(scene, scene->mMeshes[noeud->mMeshes[mesh_index]]);
		}

		/// Pour éviter les multiples allocations de mémoire
		enfants_.reserve(noeud->mNumChildren);

		/// Ajouter et construire tous les noeuds enfants
		for (size_t child_index{ 0 }; child_index < noeud->mNumChildren; ++child_index)
		{
			enfants_.emplace_back(scene, noeud->mChildren[child_index]);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Noeud::Noeud(Noeud && noeud)
	///
	/// Constructeur "move".  Utilise l'assignation "move".
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Noeud::Noeud(Noeud && noeud)
	{
		*this = std::move(noeud);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Noeud& Noeud::operator=(Noeud && noeud)
	///
	/// Assignation par transfert ("move"), ne fait que transférer les
	/// données.
	///
	/// @return le noeud courant.
	///
	////////////////////////////////////////////////////////////////////////
	Noeud& Noeud::operator=(Noeud && noeud)
	{
		if (this != &noeud)
		{
			meshes_ = std::move(noeud.meshes_);
			enfants_ = std::move(noeud.enfants_);
			transform_ = std::move(noeud.transform_);
			noeud.transform_ = glm::mat4x4{};
			nom_ = std::move(noeud.nom_);
		}
		return *this;
	}

} /// fin de rendering

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////