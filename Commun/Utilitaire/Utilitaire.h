//////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_UTILITAIRE_H__
#define __UTILITAIRE_UTILITAIRE_H__

#include "glm\glm.hpp"

#include <sstream>

template <typename T> class aiMatrix4x4t;	/// Déclaration avancée d'une classe
using aiMatrix4x4 = aiMatrix4x4t<float>;	//  template

struct aiColor3D;

namespace modele{
	class Modele3D;
	class Noeud;
}

namespace utilitaire {


   /// Définition d'un type d'entier non signé.
	using uint = unsigned int;

	/// Constante pour la différence entre deux nombres réels.
	static const double EPSILON{ 0.00000001 };
	/// Constante PI.
	static const double PI{ 3.1415926535897932384626433832795 };

	/// Le vecteur i (dirigé vers l'axe des X positifs et unitaire).
	static glm::dvec3 vi{ 1.0, 0.0, 0.0 };
	/// Le vecteur j (dirigé vers l'axe des Y positifs et unitaire).
	static glm::dvec3 vj{ 0.0, 1.0, 0.0 };
	/// Le vecteur k (dirigé vers l'axe des Z positifs et unitaire).
	static glm::dvec3 vk{ 0.0, 0.0, 1.0 };

   /// Fonction globale pour l'affichage d'erreur.
   void afficherErreur(const std::string& message);

   /// Pour convertir les angles de radians en degrés.
   double RAD_TO_DEG( double AngleRad );
   /// Pour convertir les angles de degrés en radians.
   double DEG_TO_RAD( double AngleDeg );

   /// Pour convertir les km/h en m/s.
   float KMH_TO_MS( float kmh );
   /// Pour convertir les m/s en km/h.
   float MS_TO_KMH( float ms );

   /// Fonction pour connaître le signe d'un nombre.
   float SIGN( float nombre );

   /// Fonction pour savoir si un double est égal à zéro.
   bool EGAL_ZERO(double Nombre);

   /// Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
   bool DANS_INTERVALLE( double Valeur, double BorneMin, double BorneMax );
   /// Fonction pour vérifier si un Point 2d est dans un carré.
   bool DANS_LIMITESXY( double x, double xMin, double xMax,
                        double y, double yMin, double yMax );

   /// Calcule le rapport d'écrasement
   double ecrasement( double a, double b);

   /// Vérification de l'existance d'un fichier
   bool fichierExiste( const std::string& nomDuFichier );

   /// Applique une matrice de transformation à un point.
   glm::dvec3 appliquerMatrice( const glm::dvec3& point, const double mat[] );

   /// Conversion d'une matrice Assimp vers glm
   glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m);
   /// Conversion d'une couleur Assimp vers glm
   glm::vec3 ai_To_glm(aiColor3D const& c);

   /// Structure contenant les données pour une sphère englobante
   struct SphereEnglobante{
	   double rayon;
   };

   /// Structure contenant les données pour un cylindre englobant
   struct CylindreEnglobant{
	   double rayon;
	   double bas;
	   double haut;
   };

   /// Structure contenant les données pour une boite englobante
   struct BoiteEnglobante{
	   glm::dvec3 coinMin;
	   glm::dvec3 coinMax;
   };

   /// Calcule la sphère englobante
   SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele);

   /// Calcule le cylindre englobant
   CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele);

   /// Calcule la boite englobante
   BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele);

   /// Permet de récupérer les points extrêmes d'un noeud (récursivement)
   void obtenirPointsExtremes(modele::Noeud const& noeud, 
	   glm::dvec3& xMin, glm::dvec3& xMax, 
	   glm::dvec3& yMin, glm::dvec3& yMax, 
	   glm::dvec3& zMin, glm::dvec3& zMax);

   /// Transformation de coordonnées cartésiennes à sphériques
   glm::dvec3 xyzToSph(glm::dvec3 xyz);
   /// Transformation de coordonnées sphériques à cartésiennes
   glm::dvec3 sphToXyz(glm::dvec3 sph);


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneSuperieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur ne dépasse pas la borne.
   ///
   /// @param[in] valeur : La valeur de l'expression à borner.
   /// @param[in] borne  : La borne supérieure.
   ///
   /// @return La valeur bornée.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneSuperieure(T const& valeur, T const& borne)
   {
	   return valeur > borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneInferieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur dépasse la borne.
   ///
   /// @param[in,out] valeur : La valeur de l'expression à borner.
   /// @param[in]     borne  : La borne inférieure.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneInferieure(T const& valeur, T const& borne)
   {
	   return valeur < borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borne(T const& valeur, T const& min, T const& max)
   ///
   /// Cette fonction s'assure que la valeur ne dépasse pas les bornes.
   ///
   /// @param[in] valeur	: La valeur de l'expression à borner.
   /// @param[in] min		: La borne inférieure.
   /// @param[in] max		: La borne supérieure.
   ///
   /// @return la valeur bornée.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borne(T const& valeur, T const& min, T const& max)
   {
	   return borneSuperieure(borneInferieure(valeur, min), max);
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static std::string convertirEnChaine(const T& valeur)
   ///
   /// @brief Conversion d'un type générique vers une chaîne de caractères.
   ///
   /// Cette fonction convertit un type générique en une chaîne de
   /// caractères.  Comme elle se sert de l'opérateur << appliqué sur
   /// un ostringstream, elle devrait fonctionner pour toutes les classes
   /// qui définissent cet opérateur pour les ostream&.
   ///
   /// @param[in] valeur    : Valeur template à convertir en chaîne de
   ///                        caractères.
   /// @param[in] modifieur : Fonction utilisée pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Chaîne représentant le type.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static std::string convertirEnChaine(
      const T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
      std::ostringstream oss;

      // Application du modifieur s'il est spécifié.
      if (modifieur)
         oss << modifieur;

      oss << valeur;
      return oss.str();
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static bool convertirEnType(const std::string& chaine, T& valeur, std::ios_base& (*modifieur)(std::ios_base&) = 0)
   ///
   /// @brief Conversion d'une chaîne de caractères vers un type générique.
   ///
   /// Cette fonction convertit une chaîne de caractères en un type générique.
   /// Comme elle se sert de l'opérateur >> appliqué sur un istringstream,
   /// elle devrait fonctionner pour toutes les classes qui définissent cet
   /// opérateur pour les istream&.
   ///
   /// @param[in] chaine    : Chaîne à convertir.
   /// @param[in] valeur    : Valeur template qui contiendra la valeur contenu
   ///                        dans la chaîne.  Ne sera pas modifiée si la
   ///                        chaîne n'est pas valide.
   /// @param[in] modifieur : Fonction utilisée pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Vrai si la conversion a réussi.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static bool convertirEnType(
      const std::string& chaine,
      T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
	   std::istringstream iss{ chaine };

      // Application du modifieur s'il est spécifié.
      if (modifieur)
         iss >> modifieur;

      // Lecture de la valeur
      T temp;
	  iss >> temp;

	  // Pour que la conversion soit un succès, toute la chaîne doit avoir été
	  // convertie.  On ajoute donc le second test pour éviter qu'une chaîne
	  // comme "123bidon" puisse être acceptée et que toute la chaîne soit
	  // utilisée pour que la conversion soit considérée comme réussie.
	  const bool succes{ ((!iss.fail()) && (iss.peek() == EOF)) };

      if (succes)
         valeur = temp;

      return succes;
   }


} // Fin du namespace utilitaire.


#endif // __UTILITAIRE_UTILITAIRE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
