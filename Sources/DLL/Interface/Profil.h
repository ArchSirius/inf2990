#pragma once

enum State { defaultBehavior, followLine, searchLine, deviationLeft, deviationRight, avoidLeft, avoidRight };
enum Capteur { inactif = 0, actif = 1 };

struct Profil{
	/// Etat suivant FollowLine
	State followLineNextState;
	/// Etat suivant SearchLine
	State searchLineNextState;
	/// Angle de rotation et Etat suivant DeviationLeft
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
	State leftSensorSafeState;
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
	char* profile_name;
};