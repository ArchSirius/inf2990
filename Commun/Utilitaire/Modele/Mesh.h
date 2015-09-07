///////////////////////////////////////////////////////////////////////////////
/// @file Mesh.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERING_MESH_H__
#define __RENDERING_MESH_H__

#include <vector>

#include "Materiau.h"

struct aiScene;		/// Déclarations avancées de Assimp
struct aiMesh;		//

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @class Mesh
	/// @brief Classe qui encapsule les données géométriques d'un modèle 3D, 
	///		   donc les vertices, les normales, les coordonnées de texture, les
	///		   couleurs des vertices et les faces.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	class Mesh{
	public:
		/// Alias de type
		template <typename T> using Conteneur = std::vector<T>;
		using Vertex	= glm::vec3;
		using Normale	= glm::vec3;
		using TexCoord	= glm::vec2;
		using Couleur	= glm::vec4;
		using Face		= glm::ivec3;

		Mesh() = default;
		/// Constructeur à partir d'un mesh et d'une scène assimp
		Mesh(aiScene const* scene, aiMesh const* mesh);
		
		/// Méthode pour obtenir les vertex du mesh	
		inline Conteneur<Vertex>   const& obtenirSommets()   const;

		/// Méthode pour obtenir les normales du mesh	
		inline Conteneur<Normale>  const& obtenirNormales()  const;

		/// Méthode pour obtenir les coordonnées de texture du mesh	
		inline Conteneur<TexCoord> const& obtenirTexCoords() const;

		/// Méthode pour obtenir les couleurs des sommets du mesh	
		inline Conteneur<Couleur>  const& obtenirCouleurs()  const;

		/// Méthode pour obtenir le materiau du mesh	
		inline Materiau			   const& obtenirMateriau()	 const;

		/// Méthode pour obtenir les couleurs des sommets du mesh	
		inline Conteneur<Face>	   const& obtenirFaces()     const;

		/// Méthode pour obtenir le nom du noeud (souvent une chaine vide)
		inline std::string		   const& obtenirNom()		 const;

		/// Vérifier si le mesh contient des sommets
		inline bool possedeSommets() const;
		/// Vérifier si le mesh contient des normales
		inline bool possedeNormales() const;
		/// Vérifier si le mesh contient des coordonnées de texture
		inline bool possedeTexCoords() const;
		/// Vérifier si le mesh contient des couleurs de vertex
		inline bool possedeCouleurs() const;
		/// Vérifier si le mesh contient des faces
		inline bool possedeFaces() const;

	private:
		/// Permet d'allouer la mémoire nécessaire pour contenir le mesh
		void reserverMemoire(aiMesh const* mesh);

		/// Les sommets du modèles
		Conteneur<Vertex> vertices_;
		/// Les normales
		Conteneur<Normale> normales_;
		/// Les coordonnées de texture
		Conteneur<TexCoord> texcoords_;
		/// Les couleurs des sommets
		Conteneur<Couleur> couleurs_;
		/// Le matériau associé au mesh
		Materiau materiau_;
		/// Indexes dans les différents tampons
		Conteneur<Face> faces_;
		/// Le nom
		std::string nom_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Vertex> const& Mesh::obtenirSommets() const
	///
	/// Cette fonction retourne les sommets dont est composé le mesh.
	///
	/// @return les sommets (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Vertex> const& Mesh::obtenirSommets() const
	{
		return vertices_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Normale> const& Mesh::obtenirNormales() const
	///
	/// Cette fonction retourne les normales contenues dans le mesh.
	///
	/// @return les normales (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Normale> const& Mesh::obtenirNormales() const
	{
		return normales_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::TexCoord> const& Mesh::obtenirTexCoords() const
	///
	/// Cette fonction retourne les coordonnées de texture dont est composé le mesh.
	///
	/// @return les coordonnées de textures (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::TexCoord> const& Mesh::obtenirTexCoords() const
	{
		return texcoords_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Couleur> const& Mesh::obtenirCouleurs() const
	///
	/// Cette fonction retourne les couleurs dont est composé le mesh.
	///
	/// @return les couleurs (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Couleur> const& Mesh::obtenirCouleurs() const
	{
		return couleurs_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Materiau const& Mesh::obtenirMateriau() const
	///
	/// Cette fonction retourne le matériau dont est composé le mesh.
	///
	/// @return le materiau (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Materiau const& Mesh::obtenirMateriau() const
	{
		return materiau_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Face> const& Mesh::obtenirFaces() const
	///
	/// Cette fonction retourne les index des faces dont est composé le mesh.
	/// Les faces sont supposées toujours être des triangles.
	///
	/// @return les faces (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Face> const& Mesh::obtenirFaces() const
	{
		return faces_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline std::string const& Mesh::obtenirNom() const
	///
	/// Cette fonction retourne le nom du mesh courant.  Le nom des meshes
	/// est très souvent vide (cela dépend du type de fichier utilisé).
	///
	/// @return Le nom du mesh (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline std::string const& Mesh::obtenirNom() const
	{
		return nom_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeSommets() const
	///
	/// Cette fonction indique si le mesh contient des sommets.
	///
	/// @return vrai si le mesh possède des sommets, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeSommets() const
	{
		return !vertices_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeNormales() const
	///
	/// Cette fonction indique si le mesh contient des normales.
	///
	/// @return vrai si le mesh possède des normales, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeNormales() const
	{
		return !normales_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeTexCoords() const
	///
	/// Cette fonction indique si le mesh contient des coordonnées de texture.
	///
	/// @return vrai si le mesh possède des coordonnées de texture, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeTexCoords() const
	{
		return !texcoords_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeCouleurs() const
	///
	/// Cette fonction indique si le mesh contient des couleurs de sommets.
	///
	/// @return vrai si le mesh possède des couleurs de sommets, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeCouleurs() const
	{
		return !couleurs_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeFaces() const
	///
	/// Cette fonction indique si le mesh contient des faces.
	///
	/// @return vrai si le mesh possède des faces, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeFaces() const
	{
		return !faces_.empty();
	}

} /// fin de rendering

#endif /// __RENDERING_MESH_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////