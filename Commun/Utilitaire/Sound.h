/*
/  Source: http://www.roguebasin.com/index.php?title=Implementing_sound_in_C_and_C_Plus_Plus
*/
#pragma once

#include "fmod.h" //FMOD Ex

class Sound {
	private:
		static bool on; //is sound on?
		static bool possible; //is it possible to play sound?
		static char * currentSound; //currently played sound
		//FMOD-specific stuff
		static FMOD_RESULT result;
		static FMOD_SYSTEM * fmodsystem;
		static FMOD_SOUND * sound1;
		static FMOD_SOUND * sound2;
		static FMOD_SOUND * sound3;
		static FMOD_SOUND * sound4;
		static FMOD_SOUND * sound5;
		static FMOD_SOUND * sound6;
		static FMOD_CHANNEL * channel;
		static FMOD_CHANNEL * channel2;
		//static FMOD_CHANNEL * channel2;

	public:
		static void initialise(void); //initialises sound

		//sound control
		static void setVolume(float v); //sets the actual playing sound's volume
		static void load(const char * filename); //loads a soundfile
		static void load2(const char * filename); //loads a soundfile
		static void load3(const char * filename); //loads a soundfile
		static void load4(const char * filename); //loads a soundfile
		static void load5(const char * filename); //loads a soundfile
		static void load6(const char * filename); //loads a soundfile
		static void unload(void); //frees the sound object
		static void play(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play2(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play3(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play4(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play5(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play6(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)

		//getters
		static bool getSound(void); //checks whether the sound is on

		//setters
		static void setPause(bool pause); //pause or unpause the sound
		static void setSound(bool sound); //set the sound on or off

		//toggles
		static void toggleSound(void); //toggles sound on and off
		static void togglePause(void); //toggle pause on/off

		static void initRobot();
		static void update();
};