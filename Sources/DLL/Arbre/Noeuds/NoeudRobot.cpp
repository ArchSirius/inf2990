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
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
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

	behaviorContext_ = std::make_unique<BehaviorContext>(this);

	manualMode_ = false;

	// La prochaine ligne est � enlever lorsque les profils seront li�s au formulaire
	loadProfile(FacadeModele::obtenirInstance()->getProfileData());
}

///////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::loadProfile(Profil profile)
///
/// Initialise/change les param�tres du robot selon le profil envoy�
///
/// @param[in] profile : La struct contenant les informations n�cessaires.
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////
void NoeudRobot::loadProfile(std::shared_ptr<Profil> profile)
{
	currentProfile = *profile;
	behaviorContext_->changeBehavior(std::make_unique<DefaultBehavior>(behaviorContext_.get())); // Premier �tat selon le profil
}

////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	glRotatef(180, 0, 0, 1);

	// Affichage du mod�le.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();

	// Capteurs
	if (true /* Affichage de catpeurs activ�s */)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		afficherCapteurs();
		glDisable(GL_BLEND);
	}

	// Restauration de la matrice.
	glPopMatrix();
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
	glTranslatef(0.0, 0.0, 5.0);	// Pour bien les voir

	if (true /*currentProfile.centerDistanceSensor*/)
	{
		/// Affiche milieu zone danger
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(midSensorDanger_->coinMin.x, midSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMax.x, midSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMax.x, midSensorDanger_->coinMax.y, 0.0f);
		glVertex3f(midSensorDanger_->coinMin.x, midSensorDanger_->coinMax.y, 0.0f);
		glEnd();

		/// Affiche milieu zone s�curitaire
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(midSensorSafe_->coinMin.x, midSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMax.x, midSensorSafe_->coinMin.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMax.x, midSensorSafe_->coinMax.y, 0.0f);
		glVertex3f(midSensorSafe_->coinMin.x, midSensorSafe_->coinMax.y, 0.0f);
		glEnd();
	}

	if (true /*currentProfile.rightDistanceSensor*/)
	{
		/// Affiche droit zone danger
		glPushMatrix();
		glRotated(-45.0, 0.0, 0.0, 1.0);
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
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

	if (true /*currentProfile.leftDistanceSensor*/)
	{
		/// Affiche gauche zone danger
		glPushMatrix();
		glRotated(45.0, 0.0, 0.0, 1.0);
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(leftSensorDanger_->coinMin.x, leftSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMax.x, leftSensorDanger_->coinMin.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMax.x, leftSensorDanger_->coinMax.y, 0.0f);
		glVertex3f(leftSensorDanger_->coinMin.x, leftSensorDanger_->coinMax.y, 0.0f);
		glEnd();

		/// Affiche gauche zone s�curit�
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

	
	if (speed_ > 0.05f)
	{
		speed_ -= 3*acceleration_ / 4.0f; 
		positionRelative_.x += speed_ * std::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
		positionRelative_.y += speed_ * std::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
	}	
	else if (speed_ < -0.05f)
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
/// @fn void NoeudRobot::forward()
///
/// Cette fonction effectue un mouvement vers l'avant
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::forward()
{
	if (speed_ + acceleration_ < maxSpeed_)
		speed_ += acceleration_;
	else
		speed_ = maxSpeed_;

	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::reverse()
///
/// Cette fonction effectue un mouvement vers l'arriere
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::reverse()
{
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
	if (speed_ != 0)
		angleRotation_ += std::abs(1.0f * speed_ / maxSpeed_);
	else
		angleRotation_ += 1.0f;
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
	if (speed_ != 0)
		angleRotation_ -= std::abs(1.0f * speed_ / maxSpeed_);
	else
		angleRotation_ -= 1.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshLineFollowers()
///
/// � partir de la bo�te englobante et des transformations courantes,
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
	glm::dvec3 matriceScale({ 1.0, 1.0, 1.0 });//({ scale_.x, scale_.y, scale_.z }); 
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
	closeCenterLeft_ = { (farLeftLineFollower_.x + centerLineFollower_.x) / 20, hitbox.coinMax.y, hitbox.coinMin.z };
	closeCenterRight_ = { (farRightLineFollower_.x + centerLineFollower_.x) / 20, hitbox.coinMax.y, hitbox.coinMin.z };

	// Transformations courantes
	farLeftLineFollower_ = farLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	closeCenterLeft_ = closeCenterLeft_ * matriceRotation * matriceScale + matriceTranslation;
	closeCenterRight_ = closeCenterRight_ * matriceRotation * matriceScale + matriceTranslation;
	centerLineFollower_ = centerLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	farRightLineFollower_ = farRightLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	nearLeftLineFollower_ = nearLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
	nearRightLineFollower_ = nearRightLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::checkSensors()
///
/// V�rifie chacun de ses capteurs et donne les valeurs bool�ennes
/// n�cessaires.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::checkSensors()
{
	centerDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(centerLineFollower_);
	centerDetected_ = centerDetected_ || FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(closeCenterLeft_);
	centerDetected_ = centerDetected_ || FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(closeCenterRight_);
	farLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farLeftLineFollower_);
	farRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farRightLineFollower_);
	nearLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearLeftLineFollower_);
	nearRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearRightLineFollower_);

	return (centerDetected_ || nearLeftDetected_ || nearRightDetected_ || farLeftDetected_ || farRightDetected_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshCapteurDist()
///
/// � partir de la bo�te englobante et des transformations courantes,
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

	//PREMIER CAPTEUR DU MILIEU : Capteur se situe au milieu du robot 
	//(ZONE DANGER)
	coinMinMidDanger_ = { midPoint - 1.5, (hitboxRobot.coinMin.y), hitboxRobot.coinMin.z };
	coinMaxMidDanger_ = { midPoint + 1.5, hitboxRobot.coinMin.y /*- currentProfile.centerSensorDangerLenght */ - 5 /*lenght*/, hitboxRobot.coinMin.z };

	midSensorDanger_->coinMax = coinMaxMidDanger_;
	midSensorDanger_->coinMin = coinMinMidDanger_;

	//(ZONE SECURITE)
	coinMinMidSafe_ = { midPoint - 1.5, hitboxRobot.coinMin.y /*- currentProfile.centerSensorDangerLenght */ - 5.0 /*lenght danger*/, hitboxRobot.coinMin.z };
	coinMaxMidSafe_ = { midPoint + 1.5, (hitboxRobot.coinMin.y /*- currentProfile.centerSensorDangerLenght */ - 5.0 /*lenght danger*/ /*- currentProfile.centerSensorSafeLenght */ - 5.0 /*lenght secu*/), hitboxRobot.coinMin.z };
	
	midSensorSafe_->coinMax = coinMaxMidSafe_;
	midSensorSafe_->coinMin = coinMinMidSafe_;

	//DEUXIEME CAPTEUR : Capteur se situe sur le bout a droite
	//(ZONE DANGER)
	coinMinRightDanger_ = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y) + 4.0, hitboxRobot.coinMin.z };
	coinMaxRightDanger_ = { (hitboxRobot.coinMax.x + 1.5), (hitboxRobot.coinMin.y /*- currentProfile.rightSensorDangerLenght */ - 1.0), hitboxRobot.coinMin.z };
	
	rightSensorDanger_->coinMax = coinMaxRightDanger_;
	rightSensorDanger_->coinMin = coinMinRightDanger_;

	//(ZONE SECURITE)
	coinMinRightSafe_ = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y /*- currentProfile.rightSensorDangerLenght*/ - 1.0), hitboxRobot.coinMin.z };
	coinMaxRightSafe_ = { (hitboxRobot.coinMax.x + 1.5), (hitboxRobot.coinMin.y /*- currentProfile.rightSensorDangerLenght - currentProfile.rightSensorSafeLenght*/ - 6.0), hitboxRobot.coinMin.z };
	
	rightSensorSafe_->coinMax = coinMaxRightSafe_;
	rightSensorSafe_->coinMin = coinMinRightSafe_;

	//TROISIME CAPTEUR : Capteur se situe sur le bout a gauche
	//(ZONE DANGER)
	coinMinLeftDanger_ = { (hitboxRobot.coinMin.x - 1.5), (hitboxRobot.coinMin.y) + 4.0, hitboxRobot.coinMin.z };
	coinMaxLeftDanger_ = { (hitboxRobot.coinMin.x + 1.5), (hitboxRobot.coinMin.y /*- currentProfile.leftSensorDangerLenght*/ - 1.0), hitboxRobot.coinMin.z };

	leftSensorDanger_->coinMax = coinMaxLeftDanger_;
	leftSensorDanger_->coinMin = coinMinLeftDanger_;

	//(ZONE SECURITE)
	coinMinLeftSafe_ = { (hitboxRobot.coinMin.x - 1.5), hitboxRobot.coinMin.y /*- currentProfile.leftSensorDangerLenght*/ - 1.0, hitboxRobot.coinMin.z };
	coinMaxLeftSafe_ = { (hitboxRobot.coinMin.x + 1.5), hitboxRobot.coinMin.y /*- currentProfile.leftSensorDangerLenght - currentProfile.leftSensorSafeLenght*/ - 6.0, hitboxRobot.coinMin.z };
	
	leftSensorSafe_->coinMax = coinMaxLeftSafe_;
	leftSensorSafe_->coinMin = coinMinLeftSafe_;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshCapteurDist()
