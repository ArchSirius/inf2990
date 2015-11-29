///////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.cpp
/// @author DGI
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Utilitaire.h"

#include <windows.h>
#include <fstream>
#include <limits>

#include "scene.h"
#include "Modele3D.h"
#include "mesh.h"
#include "Noeud.h"

#include "glm\gtx\norm.hpp"

namespace utilitaire {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void afficherErreur(const std::string& message)
	///
	/// Cette fonction affiche une message d'erreur.
	///
	/// @param[in] message : La chaîne décrivant l'erreur.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	void afficherErreur(const std::string& message)
	{
#ifdef WIN32
		MessageBoxA(0, message.c_str(), "Erreur", MB_OK | MB_ICONERROR);
#else
		std::cerr << message << std::endl;
#endif
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool EGAL_ZERO(double nombre)
	///
	/// Fonction pour savoir si un double est égal à zéro.
	///
	/// @param[in] nombre : Valeur à vérifier.
	///
	/// @return true si nombre est égal a 0, false autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool EGAL_ZERO(double nombre)
	{
		return (nombre < EPSILON) && (-nombre < EPSILON);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double RAD_TO_DEG(double angleRad)
	///
	/// Cette fonction convertit les angles de radians en degrés.
	///
	/// @param[in] angleRad : L'angle en radians à convertir.
	///
	/// @return L'angle converti en degrés
	///
	////////////////////////////////////////////////////////////////////////
	double RAD_TO_DEG(double angleRad)
	{
		return angleRad * 57.2957795130823208767981548141052;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double DEG_TO_RAD(double angleDeg)
	///
	/// Cette fonction convertit les angles de degrés en radians.
	///
	/// @param[in] angleDeg : L'angle en degrés à convertir.
	///
	/// @return L'angle converti en radians.
	///
	////////////////////////////////////////////////////////////////////////
	double DEG_TO_RAD(double angleDeg)
	{
		return angleDeg * 0.0174532925199432957692369076848861;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float KMH_TO_MS( float kmh )
	///
	/// Fonction de conversion des km/h en m/s.
	///
	/// @param[in] kmh : Valeur en kilomètres / heure.
	///
	/// @return float => vitesse en mètres par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	float KMH_TO_MS(float kmh)
	{
		return (kmh * 1000.0f / 3600.0f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float MS_TO_KMH( float ms )
	///
	/// Fonction de conversion des m/s en km/h.
	///
	/// @param[in] ms : Valeur en mètres / seconde.
	///
	/// @return float => vitesse en kilomètres / heure.
	///
	////////////////////////////////////////////////////////////////////////
	float MS_TO_KMH(float ms)
	{
		return (ms * 3.6f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn int SIGN( float nombre )
	///
	/// Fonction pour connaître le signe d'un nombre.
	///
	/// @param[in] nombre : Valeur dont on veut trouver le signe.
	///
	/// @return int => 1 si positif, -1 si négatif, 0 si = 0.
	///
	////////////////////////////////////////////////////////////////////////
	float SIGN(float nombre)
	{
		if (nombre == 0.0f) {
			return 0.0f;
		}
		else if (nombre > 0.0f) {
			return  1.0f;
		}
		else {
			return -1.0f;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_INTERVALLE( double valeur, double borneMin, double borneMax ) 
	///
	/// Cette fonction vérifie si une valeur est dans un intervalle.
	///
	/// @param[in] valeur   : La valeur à vérifier.
	/// @param[in] borneMin : La borne inférieure de l'intervalle.
	/// @param[in] borneMax : La borne supérieure de l'intervalle.
	///
	/// @return Vrai si la valeur est dans l'intervalle, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_INTERVALLE(double valeur, double borneMin, double borneMax)
	{
		return (valeur >= borneMin) && (valeur <= borneMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_LIMITESXY( double x, double xMin, double xMax, double y, double yMin, double yMax )
	///
	/// Cette fonction vérifie si un point 2d est dans un carré.
	///
	/// @param[in] x    : Coordonnée x du point.
	/// @param[in] xMin : La borne inférieure en x.
	/// @param[in] xMax : La borne supérieure en x.
	/// @param[in] y    : Coordonnée y du point.
	/// @param[in] yMin : La borne inférieure en y.
	/// @param[in] yMax : La borne supérieure en y.
	///
	/// @return Vrai si le point (x,y) est dans le carré, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_LIMITESXY(double x, double xMin, double xMax,
		double y, double yMin, double yMax)
	{
		return (DANS_INTERVALLE(x, xMin, xMax) && DANS_INTERVALLE(y, yMin, yMax));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double CUtilitaire::ecrasement( double a, double b )
	///
	/// Cette fonction calcule le rapport d'écrasement pour un rectangle de
	/// longueur @a a et largeur @a b.
	///   - si a = b, le rapport est 1
	///   - le rapport est toujours positif et plus grand que 1.
	///
	/// @param[in] a : Valeur à rapprocher.
	/// @param[in] b : Point limite du rapprochement.
	///
	/// @return Le rapport @a r  de @a a /  @a b
	///
	////////////////////////////////////////////////////////////////////////
	double ecrasement(double a, double b)
	{
		double r{ a / b };
		// Le rapport doit être toujours positif.
		if (r < 1.0)
			r = 1.0 / r;

		return r;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool fichierExiste( const std::string &nomDuFichier )
	///
	/// Cette fonction vérifie si un fichier d'un certain nom donné existe.
	///
	/// @param [in] nomDuFichier : Le nom du fichier dont on veut vérifier
	///                            l'existence.
	///
	/// @return Vrai si le fichier existe, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool fichierExiste(const std::string& nomDuFichier)
	{
		std::ifstream ficin;
		ficin.open(nomDuFichier.c_str());
		bool fail{ ficin.fail() };

		if (!fail)
			ficin.close();

		return !fail;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m)
	///
	/// Cette fonction convertit une matrice 4x4 assimp vers une matrice
	/// 4x4 de glm
	///
	/// @param [in] m : La matrice assimp
	///
	/// @return la matrice glm
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m)
	{
		glm::mat4x4 mat;
		for (glm::length_t i{ 0 }; i < mat.length(); ++i)
		{
			for (glm::length_t j{ 0 }; j < mat.length(); ++j)
			{
				mat[i][j] = m[i][j];
			}
		}
		/// On passe d'un ordre par rangée vers un ordre par colonne
		return glm::transpose(mat);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::vec3 ai_To_glm(aiColor3D const& c)
	///
	/// Cette fonction convertit une couleur 3D assimp vers un vecteur 3D
	/// de glm
	///
	/// @param [in] m : La couleur assimp
	///
	/// @return le vecteur glm
	///
	////////////////////////////////////////////////////////////////////////
	glm::vec3 ai_To_glm(aiColor3D const& c)
	{
		glm::vec3 couleur;
		for (glm::length_t i{ 0 }; i < couleur.length(); ++i)
		{
			couleur[i] = c[i];
		}
		return couleur;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void appliquerMatrice( const glm::dvec3& point, const double mat[])
	///
	/// Cette fonction multiplie le point par une matrice de transformation
	/// donnée et retourne le résultat.
	///
	/// @param [in] point : Le point à transformer.
	/// @param [in] mat   : La matrice de transformation.
	///
	/// @return Le point transformé.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 appliquerMatrice(const glm::dvec3& point, const double mat [])
	{
		// Calculer la multiplication entre la matrice et le point.
		glm::dvec3 pointTransforme{
		mat[0] * point[0] + mat[4] * point[1] + mat[8] * point[2] + mat[12],
		mat[1] * point[0] + mat[5] * point[1] + mat[9] * point[2] + mat[13],
		mat[2] * point[0] + mat[6] * point[1] + mat[10] * point[2] + mat[14] };

		const double w{
			mat[3] * point[0] +
			mat[7] * point[1] +
			mat[11] * point[2] +
			mat[15] };

		// Retour des coordonnées homogènes vers la 3D.
		pointTransforme /= w;

		return pointTransforme;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule la sphère englobante d'un modèle 3D en espace
	/// local.
	///
	/// @param [in] modele : le modèle 3D
	///
	/// @return La sphereEnglobante.
	///
	////////////////////////////////////////////////////////////////////////
	SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele)
	{
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();

		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		obtenirPointsExtremes(modele.obtenirNoeudRacine(), xMin, xMax, yMin, yMax, zMin, zMax);

		// Le rayon de la sphère englobante est le point le plus éloigné parmi les 6 points extrêmes possibles...
		double max{ 0 };
		double norme{ 0 };

		norme = glm::length2(xMin); if (norme > max) max = norme;
		norme = glm::length2(yMin); if (norme > max) max = norme;
		norme = glm::length2(zMin); if (norme > max) max = norme;
		norme = glm::length2(xMax); if (norme > max) max = norme;
		norme = glm::length2(yMax); if (norme > max) max = norme;
		norme = glm::length2(zMax); if (norme > max) max = norme;

		return SphereEnglobante{ sqrt(max) };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule le cylindre englobant d'u nmodèle 3D en espace
	/// local.
	///
	/// @param [in] modele : le modèle 3D
	///
	/// @return Le cylindre englobant.
	///
	////////////////////////////////////////////////////////////////////////
	CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele)
	{
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();

		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		obtenirPointsExtremes(modele.obtenirNoeudRacine(), xMin, xMax, yMin, yMax, zMin, zMax);

		// Obtenir le point extrême le plus éloigné parmi les axes xy. L'axe z servira
		// à établir le bas et le haut du cylindre.

		double max{ 0 };
		double norme{ 0 };
		norme = xMin[0] * xMin[0] + xMin[1] * xMin[1]; if (norme > max) max = norme;
		norme = yMin[0] * yMin[0] + yMin[1] * yMin[1]; if (norme > max) max = norme;
		norme = zMin[0] * zMin[0] + zMin[1] * zMin[1]; if (norme > max) max = norme;
		norme = xMax[0] * xMax[0] + xMax[1] * xMax[1]; if (norme > max) max = norme;
		norme = yMax[0] * yMax[0] + yMax[1] * yMax[1]; if (norme > max) max = norme;
		norme = zMax[0] * zMax[0] + zMax[1] * zMax[1]; if (norme > max) max = norme;

		// Nous avons trouvé le rayon...
		double rayon{ sqrt(max) };

		// Le bas et le dessus sont les extrémums en z.
		double bas{ dmax }, haut{ dmin };
		if (xMin[2]<bas) bas = xMin[2]; if (xMin[2]>haut) haut = xMin[2];
		if (yMin[2]<bas) bas = yMin[2]; if (yMin[2]>haut) haut = yMin[2];
		if (zMin[2]<bas) bas = zMin[2]; if (zMin[2]>haut) haut = zMin[2];
		if (xMax[2]<bas) bas = xMax[2]; if (xMax[2]>haut) haut = xMax[2];
		if (yMax[2]<bas) bas = yMax[2]; if (yMax[2]>haut) haut = yMax[2];
		if (zMax[2]<bas) bas = zMax[2]; if (zMax[2]>haut) haut = zMax[2];

		return CylindreEnglobant{ rayon, bas, haut };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule la boite englobante d'un modèle 3D en espace
	/// local.
	///
	/// @param [in] modele : le modèle 3D
	///
	/// @return La boite englobante.
	///
	////////////////////////////////////////////////////////////////////////
	BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele)
	{
		const modele::Noeud& noeud{ modele.obtenirNoeudRacine() };
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();
		
		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		/// Récupérer les points extrêmes du modèle 3D
		obtenirPointsExtremes(noeud, xMin, xMax, yMin, yMax, zMin, zMax);

		// Le coin min est simplement les coordonnées minimales et le coin max est
		// simplement les coordonnées maximales.
		glm::dvec3 coinMin{ xMin[0], yMin[1], zMin[2] };
		glm::dvec3 coinMax{ xMax[0], yMax[1], zMax[2] };
		return BoiteEnglobante{ coinMin, coinMax };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void obtenirPointsExtremes(modele::Noeud const& noeud, glm::dvec3& xMin, glm::dvec3& xMax, glm::dvec3& yMin, glm::dvec3& yMax, glm::dvec3& zMin, glm::dvec3& zMax)
	///
	/// Cette fonction calcule les points extrêmes d'un noeud, récursivement.
	///
	/// @param [in] noeud : un noeud d'un modèle 3D
	/// @param [in,out] xMin  : point contenant la valeur minimale de x
	/// @param [in,out] xMax  : point contenant la valeur maximale de x
	/// @param [in,out] yMin  : point contenant la valeur minimale de y
	/// @param [in,out] yMax  : point contenant la valeur maximale de y
	/// @param [in,out] zMin  : point contenant la valeur minimale de z
	/// @param [in,out] zMax  : point contenant la valeur maximale de z
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void obtenirPointsExtremes(modele::Noeud const& noeud,
		glm::dvec3& xMin, glm::dvec3& xMax,
		glm::dvec3& yMin, glm::dvec3& yMax,
		glm::dvec3& zMin, glm::dvec3& zMax)
	{
		// Pour chacun des 'meshes'...
		for (modele::Mesh const& mesh : noeud.obtenirMeshes())
		{
			// Pour chaque face...
			for (modele::Mesh::Face const& face : mesh.obtenirFaces())
			{
				// Pour chaque vertex...
				for (glm::length_t index{ 0 }; index < face.length(); ++index)
				{
					int indexVertex{ face[index] };

					// On vérifie les coordonnées...
					glm::dvec3 sommet{ mesh.obtenirSommets()[indexVertex] };

					if (sommet.x<xMin.x)
						xMin = sommet;
					else if (sommet.x>xMax.x)
						xMax = sommet;

					if (sommet.y<yMin.y)
						yMin = sommet;
					else if (sommet.y>yMax.y)
						yMax = sommet;

					if (sommet.z<zMin.z)
						zMin = sommet;
					else if (sommet.z>zMax.z)
						zMax = sommet;
				}
			}
		}
		
		// Calcul récursif des points extrêmes
		for (modele::Noeud const& noeud : noeud.obtenirEnfants())
		{
			obtenirPointsExtremes(noeud, xMin, xMax, yMin, yMax, zMin, zMax);
		}
	}

	/// Transformation de coordonnées cartésiennes à sphériques
	glm::dvec3 xyzToSph(glm::dvec3 xyz) 
	{
		auto rho = std::sqrt(xyz.x*xyz.x + xyz.y*xyz.y + xyz.z*xyz.z);
		auto phi = std::acos(xyz.z / rho);
		auto tht = std::atan2(xyz.y, xyz.x);
		return glm::dvec3{ rho, phi, tht };
	}

	/// Transformation de coordonnées sphériques à cartésiennes
	glm::dvec3 sphToXyz(glm::dvec3 sph) 
	{
		auto x = sph.x * std::sin(sph.y) * std::cos(sph.z);
		auto y = sph.x * std::sin(sph.y) * std::sin(sph.z);
		auto z = sph.x * std::cos(sph.y);
		return glm::dvec3{ x, y, z };
	}
}; // Fin de l'espace de nom utilitaire.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
