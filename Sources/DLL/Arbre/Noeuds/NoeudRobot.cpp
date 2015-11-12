///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.cpp
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRobot.h"
#include "Utilitaire.h"
#include "../../Behavior/BehaviorList.h"

#include "GL/glew.h"
#include <cmath>
#include <math.h>
#include <algorithm>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "../../Application/Visitor/CollisionTool.h"
#include "../../Application/FacadeModele.h"

////////////////////////////////////////////////////////////////////////
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	scaleInitial_ = { 0.6f, 0.5f, 1.0f };
	scale_ = scaleInitial_;
	timeLost_ = 0;
	speed_ = 0.0f; 
	_lastDetection = time(0) - 5;
	_lastIntersection = time(0) - 5;

	assignerEstEnregistrable(false);

	behaviorContext_ = std::make_unique<BehaviorContext>(this);
	assignerEstEnregistrable(false);
	manualMode_ = false;

	// La prochaine ligne est à enlever lorsque les profils seront liés au formulaire
	loadProfile(FacadeModele::obtenirInstance()->getProfileData());
}

///////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::loadProfile(Profil profile)
///
/// Initialise/change les paramètres du robot selon le profil envoyé
///
/// @param[in] profile : La struct contenant les informations nécessaires.
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////
void NoeudRobot::loadProfile(std::shared_ptr<Profil> profile)
{
	currentProfile = *profile;
	if (currentProfile.centerSensorDangerLenght <= 0) { currentProfile.centerSensorDangerLenght = 0.05; }
	if (currentProfile.centerSensorSafeLenght <= 0) { currentProfile.centerSensorSafeLenght = 0.05; }
	if (currentProfile.leftSensorDangerLenght <= 0) { currentProfile.leftSensorDangerLenght = 0.05; }
	if (currentProfile.leftSensorSafeLenght <= 0) { currentProfile.leftSensorSafeLenght = 0.05; }
	if (currentProfile.rightSensorDangerLenght <= 0) { currentProfile.rightSensorDangerLenght = 0.05; }
	if (currentProfile.rightSensorSafeLenght <= 0) { currentProfile.rightSensorSafeLenght = 0.05; }
	behaviorContext_->changeBehavior(std::make_unique<DefaultBehavior>(behaviorContext_.get()));
}

////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	glRotatef(180, 0, 0, 1);


	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();

	// Capteurs
	if (true /* Affichage de catpeurs activés */)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		afficherCapteurs();
		glDisable(GL_BLEND);
		//glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
	}

	// Restauration de la matrice.
	glPopMatrix();

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();
}