///
/// � partir de la bo�te englobante et des transformations courantes,
/// calcule et enregistre la position des capteurs.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::refreshSensorDist()
{
	// TODO IL RESTE LA ROTATION DES CAPTEURS DES COINS 
	// TODO DETECTION EN AVANT PAS EN ARRIERE

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
	{ glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), -glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), 0 },
	{ 0, 0, 1 });
	// Scale  ***Test sans le scale***
	glm::dvec3 matriceScale({ 0.6, 0.5, 1.0 });//({ scale_.x, scale_.y, scale_.z }); 
	// Translation
	glm::dvec3 matriceTranslation(
	{ positionRelative_.x, positionRelative_.y, positionRelative_.z });


	coinMaxMidDanger_= midSensorDanger_->coinMax * matriceRotation * matriceScale + matriceTranslation;
	coinMinMidDanger_ = midSensorDanger_->coinMin * matriceRotation * matriceScale + matriceTranslation;

	coinMaxMidSafe_ = midSensorSafe_->coinMax * matriceRotation * matriceScale + matriceTranslation;
	coinMinMidSafe_ = midSensorSafe_->coinMin * matriceRotation * matriceScale + matriceTranslation;

	coinMaxRightDanger_ = rightSensorDanger_->coinMax * matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	coinMinRightDanger_ = rightSensorDanger_->coinMin * matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;

	coinMaxRightSafe_ = rightSensorSafe_->coinMax * matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;
	coinMinRightSafe_ = rightSensorSafe_->coinMin * matriceRotationDroite * matriceRotation * matriceScale + matriceTranslation;

	coinMaxLeftDanger_ = leftSensorDanger_->coinMax * matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
	coinMinLeftDanger_ = leftSensorDanger_->coinMin * matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;

	coinMaxLeftSafe_ = leftSensorSafe_->coinMax * matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
	coinMinLeftSafe_ = leftSensorSafe_->coinMin * matriceRotationGauche * matriceRotation * matriceScale + matriceTranslation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::unique_ptr<Behavior> NoeudRobot::getBehavior(State stateEnum)
///
/// Prend un enum repr�sentant un �tat (provenant du C#) puis donne
/// le comportement associ�.
///
/// @param[in] stateEnum l'enum du Profil associ� au comportement d�sir�.
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
/// @fn void setHitbox()
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////