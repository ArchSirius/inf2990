///////////////////////////////////////////////////////////////////////////////
/// @file AideCollision.h
/// @brief Ce fichier contient la déclaration de l'espace de nom aidecollision.
///
/// Il contient les déclarations de fonctions utiles pour le calcul des forces
/// causées par les collisions.
///
/// @author Martin Bisson
/// @date 2007-01-10
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_AIDECOLLISION_H__
#define __UTILITAIRE_AIDECOLLISION_H__


#include "glm\glm.hpp"

/// Espace de nom contenant des fonctions utiles pour le calcul des forces
/// causées par les collisions.
namespace aidecollision {


   /// Type de collisions possibles avec un segment.
   enum Collision {
      COLLISION_AUCUNE = 0 ,
      COLLISION_SEGMENT_PREMIERPOINT ,
      COLLISION_SEGMENT ,
      COLLISION_SEGMENT_DEUXIEMEPOINT ,
      COLLISION_SPHERE ,
      COLLISION_ARC
   };

   /// Structure contenant les informations d'une collision.
   class DetailsCollision {
   public:
      /// Type de collision.
      Collision type;
      /// Direction de la collision.
      glm::dvec3  direction;
      /// Enfoncement de l'objet à l'intérieur de la collision.
      double    enfoncement;
   };

   /// Calcule la collision d'un objet circulaire avec un segment de droite.
   DetailsCollision calculerCollisionSegment(
      const glm::dvec2& point1,
      const glm::dvec2& point2,
      const glm::dvec2& position,
      double          rayon,
      bool            collisionAvecPoints = true
      );

   /// Calcule la collision d'un objet sphérique avec un segment de droite.
   DetailsCollision calculerCollisionSegment(
      const glm::dvec3& point1,
      const glm::dvec3& point2,
      const glm::dvec3& position,
      double          rayon,
      bool            collisionAvecPoints = true
      );

   /// Calcule la collision d'un objet circulaire avec un cercle.
   DetailsCollision calculerCollisionCercle(
      const glm::dvec2& centreCercle,
      double          rayonCercle,
      const glm::dvec2& positionObjet,
      double          rayonObjet
      );

   /// Calcule la collision d'un objet circulaire avec un arc de cercle.
   DetailsCollision calculerCollisionArc(
      const glm::dvec2& centreCercle,
      const glm::dvec2& pointArc1,
      const glm::dvec2& pointArc2,
      const glm::dvec2& positionObjet,
      double          rayonObjet
      );

   /// Calcule la collision d'un objet sphérique avec une sphère.
   DetailsCollision calculerCollisionSphere(
      const glm::dvec3& centreSphere,
      double          rayonSphere,
      const glm::dvec3& positionObjet,
      double          rayonObjet
      );

   /// Calcule la force en deux dimensions à partir d'une collision.
   glm::dvec2 calculerForceRebondissement2D(
      const DetailsCollision& details,
      double constanteRebondissement
      );

   /// Calcule la force en trois dimensions à partir d'une collision.
   glm::dvec3 calculerForceRebondissement3D(
      const DetailsCollision& details,
      double constanteRebondissement
      );

   /// Calcule la force d'amortissement en deux dimensions au cours d'une
   /// collision.
   glm::dvec2 calculerForceAmortissement2D(
      const DetailsCollision& details,
      const glm::dvec2& vitesse,
      double constanteAmortissement
      );

   /// Calcule la force d'amortissement en trois dimensions au cours d'une
   /// collision.
   glm::dvec3 calculerForceAmortissement3D(
      const DetailsCollision& details,
      const glm::dvec3& vitesse,
      double constanteAmortissement
      );

   /// Calcule la force en deux dimensions causée par la collision d'un objet
   /// circulaire avec un segment de droite.
   glm::dvec2 calculerCollisionSegment(
      const glm::dvec2&   point1,
      const glm::dvec2&   point2,
      const glm::dvec2&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const glm::dvec2&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en trois dimensions causée par la collision d'un objet
   /// sphérique avec un segment de droite.
   glm::dvec3 calculerCollisionSegment(
      const glm::dvec3&   point1,
      const glm::dvec3&   point2,
      const glm::dvec3&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const glm::dvec3&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en deux dimensions causée par la collision d'un objet
   /// circulaire avec un cercle.
   glm::dvec3 calculerCollisionCercle(
      const glm::dvec3&   centreCercle,
      double            rayonCercle,
      const glm::dvec3&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const glm::dvec2&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en trois dimensions causée par la collision d'un objet
   /// sphérique avec une sphère.
   glm::dvec3 calculerCollisionSphere(
      const glm::dvec3&   centreSphere,
      double            rayonSphere,
      const glm::dvec3&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const glm::dvec3&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la combinaison de deux constantes de rebondissement.
   double calculerCombinaisonRebondissement(
      double constante1, double constante2
      );

   /// Calcule la combinaison de deux constantes d'amortissement.
   double calculerCombinaisonAmortissement(
      double constante1, double constante2
      );


} // Fin de l'espace de nom aidecollision.


#endif // __UTILITAIRE_AIDECOLLISION_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
