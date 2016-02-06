
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
	void updateRocketSound(sf::Vector2f RocketPos);
	void PlayRocket(bool toggle);
	void StopRocket();
	void UpdateReverb();
	void playExplosionSound(sf::Vector2f rocketPos);
	void playFireSound();
	bool getReverbActive();
	void ToggleReverb(bool toggle);
	void pauseBackground(bool toggle);
	void pauseWave(bool toggle);
	void ToggleTest(bool toggle);
	void ToggleDoppler(int level);
	void PauseTest(bool  toggle);

	sf::Vector2f getReverbPosition();

private:
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD::Sound *BackgroundMusic;
	FMOD::Sound *RocketSound;
	FMOD::Channel *RocketChannel;
	FMOD::Sound *WaveSound;
	FMOD::Channel *WaveChannel;
	FMOD::Sound *TestSound;
	FMOD::Channel *TestChannel;
	FMOD::Channel *Backgroundchannel;
	FMOD_VECTOR  playerVelocity;
	FMOD_VECTOR  playerPos;
	FMOD_VECTOR  sourcePos;
	FMOD_VECTOR  sourceVel;
	FMOD::Sound *fireSound;
	FMOD::Channel *fireChannel;
	FMOD_VECTOR reverbPosition;
	FMOD::Sound *explosionSound;
	FMOD::Channel *explosionChannel;
	FMOD_VECTOR rocketPosition;
	FMOD_VECTOR TestPos;

	
	float mindistance;
	float maxdistance;
	FMOD_REVERB_PROPERTIES prop1;
	FMOD::Reverb *reverb;
	FMOD_VECTOR pos;
	sf::Vector2f reverbpos;
	float volume;
	bool reverbActive;

};

#endif