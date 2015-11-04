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

enum State { default, followLine, searchLine, deviationLeft, deviationRight, avoidLeft, avoidRight };
enum Capteur { inactif = 0, actif = 1 };

struct Profil{
	/// Etat suivant FollowLine
	State followLineNextState;
	/// Etat suivant SearchLine
	State searchLineNextState;
	/// Angle de rotation et Etat suivant DiviationLeft
	State deviationLeftNextState;
	float deviationLeftAngle;
	/// Angle de rotation et Etat suivant DeviationRight
	State deviationRightNextState;
	float deviationRightAngle;
	/// Angle, duree, et Etat suivant AvoidLeft
	State avoidLeftNextState;
	float avoidLeftAngle;
	double avoidLeftTime;
	/// Angle, duree, et Etat suivant AvoidRight
	State avoidRightNextState;
	float avoidRightAngle;
	double avoidRightTime;

	/// Capteurs --- ligne + distances
	Capteur leftDistanceSensor;
	Capteur rightDistanceSensor;
	Capteur centerDistanceSensor;
	State leftSensorDangerState;
	State LeftSensorSafeState;
	State rightSensorDangerState;
	State rightSensorSafeState;
	State centerSensorDangerState;
	State centerSensorSafeState;
	/// Longueurs zones (somme <= 30 pouces)
	double leftSensorSafeLenght;
	double leftSensorDangerLenght;
	double rightSensorSafeLenght;
	double rightSensorDangerLenght;
	double centerSensorSafeLenght;
	double centerSensorDangerLenght;

	Capteur capteurLigne;
};

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

private:
	float const acceleration_ = 0.03f;
	float const maxSpeed_	  = 0.1f;
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

	// capteur milieu zone danger
	glm::dvec3 coinMin_;
	glm::dvec3 coinMax_;
	// capteur milieu zone securite
	glm::dvec3 coinMin1_;
	glm::dvec3 coinMax1_;
	//capteur droite zone danger
	glm::dvec3 coinMin2_;
	glm::dvec3 coinMax2_;
	//capteur droite zone danger
	glm::dvec3 coinMin3_;
	glm::dvec3 coinMax3_;
	//capteur gauche zone danger
	glm::dvec3 coinMin4_;
	glm::dvec3 coinMax4_;
	//capteur gauche zone securite
	glm::dvec3 coinMin5_;
	glm::dvec3 coinMax5_;
};
#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
