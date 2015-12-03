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
#include "Profil.h"
#include "GL/glew.h"
#include "Utilitaire.h"
#include <time.h>
#include "Utilitaire.h"
#include <memory>
#include "Debug.h"
#include "sound.h"
#include <chrono>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui représente le robot du premier projet intégrateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot() = default;

	/// Charge le profil
	void loadProfile(std::shared_ptr<Profil> profile);
	std::unique_ptr<Behavior> getBehavior(State stateEnum);
	Profil getProfile() { return currentProfile; }

	/// Temps initial de l'etat d'evitement
	time_t getStartTime() { return startTime_; };
	void setStartTime(time_t time) { startTime_ = time; };

	/// Fonctions de deplacement
	void forward() ;
	void reverse();
	void turnLeft();
	void turnRight();
	void collisionLeft();
	void collisionRight();

	/// Passage en mode manuel / automatique
	void toggleManualMode();
	bool isManual() { return manualMode_; }

	// Suiveur de ligne
	int getTimeLost() const { return timeLost_; }
	void setTimeLost(int timeLost) { timeLost_ = timeLost; }
	void refreshLineFollowers();
	void setShouldFollow(bool should) { shouldFollow_ = should; }
	glm::dvec3 getFarLeftLineFollower() { return farLeftLineFollower_; }
	glm::dvec3 getNearLeftLineFollower() { return nearLeftLineFollower_; }
	glm::dvec3 getCenterLineFollower() { return centerLineFollower_; }
	glm::dvec3 getNearRightLineFollower() { return nearRightLineFollower_; }
	glm::dvec3 getFarRightLineFollower() { return farRightLineFollower_; }
	glm::dvec3 getOutsideRightLineFollower() { return outsideRightLineFollower_; }
	glm::dvec3 getOutsideLeftLineFollower() { return outsideLeftLineFollower_; }

	// capteur distance
	void initSensorDist();
	void refreshSensorDist();
	utilitaire::BoiteEnglobante* getMidSensorDanger() { return midSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getMidSensorSafe() { return midSensorSafeDetect_.get(); }
	utilitaire::BoiteEnglobante* getLeftSensorDanger() { return leftSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getLeftSensorSafe() { return leftSensorSafeDetect_.get(); }
	utilitaire::BoiteEnglobante* getRightSensorDanger() { return rightSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getRightSensorSafe() { return rightSensorSafeDetect_.get(); }
	
	// Detection d'obstacle
	void objectDetected(Debug::Declencheur sensor);
	void setLastDetection(time_t time) { _lastDetection = time; }
	time_t getLastDetection() { return _lastDetection; }

	// Detection de suiveur
	bool checkSensors();
	bool isFarLeftDetected() { return farLeftDetected_; }
	bool isFarRightDetected() { return farRightDetected_; }
	bool isNearLeftDetected() { return nearLeftDetected_; }
	bool isNearRightDetected() { return nearRightDetected_; }
	bool isCenterDetected() { return centerDetected_; }
	bool isOutsideLeftDetected() { return outsideLeftDetected_; }
	bool isOutsideRightDetected() { return outsideRightDetected_; }

	bool shouldWait() { return wait_; }
	void resetWaitTime() { _waitBeforeChangeState = time(0); }

	bool isLastLeftDetected() { return lastLeftDetected_; }
	bool isLastRightDetected() { return lastRightDetected_; }
	void setLastLeftDetected(bool detected) { lastLeftDetected_ = detected; }
	void setLastRightDetected(bool detected) { lastRightDetected_ = detected; }

	/// Affiche le robot.
	virtual void afficherConcret() const;
	void afficherCapteurs() const;
	void animer(float dt) override;

	/// Vitesse du robot
	float getMaxSpeed() const;
	float getSpeed() const;
	void setSpeed(float speed);
	void hitBoxRobot();

	utilitaire::BoiteEnglobante* getHitbox() const;
	void makeHitbox();

	bool isTurnLeft();
	bool isTurnRight();

	void jouerSon(int i);
	void pauseSon(int i, bool pause);
	void updateSound();

	double theta_ = 0;

private:
	float const acceleration_ = 0.05f;
	float const maxSpeed_	  = 0.2f;
	float		speed_		  = 0.0f;
	time_t startTime_;
	time_t _lastDetection;
	time_t _lastIntersection;
	time_t _waitBeforeChangeState;
	bool wait_ = false;
	std::unique_ptr<BehaviorContext> behaviorContext_;

	/// Profil actif du robot
	Profil currentProfile;

	// Suiveur de ligne
	int timeLost_;
	glm::dvec3 outsideLeftLineFollower_;
	glm::dvec3 farLeftLineFollower_;
	glm::dvec3 nearLeftLineFollower_;
	glm::dvec3 closeCenterLeft_;
	glm::dvec3 centerLineFollower_;
	glm::dvec3 closeCenterRight_;
	glm::dvec3 nearRightLineFollower_;
	glm::dvec3 farRightLineFollower_;
	glm::dvec3 outsideRightLineFollower_;

	// Detection des suiveurs
	bool shouldFollow_;
	bool farLeftDetected_;
	bool farRightDetected_;
	bool nearLeftDetected_;
	bool nearRightDetected_;
	bool centerDetected_;
	bool outsideLeftDetected_;
	bool outsideRightDetected_;

	// Pour savoir par ou tourner
	bool lastLeftDetected_ = false;
	bool lastRightDetected_ = false;

	// Hitbox
	std::unique_ptr<utilitaire::BoiteEnglobante> hitbox_;

	bool manualMode_;
	bool isTurnLeft_ = false;
	bool isTurnRight_ = false;
	bool isSonTurn_ = false;
	bool isSonMotor_ = false;

	//coins de la hitBox du robot
	std::unique_ptr<utilitaire::BoiteEnglobante> hitboxRobot_ = nullptr;

	// capteur milieu zone danger
	std::shared_ptr<utilitaire::BoiteEnglobante> midSensorDangerDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> midSensorDanger_ = std::make_shared < utilitaire::BoiteEnglobante >() ;	// Affichage
	// capteur milieu zone securite
	std::shared_ptr<utilitaire::BoiteEnglobante> midSensorSafeDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> midSensorSafe_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Affichage
	//capteur droite zone danger
	std::shared_ptr<utilitaire::BoiteEnglobante> rightSensorDangerDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> rightSensorDanger_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Affichage
	//capteur droite zone danger
	std::shared_ptr<utilitaire::BoiteEnglobante> rightSensorSafeDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> rightSensorSafe_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Affichage
	//capteur gauche zone danger
	std::shared_ptr<utilitaire::BoiteEnglobante> leftSensorDangerDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> leftSensorDanger_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Affichage
	//capteur gauche zone securite
	std::shared_ptr<utilitaire::BoiteEnglobante> leftSensorSafeDetect_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Detection
	std::shared_ptr<utilitaire::BoiteEnglobante> leftSensorSafe_ = std::make_shared < utilitaire::BoiteEnglobante >();	// Affichage

	//FMOD
	std::unique_ptr<Sound> son_;

	// Spot
	std::chrono::time_point < std::chrono::system_clock > initialTime_;
	std::chrono::duration<double> elapsedTime_;
};
#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