////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherCapteurs() const
///
/// Cette fonction effectue le rendu des capteurs du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherCapteurs() const
{	
	glTranslatef(0.0, 0.0, 30.0);	// Pour bien les voir
	if (Debug::getInstance()->visualsEnabled())
		return;
	if (currentProfile.centerDistanceSensor)
	{
		/// Affiche milieu zone danger
		glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(midSensorDanger_->coinMin.x, midSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMax.x, midSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMax.x, midSensorDanger_->coinMax.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMin.x, midSensorDanger_->coinMax.y, 0.0f);
		glEnd();

		/// Affiche milieu zone sécuritaire
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(midSensorSafe_->coinMin.x, midSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMax.x, midSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMax.x, midSensorSafe_->coinMax.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMin.x, midSensorSafe_->coinMax.y, 0.0f);
		glEnd();
	}

	if (currentProfile.rightDistanceSensor)
	{
		/// Affiche droit zone danger
		glPushMatrix();
		glRotated(-45.0, 0.0, 0.0, 1.0);
		glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(rightSensorDanger_->coinMin.x, rightSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(rightSensorDanger_->coinMax.x, rightSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(rightSensorDanger_->coinMax.x, rightSensorDanger_->coinMax.y, 0.0f);
		glVertex3f(rightSensorDanger_->coinMin.x, rightSensorDanger_->coinMax.y, 0.0f);
		glEnd();

		/// Affiche droit zone securitaire
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(rightSensorSafe_->coinMin.x, rightSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(rightSensorSafe_->coinMax.x, rightSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(rightSensorSafe_->coinMax.x, rightSensorSafe_->coinMax.y, 0.0f);
		glVertex3f(rightSensorSafe_->coinMin.x, rightSensorSafe_->coinMax.y, 0.0f);
		glEnd();
		glPopMatrix();
	}

	if (currentProfile.leftDistanceSensor)
	{
		/// Affiche gauche zone danger
		glPushMatrix();
		glRotated(45.0, 0.0, 0.0, 1.0);
		glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(leftSensorDanger_->coinMin.x, leftSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMax.x, leftSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMax.x, leftSensorDanger_->coinMax.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMin.x, leftSensorDanger_->coinMax.y, 0.0f);
		glEnd();

		/// Affiche gauche zone sécurité
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(leftSensorSafe_->coinMin.x, leftSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(leftSensorSafe_->coinMax.x, leftSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(leftSensorSafe_->coinMax.x, leftSensorSafe_->coinMax.y, 0.0f);
		glVertex3f(leftSensorSafe_->coinMin.x, leftSensorSafe_->coinMax.y, 0.0f);
		glEnd();
		glPopMatrix();
	}
}

/////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::animer(float dt)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void NoeudRobot::animer(float dt)
{
	refreshSensorDist();
	refreshLineFollowers();
	
	if (!manualMode_)
	{
		if (checkSensors() && shouldFollow_)
		{
			behaviorContext_->changeBehavior(std::make_unique<FollowLine>(behaviorContext_.get()));
		}

		behaviorContext_->doAction();
	}
		
	if (speed_ > 0.04/*0.05f + -utilitaire::EPSILON*/)
	{
		speed_ -= 3*acceleration_ / 4.0f; 
		positionRelative_.x += speed_ * std::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
		positionRelative_.y += speed_ * std::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
	}	
	else if (speed_ < -0.04/*-0.05f - utilitaire::EPSILON*/)
	{
		speed_ += 3*acceleration_ / 4.0f; 
		positionRelative_.x += speed_ * std::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
		positionRelative_.y += speed_ * std::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
	}	
	else
	{
		speed_ = 0.0f;
	}		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float NoeudRobot::getMaxSpeed() const
///
/// Cette fonction retourne la vitesse maximale du robot
///
/// @return La vitesse maximale du robot
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::toggleManualMode()
{
	manualMode_ = !manualMode_;
	if (!manualMode_)
	{
		behaviorContext_->changeBehavior(std::make_unique<DefaultBehavior>(behaviorContext_.get()));
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn float NoeudRobot::getMaxSpeed() const
///
/// Cette fonction retourne la vitesse maximale du robot
///
/// @return La vitesse maximale du robot
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::getMaxSpeed() const
{
	return maxSpeed_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float NoeudRobot::getSpeed() const
///
/// Cette fonction retourne la vitesse actuelle du robot
///
/// @return La vitesse du robot
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::getSpeed() const
{
	return speed_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::setSpeed(float speed)
///
/// Cette fonction assigne la vitesse actuelle du robot
///
/// @param[in] speed : La nouvelle vitesse du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::setSpeed(float speed)
{
	speed_ = speed;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::forward(bool checkCollision)
///
/// Cette fonction effectue un mouvement vers l'avant
///
/// @param[in] checkCollision : true pour effectuer le calcul de collisions.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::forward()
{
	isTurnLeft_ = false;
	isTurnRight_ = false;

	if (speed_ + acceleration_ < maxSpeed_)
		speed_ += acceleration_;
	else
		speed_ = maxSpeed_;

	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::reverse(bool checkCollision)
///
/// Cette fonction effectue un mouvement vers l'arriere
///
/// @param[in] checkCollision : true pour effectuer le calcul de collisions.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::reverse()
{
	isTurnLeft_ = false;
	isTurnRight_ = false;

	if (speed_ - acceleration_ > -maxSpeed_)
		speed_ -= acceleration_;
	else
		speed_ = -maxSpeed_;
	
	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::turnLeft()
///
/// Cette fonction effectue une rotation vers la gauche
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::turnLeft()
{
	isTurnLeft_ = true;
	isTurnRight_ = false;

	if (speed_ != 0)
		angleRotation_ += std::abs(1.0f * speed_ / maxSpeed_);
	else
		angleRotation_ += 1.0f;

	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::collisionLeft()
///
/// Cette fonction effectue la reaction a une collision par la gauche
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::collisionLeft()
{
	if (speed_ != 0)
		angleRotation_ += abs(3.0f * speed_ / maxSpeed_);
	else
		angleRotation_ += 3.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::turnRight()
///
/// Cette fonction effectue un mouvement vers la droite
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::turnRight()
{
	isTurnLeft_ = false;
	isTurnRight_ = true;

	if (speed_ != 0)
		angleRotation_ -= std::abs(1.0f * speed_ / maxSpeed_);
	else
		angleRotation_ -= 1.0f;

	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::collisionRight()
///
/// Cette fonction effectue la reaction a une collision par la droite
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::collisionRight()
{
	if (speed_ != 0)
		angleRotation_ -= abs(3.0f * speed_ / maxSpeed_);
	else
		angleRotation_ -= 3.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshLineFollowers()
///
/// À partir de la boîte englobante et des transformations courantes,
/// calcule et enregistre la position des suiveurs de ligne.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::refreshLineFollowers()
{ 
	auto hitbox = utilitaire::calculerBoiteEnglobante(*modele_);;

	// Scale  ***Test sans le scale***
	glm::dvec3 matriceScale(
	{ 1.0, 1.0, 1.0 });
	// Translation
	glm::dvec3 matriceTranslation(
	{ positionRelative_.x, positionRelative_.y, positionRelative_.z });
	// Rotation
	glm::dmat3 matriceRotation(
	{ glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), -glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), 0 },
	{ 0, 0, 1 });

	// Suiveurs de lignes, sans les transformations courantes
	centerLineFollower_ = { (hitbox.coinMin.x + hitbox.coinMax.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	farLeftLineFollower_ = { (hitbox.coinMin.x + centerLineFollower_.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	farRightLineFollower_ = { (hitbox.coinMax.x + centerLineFollower_.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	nearLeftLineFollower_ = { (farLeftLineFollower_.x + centerLineFollower_.x) / 4, hitbox.coinMax.y, hitbox.coinMin.z };
	nearRightLineFollower_ = { (farRightLineFollower_.x + centerLineFollower_.x) / 4, hitbox.coinMax.y, hitbox.coinMin.z };
	closeCenterLeft_ = { (farLeftLineFollower_.x + centerLineFollower_.x) / 15, hitbox.coinMax.y, hitbox.coinMin.z };
	closeCenterRight_ = { (farRightLineFollower_.x + centerLineFollower_.x) / 15, hitbox.coinMax.y, hitbox.coinMin.z };
	//outsideLeftLineFollower_ = { hitbox.coinMin.x, hitbox.coinMax.y, hitbox.coinMin.z };
	//outsideRightLineFollower_ = { hitbox.coinMax.x, hitbox.coinMax.y, hitbox.coinMin.z };

	// Transformations courantes
	farLeftLineFollower_ = farLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	closeCenterLeft_ = closeCenterLeft_ * matriceRotation * matriceScale + matriceTranslation;
	closeCenterRight_ = closeCenterRight_ * matriceRotation * matriceScale + matriceTranslation;
	centerLineFollower_ = centerLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	farRightLineFollower_ = farRightLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	nearLeftLineFollower_ = nearLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	nearRightLineFollower_ = nearRightLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	//outsideLeftLineFollower_ = outsideLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	//outsideRightLineFollower_ = outsideRightLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::checkSensors()
///
/// Vérifie chacun de ses capteurs et donne les valeurs booléennes
/// nécessaires.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::checkSensors()
{
	// Si le capteur est desactive
	if (currentProfile.capteurLigne == Capteur::inactif)
	{
		centerDetected_ = false;
		farLeftDetected_ = false;
		farRightDetected_ = false;
		nearLeftDetected_ = false;
		nearRightDetected_ = false;
		lastLeftDetected_ = false;
		lastRightDetected_ = false;

		return false;
	}

	if (farLeftDetected_ /*|| outsideLeftDetected_*/)
	{
		lastLeftDetected_= true;
		lastRightDetected_= false;
		_lastIntersection = time(0);
	}
	else if (farRightDetected_ /*|| outsideRightDetected_*/)
	{
		lastLeftDetected_= false;
		lastRightDetected_ = true;
		_lastIntersection = time(0);
	}
	else
	{
		if (difftime(time(0), _lastIntersection) > 2)
		{
			lastLeftDetected_ = false;
			lastRightDetected_ = false;
		}
		else 
		{
			forward();
		}
	}
	
	centerDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(centerLineFollower_);
	centerDetected_ = centerDetected_ || FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(closeCenterLeft_);
	centerDetected_ = centerDetected_ || FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(closeCenterRight_);
	farLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farLeftLineFollower_);
	farRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farRightLineFollower_);
	nearLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearLeftLineFollower_);
	nearRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearRightLineFollower_);
	//outsideLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(outsideLeftLineFollower_);
	//outsideRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(outsideRightLineFollower_);
	
	return (centerDetected_ || nearLeftDetected_ || nearRightDetected_ || farLeftDetected_ || farRightDetected_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::initCapteurDist()
///
/// À partir de la boîte englobante et des transformations courantes,
/// calcule et enregistre la position des capteurs.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::initSensorDist()
{
	auto hitboxRobot = utilitaire::calculerBoiteEnglobante(*modele_);;
	// point milieu du robot
	double midPoint = (hitboxRobot.coinMin.x + hitboxRobot.coinMax.x) / 2;
	// distance du bout a gauche selon les x
	double coinMinX= (hitboxRobot.coinMin.x + midPoint) / 2;
	// distance du bout a droite selon les y
	double coinMaxX = (hitboxRobot.coinMax.x + midPoint) / 2;
	float unscale = 1 / scale_.y;

	//PREMIER CAPTEUR DU MILIEU : Capteur se situe au milieu du robot 
	//(ZONE DANGER)
	midSensorDangerDetect_->coinMin = { midPoint - 1.5, (hitboxRobot.coinMin.y), hitboxRobot.coinMin.z };
	midSensorDangerDetect_->coinMax = { midPoint + 1.5, hitboxRobot.coinMin.y - currentProfile.centerSensorDangerLenght * unscale /*lenght*/, hitboxRobot.coinMin.z };

	midSensorDanger_->coinMax = midSensorDangerDetect_->coinMax;
	midSensorDanger_->coinMin = midSensorDangerDetect_->coinMin;
	
	//(ZONE SECURITE)
	midSensorSafeDetect_->coinMin = { midPoint - 1.5, hitboxRobot.coinMin.y - currentProfile.centerSensorDangerLenght * unscale/*lenght danger*/, hitboxRobot.coinMin.z };
	midSensorSafeDetect_->coinMax = { midPoint + 1.5, (hitboxRobot.coinMin.y - (currentProfile.centerSensorDangerLenght /*lenght danger*/ + currentProfile.centerSensorSafeLenght) * unscale/*lenght secu*/), hitboxRobot.coinMin.z };
	
	midSensorSafe_->coinMax = midSensorSafeDetect_->coinMax;
	midSensorSafe_->coinMin = midSensorSafeDetect_->coinMin;
	
	//DEUXIEME CAPTEUR : Capteur se situe sur le bout a droite
	//(ZONE DANGER)
	rightSensorDangerDetect_->coinMin = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y) + 4.0, hitboxRobot.coinMin.z };
	rightSensorDangerDetect_->coinMax = { (hitboxRobot.coinMax.x + 1.5), (hitboxRobot.coinMin.y - currentProfile.rightSensorDangerLenght * unscale) + 4.0, hitboxRobot.coinMin.z };
	
	rightSensorDanger_->coinMax = rightSensorDangerDetect_->coinMax;
	rightSensorDanger_->coinMin = rightSensorDangerDetect_->coinMin;
	
	//(ZONE SECURITE)
	rightSensorSafeDetect_->coinMin = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y - currentProfile.rightSensorDangerLenght * unscale)+4.0, hitboxRobot.coinMin.z };
	rightSensorSafeDetect_->coinMax = { (hitboxRobot.coinMax.x + 1.5), (hitboxRobot.coinMin.y - (currentProfile.rightSensorDangerLenght + currentProfile.rightSensorSafeLenght) * unscale) + 4.0, hitboxRobot.coinMin.z };
	
	rightSensorSafe_->coinMax = rightSensorSafeDetect_->coinMax;
	rightSensorSafe_->coinMin = rightSensorSafeDetect_->coinMin;
	
	//TROISIME CAPTEUR : Capteur se situe sur le bout a gauche
	//(ZONE DANGER)
	leftSensorDangerDetect_->coinMin = { (hitboxRobot.coinMin.x - 1.5), (hitboxRobot.coinMin.y) + 4.0, hitboxRobot.coinMin.z };
	leftSensorDangerDetect_->coinMax = { (hitboxRobot.coinMin.x + 1.5), (hitboxRobot.coinMin.y - currentProfile.leftSensorDangerLenght * unscale) + 4.0, hitboxRobot.coinMin.z };

	leftSensorDanger_->coinMax = leftSensorDangerDetect_->coinMax;
	leftSensorDanger_->coinMin = leftSensorDangerDetect_->coinMin;
	
	//(ZONE SECURITE)
	leftSensorSafeDetect_->coinMin = { (hitboxRobot.coinMin.x - 1.5), (hitboxRobot.coinMin.y - currentProfile.leftSensorDangerLenght * unscale) + 4.0, hitboxRobot.coinMin.z };
	leftSensorSafeDetect_->coinMax = { (hitboxRobot.coinMin.x + 1.5), hitboxRobot.coinMin.y - ((currentProfile.leftSensorDangerLenght + currentProfile.leftSensorSafeLenght) * unscale) + 4.0, hitboxRobot.coinMin.z };
	
	leftSensorSafe_->coinMax = leftSensorSafeDetect_->coinMax;
	leftSensorSafe_->coinMin = leftSensorSafeDetect_->coinMin;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshCapteurDist()
///
/// À partir de la boîte englobante et des transformations courantes,
/// calcule et enregistre la position des capteurs.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::refreshSensorDist()
{
	// Rotation pour le capteur de droite
	glm::dmat3 matriceRotationDroite(
	{ glm::cos(utilitaire::DEG_TO_RAD(-45.0)), -glm::sin(utilitaire::DEG_TO_RAD(-45.0)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(-45.0)), glm::cos(utilitaire::DEG_TO_RAD(-45.0)), 0 },
	{ 0, 0, 1 });

	// Rotation pour le capteur de gauche
	glm::dmat3 matriceRotationGauche(
	{ glm::cos(utilitaire::DEG_TO_RAD(45.0)), -glm::sin(utilitaire::DEG_TO_RAD(45.0)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(45.0)), glm::cos(utilitaire::DEG_TO_RAD(45.0)), 0 },
	{ 0, 0, 1 });

	// Rotation du robot
	glm::dmat3 matriceRotation(
	{ glm::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 180)), -glm::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 180)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 180)), glm::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 180)), 0 },
	{ 0, 0, 1 });
	// Scale  ***Test sans le scale***
	glm::dvec3 matriceScale({ 0.6, 0.5, 1.0 });//({ scale_.x, scale_.y, scale_.z }); 
	// Translation
	glm::dvec3 matriceTranslation(
	{ positionRelative_.x, positionRelative_.y, positionRelative_.z });
	
	midSensorDangerDetect_->coinMax = midSensorDanger_->coinMax;// *matriceRotation * matriceScale + matriceTranslation;
	midSensorDangerDetect_->coinMin = midSensorDanger_->coinMin;// *matriceRotation * matriceScale + matriceTranslation;
	
	midSensorSafeDetect_->coinMax = midSensorSafe_->coinMax;// *matriceRotation * matriceScale + matriceTranslation;
	midSensorSafeDetect_->coinMin = midSensorSafe_->coinMin;// *matriceRotation * matriceScale + matriceTranslation;
	
	rightSensorDangerDetect_->coinMax = rightSensorDanger_->coinMax;// *matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	rightSensorDangerDetect_->coinMin = rightSensorDanger_->coinMin;// *matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	
	rightSensorSafeDetect_->coinMax = rightSensorSafe_->coinMax;// *matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	rightSensorSafeDetect_->coinMin = rightSensorSafe_->coinMin;// *matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	
	leftSensorDangerDetect_->coinMax = leftSensorDanger_->coinMax;// *matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
	leftSensorDangerDetect_->coinMin = leftSensorDanger_->coinMin;// *matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
	
	leftSensorSafeDetect_->coinMax = leftSensorSafe_->coinMax;// *matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
	leftSensorSafeDetect_->coinMin = leftSensorSafe_->coinMin;// *matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::unique_ptr<Behavior> NoeudRobot::getBehavior(State stateEnum)
///
/// Prend un enum représentant un état (provenant du C#) puis donne
/// le comportement associé.
///
/// @param[in] stateEnum l'enum du Profil associé au comportement désiré.
///
/// @return Le comportement correspondant.
///
////////////////////////////////////////////////////////////////////////
std::unique_ptr<Behavior> NoeudRobot::getBehavior(State stateEnum)
{
	// enum State { defaultBehavior, followLine, searchLine, deviationLeft, deviationRight, avoidLeft, avoidRight };
	switch (stateEnum)
	{
		case State::defaultBehavior:
			return std::make_unique<DefaultBehavior>(behaviorContext_.get());
		case State::followLine:
			return std::make_unique<FollowLine>(behaviorContext_.get());
		case State::searchLine :
			return std::make_unique<SearchLine>(behaviorContext_.get());
		case State::deviationLeft:
			return std::make_unique<DeviationLeft>(behaviorContext_.get());
		case State::deviationRight:
			return std::make_unique<DeviationRight>(behaviorContext_.get());
		case State::avoidLeft:
			return std::make_unique<AvoidLeft>(behaviorContext_.get());
		case State::avoidRight:
			return std::make_unique<AvoidRight>(behaviorContext_.get());
		default:
			return NULL;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn utilitaire::BoiteEnglobante* NoeudRobot::getHitbox() const
///
/// Cette Fonction retourne la boite englobante du robot.
///
/// @param[in] Aucun.
///
/// @return utilitaire::BoiteEnglobante.
///
////////////////////////////////////////////////////////////////////////
utilitaire::BoiteEnglobante* NoeudRobot::getHitbox() const
{
	return hitbox_.get();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::setHitbox()
///
/// Cette Fonction assigne la boite englobante du robot.
///
/// @param[in] utilitaire::BoiteEnglobante.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::makeHitbox()
{
	hitbox_ = std::make_unique<utilitaire::BoiteEnglobante>(utilitaire::calculerBoiteEnglobante(*modele_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool isTurnLeft()
///
/// Cette Fonction return true si le robot tourne a gauche.
///
/// @param[in] Aucun.
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::isTurnLeft()
{
	return isTurnLeft_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool isTurnRight()
///
/// Cette Fonction return true si le robot tourne a droite.
///
/// @param[in] Aucun.
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::isTurnRight()
{
	return isTurnRight_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::objectDetected()
///
/// Alerte le robot lors d'une detection d'obstacle.
///
/// @param[in] Debug::Declencheur sensor Le capteur qui declenche l'alerte.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::objectDetected(Debug::Declencheur sensor)
{
	switch (sensor)
	{
	case Debug::CAPTEUR_CENTRE_DANGER:
		behaviorContext_->changeBehavior(getBehavior(getProfile().centerSensorDangerState));
		break;
	case Debug::CAPTEUR_CENTRE_SAFE:
		behaviorContext_->changeBehavior(getBehavior(getProfile().centerSensorSafeState));
		break;
	case Debug::CAPTEUR_GAUCHE_DANGER:
		behaviorContext_->changeBehavior(getBehavior(getProfile().leftSensorDangerState));
		break;
	case Debug::CAPTEUR_GAUCHE_SAFE:
		behaviorContext_->changeBehavior(getBehavior(getProfile().leftSensorSafeState));
		break;
	case Debug::CAPTEUR_DROIT_DANGER:
		behaviorContext_->changeBehavior(getBehavior(getProfile().rightSensorDangerState));
		break;
	case Debug::CAPTEUR_DROIT_SAFE:
		behaviorContext_->changeBehavior(getBehavior(getProfile().rightSensorSafeState));
		break;
	default:
		behaviorContext_->changeBehavior(std::make_unique<DefaultBehavior>(behaviorContext_.get()));
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////