///////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.h
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_ROBOT_H__
#define __ARBRE_NOEUD_ROBOT_H__

#include "../../Behavior/BehaviorContext.h"
#include "NoeudComposite.h"
#include "GL/glew.h"
#include <time.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui repr�sente le robot du premier projet int�grateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot() = default;

	/// Temps initial de l'etat d'evitement
	time_t getStartTime() { return startTime_; };
	void setStartTime(time_t time) { startTime_ = time; };

	/// Vitesse
	float getSpeed() { return speed_; }
	void setSpeed(float speed) { speed_ = speed; }

	/// Fonctions de deplacement
	void forward();
	void reverse();
	void turnLeft();
	void turnRight();

	// Suiveur de ligne
	void refreshLineFollowers();
	glm::dvec3 getOutsideLeftLineFollower() { return outsideLeftLineFollower_; }
	glm::dvec3 getInsideLeftLineFollower() { return insideLeftLineFollower_; };
	glm::dvec3 getCenterLineFollower() { return centerLineFollower_; };
	glm::dvec3 getInsideRightLineFollower() { return insideRightLineFollower_; };
	glm::dvec3 getOutsideRightLineFollower() { return outsideRightLineFollower_; }

	/// Affiche le robot.
	virtual void afficherConcret() const;
	void animer(float dt) override;

private:
	float const acceleration_ = 0.001f;
	float const maxSpeed_	  = 0.1f;
	float		speed_		  = 0.0f;
	time_t startTime_;
	std::unique_ptr<BehaviorContext> behaviorContext_;

	// Suiveur de ligne
	glm::dvec3 outsideLeftLineFollower_;
	glm::dvec3 insideLeftLineFollower_;
	glm::dvec3 centerLineFollower_;
	glm::dvec3 insideRightLineFollower_;
	glm::dvec3 outsideRightLineFollower_;
};
#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
