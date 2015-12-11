
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#pragma comment(lib,"fmodex_vc.lib")

#include "fmod.hpp"
#include <iostream>
#include "fmod_errors.h"
#include "SFML\Graphics.hpp"


class SoundManager {

public:
	SoundManager();
	void init();
	void update(sf::Vector2f playerpos, sf::Vector2f playervel, sf::Vector2f sourcepos);
	void updatRocketSound(sf::Vector2f playerpos, sf::Vector2f playervel, sf::Vector2f sourcepos);
	void PlayRocket();
	void StopRocket();

private:
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD::Sound *BackgroundMusic;
	FMOD::Sound *RocketSound;
	FMOD::Channel *RocketChannel;
	FMOD::Sound *WaveSound;
	FMOD::Channel *WaveChannel;
	FMOD::Channel *Backgroundchannel;
	FMOD_VECTOR  playerVelocity;
	FMOD_VECTOR  playerPos;
	FMOD_VECTOR  sourcePos;
	FMOD_VECTOR  sourceVel;

	float volume;

};

#endif