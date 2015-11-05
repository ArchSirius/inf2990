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
	void loadProfile(Profil profile);
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
	void refreshSensorDist();
	
	// Detection de suiveur
	bool checkSensors();
	bool isFarLeftDetected() { return farLeftDetected_; }
	bool isFarRightDetected() { return farRightDetected_; }
	bool isNearLeftDetected() { return nearLeftDetected_; }
	bool isNearRightDetected() { return nearRightDetected_; }
	bool isCenterDetected() { return centerDetected_; }

	/// Affiche le robot.
	virtual void afficherConcret() const;
	void animer(float dt) override;

	/// Vitesse du robot
	float getMaxSpeed() const;
	float getSpeed() const;
	void setSpeed(float speed);
	void hitBoxRobot();

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

	bool manualMode_;

	//coins de la hitBox du robot
	double hitBoxCoinMaxX_;
	double hitBoxCoinMinX_;
	double hitBoxCoinMaxY_;
	double hitBoxCoinMinY_;


	// capteur milieu zone danger
	glm::dvec3 coinMin_;
	glm::dvec3 coinMax_;
	utilitaire::BoiteEnglobante* midSensorDistDang1_ = new utilitaire::BoiteEnglobante();
	// capteur milieu zone securite
	glm::dvec3 coinMin1_;
	glm::dvec3 coinMax1_;
	utilitaire::BoiteEnglobante* midSensorDistSec1_ = new utilitaire::BoiteEnglobante();
	//capteur droite zone danger
	glm::dvec3 coinMin2_;
	glm::dvec3 coinMax2_;
	utilitaire::BoiteEnglobante* rightSensorDistDang2_ = new utilitaire::BoiteEnglobante();
	//capteur droite zone danger
	glm::dvec3 coinMin3_;
	glm::dvec3 coinMax3_;
	utilitaire::BoiteEnglobante* rightSensorDistSec2_ = new utilitaire::BoiteEnglobante();
	//capteur gauche zone danger
	glm::dvec3 coinMin4_;
	glm::dvec3 coinMax4_;
	utilitaire::BoiteEnglobante* leftSensorDistDang3_ = new utilitaire::BoiteEnglobante();
	//capteur gauche zone securite
	glm::dvec3 coinMin5_;
	glm::dvec3 coinMax5_;
	utilitaire::BoiteEnglobante* leftSensorDistSec3_ = new utilitaire::BoiteEnglobante();
};
#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
