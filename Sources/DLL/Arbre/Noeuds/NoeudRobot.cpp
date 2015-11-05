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

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "../../Application/Visitor/CollisionTool.h"
#include "../../Application/FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
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

	behaviorContext_ = std::make_unique<BehaviorContext>(this);

	manualMode_ = false;

	// Profil temporaire pour tests
	Profil placeholderProfile
	{
		State::followLine,		// onStartState
		State::searchLine,		// followLineNextState
		State::defaultBehavior,	// searchLineNextState
		State::followLine,		// deviationLeftNextState
		45.0f,					// deviationLeftAngle
		State::followLine,		// deviationRightNextState
		45.0f,					// deviationRightAngle
		State::followLine,		// avoidLeftNextState
		90.0f,					// avoidLeftAngle
		4.0,					// avoidLeftTime
		State::followLine,		// avoidRightNextState
		90.0f,					// avoidRightAngle
		4.0,					// avoidRightTime
		Capteur::inactif,		// leftDistanceSensor
		Capteur::inactif,		// rightDistanceSensor
		Capteur::inactif,		// centerDistanceSensor
		State::avoidRight,		// leftSensorDangerState
		State::deviationRight,	// leftSensorSafeState
		State::avoidLeft,		// rightSensorDangerState
		State::deviationLeft,	// rightSensorSafeState
		State::avoidLeft,		// centerSensorDangerState
		State::deviationLeft,	// centerSensorSafeState
		1.0,					// leftSensorSafeLenght
		1.0,					// leftSensorDangerLenght
		1.0,					// rightSensorSafeLenght
		1.0,					// rightSensorDangerLenght
		1.0,					// centerSensorSafeLenght
		1.0,					// centerSensorDangerLenght
		Capteur::actif			// capteurLigne
	};

	// La prochaine ligne est à enlever lorsque les profils seront liés au formulaire
	loadProfile(placeholderProfile);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::loadProfile(Profil profile)
