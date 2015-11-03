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
#include "FacadeModele.h"

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
	behaviorContext_ = std::make_unique<BehaviorContext>(this);
	behaviorContext_->changeBehavior(std::make_unique<FollowLine>(behaviorContext_.get())); // Premier état selon le profil
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
	glScalef(0.6f, 0.5f, 1.0f);

	glLineWidth(10.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(farLeftLineFollower_.x, farLeftLineFollower_.y, 3.0f);
	glVertex3f(nearLeftLineFollower_.x, nearLeftLineFollower_.y, 3.0f);
	glVertex3f(centerLineFollower_.x, centerLineFollower_.y, 3.0f);
	glVertex3f(nearRightLineFollower_.x, nearRightLineFollower_.y, 3.0f);
	glVertex3f(farRightLineFollower_.x, farRightLineFollower_.y, 3.0f);
	glEnd();

	// Affichage du modèle.
	if (selectionne_)
		vbo_->dessinerSelected();
	else
		vbo_->dessiner();
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
	refreshLineFollowers();

	if (checkSensors() && shouldFollow_)
	{
		behaviorContext_->changeBehavior(std::make_unique<FollowLine>(behaviorContext_.get()));
	}

	behaviorContext_->doAction();
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
		angleRotation_ += std::abs(0.3f * speed_ / maxSpeed_);
	else
		angleRotation_ += 0.7f;
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
		angleRotation_ -= std::abs(0.3f * speed_ / maxSpeed_);
	else
		angleRotation_ -= 0.7f;
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

	// Scale
	glm::dvec3 matriceScale({ scale_.x * 0.6f, scale_.y, scale_.z }); 
	// Translation
	glm::dvec3 matriceTranslation(
	{ positionRelative_.x, positionRelative_.y, positionRelative_.z });
	// Rotation
	glm::dmat3 matriceRotation(
	{ glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)),	-glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), 0 }, 
	{ glm::sin(utilitaire::DEG_TO_RAD(angleRotation_)), glm::cos(utilitaire::DEG_TO_RAD(angleRotation_)), 0 }, 
	{ 0, 0, 1 });

	// Suiveurs de lignes, sans les transformations courantes
	farLeftLineFollower_ = { hitbox.coinMin.x, hitbox.coinMax.y, hitbox.coinMin.z };
	centerLineFollower_ = { (hitbox.coinMin.x + hitbox.coinMax.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	farRightLineFollower_ = { hitbox.coinMax.x, hitbox.coinMax.y, hitbox.coinMin.z };
	nearLeftLineFollower_ = { (farLeftLineFollower_.x + centerLineFollower_.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	nearRightLineFollower_ = { (farRightLineFollower_.x + centerLineFollower_.x) / 2, hitbox.coinMax.y, hitbox.coinMin.z };
	
	// Transformations courantes
	farLeftLineFollower_ = farLeftLineFollower_ * matriceRotation * matriceScale + matriceTranslation;
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
	farLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farLeftLineFollower_);
	farRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(farRightLineFollower_);
	nearLeftDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearLeftLineFollower_);
	nearRightDetected_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->lineHit(nearRightLineFollower_);

	return (centerDetected_ || nearLeftDetected_ || nearRightDetected_);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::refreshCapteurDist()
///
/// À partir de la boîte englobante et des transformations courantes,
/// calcule et enregistre la position des suiveurs de ligne.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::refreshSensorDist()
{
	auto hitboxRobot = utilitaire::calculerBoiteEnglobante(*modele_);
	// point milieu du robot
	double midPoint = (hitboxRobot.coinMin.x + hitboxRobot.coinMax.x) / 2;
	// distance du bout a gauche selon les x
	double coinMinX= (hitboxRobot.coinMin.x + midPoint) / 2;
	// distance du bout a droite selon les y
	double coinMaxX = (hitboxRobot.coinMax.x + midPoint) / 2;
	//PREMIER CAPTEUR DU MILIEU : Capteur se situe au milieu du robot 
	//(ZONE DANGER)
	glm::dvec3 coinMin = { coinMinX, hitboxRobot.coinMax.y, hitboxRobot.coinMin.z };
	glm::dvec3 coinMax = { coinMaxX, (hitboxRobot.coinMax.y + 5.0), hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistDang1;
	midSensorDistDang1->coinMax = coinMax;
	midSensorDistDang1->coinMin = coinMin;

	//(ZONE SECURITE)
	glm::dvec3 coinMin1 = { coinMinX , hitboxRobot.coinMax.y + 5.0, hitboxRobot.coinMin.z };
	glm::dvec3 coinMax1 = { coinMaxX , (hitboxRobot.coinMax.y + 10.0), hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistSec1;
	midSensorDistSec1->coinMax = coinMax1;
	midSensorDistSec1->coinMin = coinMin1;

	//DEUXIEME CAPTEUR : Capteur se situe sur le bout a droite
	//(ZONE DANGER)
	glm::dvec3 coinMin2 = { (hitboxRobot.coinMax.x + coinMinX) , hitboxRobot.coinMax.y , hitboxRobot.coinMin.z };
	glm::dvec3 coinMax2 = { (hitboxRobot.coinMax.x + coinMaxX) , hitboxRobot.coinMax.y +5.0 , hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistDang2;
	midSensorDistDang2->coinMax = coinMax2;
	midSensorDistDang2->coinMin = coinMin2;
	
	//(ZONE SECURITE)
	glm::dvec3 coinMin3 = { (hitboxRobot.coinMax.x + coinMinX), hitboxRobot.coinMax.y +5.0 , hitboxRobot.coinMin.z };
	glm::dvec3 coinMax3 = { (hitboxRobot.coinMax.x + coinMaxX), hitboxRobot.coinMax.y +10.0, hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistSec2;
	midSensorDistSec2->coinMax = coinMax3;
	midSensorDistSec2->coinMin = coinMin3;

	//TROISIME CAPTEUR : Capteur se situe sur le bout a gauche
	//(ZONE DANGER)
	glm::dvec3 coinMin4 = { (hitboxRobot.coinMin.x + coinMinX), hitboxRobot.coinMax.y, hitboxRobot.coinMin.z };
	glm::dvec3 coinMax4 = { (hitboxRobot.coinMin.x + coinMaxX), hitboxRobot.coinMax.y + 5.0, hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistDang3;
	midSensorDistDang2->coinMax = coinMax4;
	midSensorDistDang2->coinMin = coinMin4;

	//(ZONE SECURITE)
	glm::dvec3 coinMin5 = { (hitboxRobot.coinMin.x + coinMinX), hitboxRobot.coinMax.y + 5.0, hitboxRobot.coinMin.z };
	glm::dvec3 coinMax5 = { (hitboxRobot.coinMin.x + coinMaxX), hitboxRobot.coinMax.y + 10.0, hitboxRobot.coinMin.z };
	utilitaire::BoiteEnglobante* midSensorDistSec3;
	midSensorDistSec2->coinMax = coinMax5;
	midSensorDistSec2->coinMin = coinMin5;


}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////