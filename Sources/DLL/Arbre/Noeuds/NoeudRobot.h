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
	void forward();
	void reverse();
	void turnLeft();
	void turnRight();

	/// Passage en mode manuel / automatique
	void toggleManualMode();

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

	// capteur distance
	void initSensorDist();
	void refreshSensorDist();
	utilitaire::BoiteEnglobante* getMidSensorDanger() { return midSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getMidSensorSafe() { return midSensorSafeDetect_.get(); }
	utilitaire::BoiteEnglobante* getLeftSensorDanger() { return leftSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getLeftSensorSafe() { return leftSensorSafeDetect_.get(); }
	utilitaire::BoiteEnglobante* getRightSensorDanger() { return rightSensorDangerDetect_.get(); }
	utilitaire::BoiteEnglobante* getRightSensorSafe() { return rightSensorSafeDetect_.get(); }
	
	// Detection de suiveur
	bool checkSensors();
	bool isFarLeftDetected() { return farLeftDetected_; }
	bool isFarRightDetected() { return farRightDetected_; }
	bool isNearLeftDetected() { return nearLeftDetected_; }
	bool isNearRightDetected() { return nearRightDetected_; }
	bool isCenterDetected() { return centerDetected_; }

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

private:
	float const acceleration_ = 0.07f;
	float const maxSpeed_	  = 0.2f;
	float		speed_		  = 0.0f;
	time_t startTime_;
	std::unique_ptr<BehaviorContext> behaviorContext_;

	/// Profil actif du robot
	Profil currentProfile;

	// Suiveur de ligne
	int timeLost_;
	glm::dvec3 farLeftLineFollower_;
	glm::dvec3 nearLeftLineFollower_;
	glm::dvec3 closeCenterLeft_;
	glm::dvec3 centerLineFollower_;
	glm::dvec3 closeCenterRight_;
	glm::dvec3 nearRightLineFollower_;
	glm::dvec3 farRightLineFollower_;

	// Detection des suiveurs
	bool shouldFollow_;
	bool farLeftDetected_;
	bool farRightDetected_;
	bool nearLeftDetected_;
	bool nearRightDetected_;
	bool centerDetected_;

	// Hitbox
	std::unique_ptr<utilitaire::BoiteEnglobante> hitbox_;

	bool manualMode_;

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
};
#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