///
/// Initialise/change les paramètres du robot selon le profil envoyé
///
/// @param[in] profile : La struct contenant les informations nécessaires.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::loadProfile(Profil profile)
{
	currentProfile = profile;
	behaviorContext_->changeBehavior(getBehavior(currentProfile.onStartState)); // Premier état selon le profil
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/// Affiche milieu zone danger
	glLineWidth(10.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(midSensorDistDang1_->coinMin.x, midSensorDistDang1_->coinMin.y, 10.0f);
	glVertex3f(midSensorDistDang1_->coinMax.x, midSensorDistDang1_->coinMin.y, 10.0f);
	glVertex3f(midSensorDistDang1_->coinMax.x, midSensorDistDang1_->coinMax.y, 10.0f);
	glVertex3f(midSensorDistDang1_->coinMin.x, midSensorDistDang1_->coinMax.y, 10.0f);
	glEnd();
	
	/// Affiche milieu zone sécuritaire
	glLineWidth(10.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(midSensorDistSec1_->coinMin.x, midSensorDistSec1_->coinMin.y, 10.0f);
	glVertex3f(midSensorDistSec1_->coinMax.x, midSensorDistSec1_->coinMin.y, 10.0f);
	glVertex3f(midSensorDistSec1_->coinMax.x, midSensorDistSec1_->coinMax.y, 10.0f);
	glVertex3f(midSensorDistSec1_->coinMin.x, midSensorDistSec1_->coinMax.y, 10.0f);
	glEnd();
	
	/// Affiche droit zone danger
	glPushMatrix();
	glRotated(-45.0, 0.0, 0.0, 1.0);
	glLineWidth(10.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(rightSensorDistDang2_->coinMin.x, rightSensorDistDang2_->coinMin.y, 10.0f);
	glVertex3f(rightSensorDistDang2_->coinMax.x, rightSensorDistDang2_->coinMin.y, 10.0f);
	glVertex3f(rightSensorDistDang2_->coinMax.x, rightSensorDistDang2_->coinMax.y, 10.0f);
	glVertex3f(rightSensorDistDang2_->coinMin.x, rightSensorDistDang2_->coinMax.y, 10.0f);
	glEnd();
	glPopMatrix();
	
	/// Affiche droit zone securitaire
	glPushMatrix();
	glRotated(-45.0, 0.0, 0.0, 1.0);
	glLineWidth(10.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(rightSensorDistSec2_->coinMin.x, rightSensorDistSec2_->coinMin.y, 10.0f);
	glVertex3f(rightSensorDistSec2_->coinMax.x, rightSensorDistSec2_->coinMin.y, 10.0f);
	glVertex3f(rightSensorDistSec2_->coinMax.x, rightSensorDistSec2_->coinMax.y, 10.0f);
	glVertex3f(rightSensorDistSec2_->coinMin.x, rightSensorDistSec2_->coinMax.y, 10.0f);
	glEnd();
	glPopMatrix();

	/// Affiche gauche zone danger
	glPushMatrix();
	glRotated(45.0, 0.0, 0.0, 1.0);
	glLineWidth(10.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(leftSensorDistDang3_->coinMin.x, leftSensorDistDang3_->coinMin.y, 10.0f);
	glVertex3f(leftSensorDistDang3_->coinMax.x, leftSensorDistDang3_->coinMin.y, 10.0f);
	glVertex3f(leftSensorDistDang3_->coinMax.x, leftSensorDistDang3_->coinMax.y, 10.0f);
	glVertex3f(leftSensorDistDang3_->coinMin.x, leftSensorDistDang3_->coinMax.y, 10.0f);
	glEnd();

	/// Affiche gauche zone sécurité
	glLineWidth(10.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(leftSensorDistSec3_->coinMin.x, leftSensorDistSec3_->coinMin.y, 10.0f);
	glVertex3f(leftSensorDistSec3_->coinMax.x, leftSensorDistSec3_->coinMin.y, 10.0f);
	glVertex3f(leftSensorDistSec3_->coinMax.x, leftSensorDistSec3_->coinMax.y, 10.0f);
	glVertex3f(leftSensorDistSec3_->coinMin.x, leftSensorDistSec3_->coinMax.y, 10.0f);
	glEnd();
	glPopMatrix();

	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
	glDisable(GL_BLEND);
	glLineWidth(1.0f);
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////
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
	if (speed_ < maxSpeed_)
	{
		speed_ += acceleration_;
	}

	positionRelative_.x += speed_ * std::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
	positionRelative_.y += speed_ * std::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));

	auto collision = CollisionTool(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accept(collision);
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
	if (speed_ > -maxSpeed_)
	{
		speed_ -= acceleration_;
	}

	positionRelative_.x += speed_ * std::cos(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
	positionRelative_.y += speed_ * std::sin(utilitaire::DEG_TO_RAD(angleRotation_ + 90.0f));
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
	auto hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	// Scalen  ***Test sans le scale***
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
	// TODO IL RESTE LA ROTATION DES CAPTEURS DES COINS 
	// TODO DETECTION EN AVANT PAS EN ARRIERE

	auto hitboxRobot = utilitaire::calculerBoiteEnglobante(*modele_);
	// point milieu du robot
	double midPoint = (hitboxRobot.coinMin.x + hitboxRobot.coinMax.x) / 2;
	// distance du bout a gauche selon les x
	double coinMinX= (hitboxRobot.coinMin.x + midPoint) / 2;
	// distance du bout a droite selon les y
	double coinMaxX = (hitboxRobot.coinMax.x + midPoint) / 2;

	// matrice rotation vers la droite POUR L'INSTANT ELLE FONT RIEN
	glm::dmat3 matriceRotationDroite(
	{ glm::cos(utilitaire::DEG_TO_RAD(-45.0)) , -glm::sin(utilitaire::DEG_TO_RAD(-45.0)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(-45.0)), glm::cos(utilitaire::DEG_TO_RAD(-45.0)), 0 },
	{ 0, 0, 1 });

	// matrice rotation vers la gauche
	glm::dmat3 matriceRotationGauche(
	{ glm::cos(utilitaire::DEG_TO_RAD(90.0)), -glm::sin(utilitaire::DEG_TO_RAD(90.0)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(90.0)), glm::cos(utilitaire::DEG_TO_RAD(90.0)), 0 },
	{ 0, 0, 1 });

	// Scalen  ***Test sans le scale***
	glm::dvec3 matriceScale({ 1.0, 1.0, 1.0 });//({ scale_.x, scale_.y, scale_.z }); 
	// Translation
	glm::dvec3 matriceTranslation(
	{ positionRelative_.x, positionRelative_.y, positionRelative_.z });

	//PREMIER CAPTEUR DU MILIEU : Capteur se situe au milieu du robot 
	//(ZONE DANGER)
	coinMin_ = { midPoint- 1.5, (hitboxRobot.coinMin.y - 5.0), hitboxRobot.coinMin.z };
	coinMax_ = { midPoint+ 1.5, hitboxRobot.coinMin.y , hitboxRobot.coinMin.z };

	midSensorDistDang1_->coinMax = coinMax_;
	midSensorDistDang1_->coinMin = coinMin_;

	//(ZONE SECURITE)
	coinMin1_ = { midPoint -1.5, hitboxRobot.coinMin.y - 10.0, hitboxRobot.coinMin.z };
	coinMax1_ = { midPoint + 1.5, (hitboxRobot.coinMin.y - 5.0), hitboxRobot.coinMin.z };
	
	midSensorDistSec1_->coinMax = coinMax1_;
	midSensorDistSec1_->coinMin = coinMin1_;

	//coinMax1_ = coinMax1_* matriceRotationGauche * matriceScale + matriceTranslation;
	//coinMin_ = coinMin1_* matriceRotationGauche * matriceScale + matriceTranslation;

	//DEUXIEME CAPTEUR : Capteur se situe sur le bout a droite
	//(ZONE DANGER)
	coinMin2_ = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y - 5.0), hitboxRobot.coinMin.z };
	coinMax2_ = { (hitboxRobot.coinMax.x + 1.5) , (hitboxRobot.coinMin.y + 4.0) , hitboxRobot.coinMin.z };
	
	rightSensorDistDang2_->coinMax = coinMax2_;
	rightSensorDistDang2_->coinMin = coinMin2_;

	//(ZONE SECURITE)
	coinMin3_ = { (hitboxRobot.coinMax.x - 1.5), (hitboxRobot.coinMin.y - 10.0) , hitboxRobot.coinMin.z };
	coinMax3_ = { (hitboxRobot.coinMax.x + 1.5), (hitboxRobot.coinMin.y - 5.0), hitboxRobot.coinMin.z };
	
	rightSensorDistSec2_->coinMax = coinMax3_;
	rightSensorDistSec2_->coinMin = coinMin3_;

	//TROISIME CAPTEUR : Capteur se situe sur le bout a gauche
	//(ZONE DANGER)
	coinMin4_ = { (hitboxRobot.coinMin.x - 1.5), (hitboxRobot.coinMin.y - 5.0), hitboxRobot.coinMin.z };
	coinMax4_ = { (hitboxRobot.coinMin.x + 1.5), (hitboxRobot.coinMin.y + 4.0), hitboxRobot.coinMin.z };

	leftSensorDistDang3_->coinMax = coinMax4_;
	leftSensorDistDang3_->coinMin = coinMin4_;

	//(ZONE SECURITE)
	coinMin5_ = { (hitboxRobot.coinMin.x - 1.5), hitboxRobot.coinMin.y - 10.0, hitboxRobot.coinMin.z };
	coinMax5_ = { (hitboxRobot.coinMin.x + 1.5), hitboxRobot.coinMin.y - 5.0, hitboxRobot.coinMin.z };
	
	leftSensorDistSec3_->coinMax = coinMax5_;
	leftSensorDistSec3_->coinMin = coinMin5_;

}
void  NoeudRobot::hitBoxRobot()
{	
	auto hitBoxRobot = utilitaire::calculerBoiteEnglobante(*modele_);
	hitBoxCoinMaxX_ = hitBoxRobot.coinMax.x;
	hitBoxCoinMinX_ = hitBoxRobot.coinMin.x;
	// Ah oui! sur l'ax des Y c'est inversé ... à cause de rotate 180
	hitBoxCoinMaxY_ = hitBoxRobot.coinMin.y;
	hitBoxCoinMinY_ = hitBoxRobot.coinMax.y;
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////