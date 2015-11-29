/*
/  Source: http://www.roguebasin.com/index.php?title=Implementing_sound_in_C_and_C_Plus_Plus
*/
#pragma once

#include "../Externe/FMOD/Include/fmod.h" //FMOD Ex

class Sound {
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
		static void load7(const char * filename); //loads a soundfile
		static void load8(const char * filename); //loads a soundfile

		static void unload(void); //frees the sound object

		static void play(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play2(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play3(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play4(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play5(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play6(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play7(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)
		static void play8(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)

		//getters
		static bool getSound(void); //checks whether the sound is on

		//setters
		static void setPause(int i, bool pause); //pause or unpause the sound
		static void setSound(bool sound); //set the sound on or off

		//toggles
		static void toggleSound(void); //toggles sound on and off
		static void togglePause(void); //toggle pause on/off

		static void initSimulation();
		static void initRobot();
		static void update();

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
		static FMOD_SOUND * sound7;
		static FMOD_SOUND * sound8;
		static FMOD_CHANNEL * channel;
		static FMOD_CHANNEL * channel2;
		static FMOD_CHANNEL * channel3;
		static FMOD_CHANNEL * channel4;
};