#include "sound.h"

bool Sound::on = true; //is sound on?
bool Sound::possible = true; //is it possible to play sound?
char * Sound::currentSound; //currently played sound
//FMOD-specific stuff
FMOD_RESULT Sound::result;
FMOD_SYSTEM * Sound::fmodsystem;
FMOD_SOUND * Sound::sound1;
FMOD_SOUND * Sound::sound2;
FMOD_SOUND * Sound::sound3;
FMOD_SOUND * Sound::sound4;
FMOD_SOUND * Sound::sound5;
FMOD_SOUND * Sound::sound6;
FMOD_SOUND * Sound::sound7;
FMOD_SOUND * Sound::sound8;
FMOD_CHANNEL * Sound::channel;
FMOD_CHANNEL * Sound::channel2;
FMOD_CHANNEL * Sound::channel3;
FMOD_CHANNEL * Sound::channel4;

//initialises sound
void Sound::initialise(void) {
	//create the sound system. If fails, sound is set to impossible
	result = FMOD_System_Create(&fmodsystem);
	if (result != FMOD_OK) possible = false;
	//if initialise the sound system. If fails, sound is set to impossible
	if (possible) result = FMOD_System_Init(fmodsystem, 8, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) possible = false;
	//sets initial sound volume (mute)
	if (possible) FMOD_Channel_SetVolume(channel, 0.0f);
	FMOD_Channel_SetLoopCount(channel, 1);
}

//sets the actual playing sound's volume
void Sound::setVolume(float v) {
	if (possible && on && v >= 0.0f && v <= 1.0f) {
		FMOD_Channel_SetVolume(channel, v);
	}
}

//loads a soundfile
void Sound::load(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound1);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound1);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load2(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound2);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound2);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load3(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound3);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound3);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load4(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound4);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound4);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load5(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound5);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound5);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load6(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound6);
		result = FMOD_System_CreateStream(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound6);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load7(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound7);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound7);
		if (result != FMOD_OK) possible = false;
	}
}

//loads a soundfile
void Sound::load8(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound8);
		result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_SOFTWARE, 0, &sound8);
		if (result != FMOD_OK) possible = false;
	}
}

//frees the sound object
void Sound::unload(void) {
	/*if (possible) {
		result = FMOD_Sound_Release(sound7);
		result = FMOD_Sound_Release(sound8);
		result = FMOD_Sound_Release(sound6);
	}
	*/

	// Pause sur l'ensemble des channel
	FMOD_Channel_SetPaused(channel3, true);
	FMOD_Channel_SetPaused(channel4, true);
	FMOD_Channel_SetPaused(channel2, true);
	FMOD_Channel_SetPaused(channel, true);
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound1, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}
//plays a sound (no argument to leave pause as dafault)
void Sound::play2(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound2, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}
//plays a sound (no argument to leave pause as dafault)
void Sound::play3(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound3, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play4(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound4, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play5(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound5, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play6(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, sound6, pause, &channel2);
		FMOD_Channel_SetMode(channel2, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel2, 0.2f);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play7(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, sound7, pause, &channel3);
		FMOD_Channel_SetMode(channel3, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel3, 0.2f);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play8(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, sound8, pause, &channel4);
		FMOD_Channel_SetMode(channel4, FMOD_LOOP_NORMAL);
	}
}

//toggles sound on and off
void Sound::toggleSound(void) {
	on = !on;
	if (on == true) { load(currentSound); play(); }
	if (on == false) { unload(); }
}

//pause or unpause the sound
void Sound::setPause(int i, bool pause) {
	if (i==3)
		FMOD_Channel_SetPaused(channel3, pause);
	if (i==4)
		FMOD_Channel_SetPaused(channel4, pause);
}

//turn sound on or off
void Sound::setSound(bool s) {
	on = s;
}

//toggle pause on and off
void Sound::togglePause(void) {
	FMOD_BOOL p;
	FMOD_Channel_GetPaused(channel, &p);
	FMOD_Channel_SetPaused(channel, !p);
}

//tells whether the sound is on or off
bool Sound::getSound(void) {
	return on;
}
void Sound::initSimulation()
{
	load6("../Exe/media/sounds/Build/Desktop/world-map-1-grass-land.wav");
	play6();
	initRobot();
}

void Sound::initRobot()
{
	load("../Exe/media/sounds/Build/Desktop/Slap_sound_effect.mp3");
	load2("../Exe/media/sounds/Build/Desktop/explosion_very_small_pop.mp3");
	load3("../Exe/media/sounds/Build/Desktop/Kalimba.wav");
	load4("../Exe/media/sounds/Build/Desktop/mur_invisible.mp3");
	load5("../Exe/media/sounds/Build/Desktop/Kalimba_10.mp3");
	load7("../Exe/media/sounds/Build/Desktop/massdriver_buzzer.wav");
	load8("../Exe/media/sounds/Build/Desktop/bigmotor.wav");
	play7(true);
	play8(true);
}

void Sound::update()
{
	FMOD_System_Update(fmodsystem);
}
