///////////////////////////////////////////////////////////////////////////////
/// @file Modele3D.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 2.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Modele3D.h"

#include "GL/glew.h"
#include "utilitaire.h"		// Afficher les erreurs dans un message box
#include "aidegl.h"			// Chargement des textures dans la mémoire du gpu

#include "Importer.hpp"		// Interface d'importation "assimp" C++
#include "scene.h"			// Structure de données de sortie "assimp"
#include "postprocess.h"	// Drapaux de post-traitement "assimp"

namespace modele{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Modele3D::Modele3D(Modele3D && modele)
	///
	/// Constructeur "move".  Utilise l'assignation "move".
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D::Modele3D(Modele3D && modele)
	{
		*this = std::move(modele);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Modele3D& Modele3D::operator=(Modele3D && modele)
	///
	/// Assignation par transfert ("move"), ne fait que transférer les
	/// données et s'assurer que les textures OpenGL ne seront pas libérées
	/// lors de la destruction du modèle passé en paramètre.
	///
	/// @return le modèle courant.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D& Modele3D::operator=(Modele3D && modele)
	{
		if (this != &modele)
		{
			identificateursTextures_ = std::move(modele.identificateursTextures_);
			mapTextures_ = std::move(modele.mapTextures_);
			racine_ = std::move(modele.racine_);
			cheminFichier_ = std::move(modele.cheminFichier_);
		}
		return *this;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::~Modele3D()
	///
	/// Destructeur. Ne fait que libérer les données des textures.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D::~Modele3D()
	{
		libererTextures();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::charger(Path cheminFichier)
	///
	/// Cette fonction charge un modèle 3D à partir d'un fichier supporté
	/// par la librairie 'assimp'. Les textures OpenGL afférentes sont
	/// également chargées.
	///
	/// @param[in] nomFichier : nom du fichier modèle (normalement .obj
	///	ou .dae)
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::charger(Path cheminFichier)
	{
		/// Ne pas charger le même fichier inutilement 
		if (cheminFichier_ == cheminFichier)
			return;

		cheminFichier_ = std::move(cheminFichier);

		/// Ne pas conserver les identifiants de texture d'un ancien modèle
		libererTextures();

		Assimp::Importer importer;

		/// Lors de l'importation, ne pas conserver les lignes et les points.
		importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);

		/// Le flag aiProcess_Triangulate, inclus dans aiProcessPreset_TargetRealtime_Quality,
		/// fera en sorte que les mesh ne comporteront que des triangles.
		const aiScene* scene{ importer.ReadFile(cheminFichier_, aiProcessPreset_TargetRealtime_Quality) };

		if (scene == nullptr) {
			utilitaire::afficherErreur(std::string{ "Impossible de charger l'objet 3d : " } +cheminFichier.filename() + std::string{ "." });
			return;
		}

		/// Charger l'ensemble des textures contenues dans le modèle :
		chargerTexturesExternes(scene);
		chargerTexturesIntegrees(scene);

		/// Chargement des données du modèle 3D
		racine_ = Noeud{ scene, scene->mRootNode };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::chargerTexturesExternes()
	///
	/// Cette fonction charge les textures OpenGL associées au modèle
	/// 'assimp' préalablement chargé, à partir des fichiers de textures.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::chargerTexturesExternes(aiScene const* scene)
	{
		// Itérer parmi l'ensemble des matériaux
		for (unsigned int i{ 0 }; i < scene->mNumMaterials; i++) {
			aiMaterial* materiau{ scene->mMaterials[i] };

			// POINT D'EXTENSION : il vous serait possible de prendre en charge d'autres types de textures que celle
			// en diffusion (DIFFUSE)...

			// Parcourir l'ensemble des textures pour ce matériau et stocker les noms de fichiers
			// Par la suite, nous initialiserons la mémoire de textures OpenGL et procéderons
			// au chargement des fichiers graphiques.
			int idTexture{ 0 };
			while (true) {

				// Chaîne UTF-8 (fort possiblement compatible ASCII) qui contient le nom de fichier associé à la texture
				// On peut l'utiliser comme une chaîne C standard (char *) sans réel risque (selon la doc. assimp !)
				aiString cheminTexture{ "" };

				// Récupérer le chemin vers la texture...
				aiReturn retour{ materiau->GetTexture(aiTextureType_DIFFUSE, idTexture, &cheminTexture) };
				// Vérifie que la texture est valide...
				if (retour != AI_SUCCESS)
					break;

				// Stocker le nom de texture dans le tableau associatif
				mapTextures_[cheminTexture.data] = NULL;

				idTexture++;
			}
		}
		// Pour chaque texture trouvée, procéder au chargement

		// Nombre de textures
		unsigned int nombreTextures{ static_cast<unsigned int>(mapTextures_.size()) };

		// Générer les textures OpenGL
		if (nombreTextures > 0)
		{
			identificateursTextures_ = std::vector<unsigned int>(nombreTextures);
			glGenTextures(nombreTextures, &identificateursTextures_[0]);

			// Itérateur STL
			std::map<std::string, unsigned int*>::iterator itr{ mapTextures_.begin() };

			for (unsigned int j{ 0 }; j < nombreTextures; j++) {
				std::string nomFichier{ itr->first };
				itr->second = &(identificateursTextures_[j]);
				itr++;

				// Charger la texture
				aidegl::glLoadTexture(std::string{ "media/" } +nomFichier, identificateursTextures_[j], false);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Mesh::chargerTexturesIntegrees()
	///
	/// Cette fonction charge les textures OpenGL intégrées au fichier du 
	/// modèle 'assimp' préalablement chargé.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::chargerTexturesIntegrees(aiScene const* scene)
	{
		if (scene->HasTextures()) {
			utilitaire::afficherErreur("Les textures intégrées ne sont pas prises en charge pour le moment.");
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::libererTextures()
	///
	/// Cette fonction libère les textures de la mémoire de la carte graphique
	/// et vide les conteneurs conservant les handles.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::libererTextures()
	{
		// Libérer les textures
		if (!identificateursTextures_.empty())
		{
			glDeleteTextures(static_cast<GLsizei>(identificateursTextures_.size()), &identificateursTextures_[0]);
			identificateursTextures_.clear();
		}
		if (!mapTextures_.empty())
		{
			mapTextures_.clear();
		}
	}

} /// fin de rendering

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////