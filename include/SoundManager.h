
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#pragma comment(lib,"fmodex_vc.lib")

#include "fmod.hpp"
#include <iostream>
#include "fmod_errors.h"


class SoundManager {

public:
	SoundManager();
	void init();
	void update();

private:
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD::Sound *sound;
	FMOD::Channel *channel;

};

#endif