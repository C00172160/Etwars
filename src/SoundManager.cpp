

#include "SoundManager.h"


SoundManager::SoundManager()
{
	init();
}

void SoundManager::init()
{
	//setup FMOD
	result = FMOD::System_Create(&FMODsys);     // Create the main system object.

    prop1 = FMOD_PRESET_AUDITORIUM;
//	FMODsys->setReverbAmbientProperties(&prop1);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
		exit(-1);
	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
		exit(-1);
	}
	result = FMODsys->createStream("Resources/song.mp3", FMOD_LOOP_NORMAL, 0, &BackgroundMusic);

	FMODsys->playSound(
		FMOD_CHANNEL_FREE,
		BackgroundMusic,
		true,
		&Backgroundchannel);
	    Backgroundchannel->setVolume(0.5f);       // Set the volume while it is paused.
	    Backgroundchannel->setPaused(false);

		result = FMODsys->createSound("Resources/wave.mp3", FMOD_LOOP_NORMAL | FMOD_3D, 0, &WaveSound);


		WaveChannel = 0;
		volume = 0.5f;
		FMODsys->playSound(
			FMOD_CHANNEL_FREE,
			WaveSound,
			true,
			&WaveChannel);
		// Set the volume while it is paused.
		WaveChannel->setPaused(false);
		result = WaveChannel->setVolume(volume);
		//need this for sound fall off
		WaveChannel->set3DMinMaxDistance(50, 10000);
		WaveChannel->set3DDopplerLevel(0);


		result = FMODsys->createStream("Resources/rocket.wav", FMOD_LOOP_NORMAL | FMOD_3D, 0, &RocketSound);
		result = FMODsys->createStream("Resources/gun.mp3", FMOD_DEFAULT, 0, &fireSound);


		result = FMODsys->createReverb(&reverb);
		reverb->setProperties(&prop1);
		reverbpos = {100, 0, 100 };
		float mindist = 1000.0f;
		float maxdist = 1500.0f;
		reverb->set3DAttributes(&reverbpos, mindist, maxdist);

		reverb->setActive(true);
	
}
void SoundManager::playFireSound(){

	FMODsys->playSound(FMOD_CHANNEL_FREE, fireSound, false, &fireChannel);

}

void SoundManager::UpdateReverb()
{

}
//void SoundManager::PlayRocket()
//{
//	RocketChannel = 0;
//	volume = 0.9f;
//
//	FMODsys->playSound(
//		FMOD_CHANNEL_FREE,
//		RocketSound,
//		true,
//		&RocketChannel);
//
//	RocketChannel->setVolume(1.0f);       // Set the volume while it is paused.
//	RocketChannel->setPaused(false);
//
//	result = RocketChannel->setVolume(volume);
//	//need this for sound fall off
//	RocketChannel->set3DMinMaxDistance(50, 1000);
//	
//}
//void SoundManager::StopRocket()
//{
//	RocketSound->release();
//}

//void SoundManager::updatRocketSound(sf::Vector2f playerpos, sf::Vector2f playervel, sf::Vector2f sourcepos)
//{
//	playerVelocity = { playervel.x, 0.0f, playervel.y };
//	//update position & velocity of listener
//	//position of listener needed for spatial & reverb effects
//	//velocity of listener needed for dopper effects
//	FMOD_VECTOR  playerPos = { playerpos.x, 0.0f, playerpos.y };
//	//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
//	FMODsys->set3DListenerAttributes(0, &playerPos, &playerVelocity, 0, 0);
//
//	//update position of sound
//	if (RocketChannel){
//		sourcePos = { sourcepos.x, 0.0f, sourcepos.y };
//		
//		//source is fixed so velocity is zero
//		RocketChannel->set3DAttributes(&sourcePos, 0);
//	}
//	
//}

void SoundManager::update(sf::Vector2f playerpos, sf::Vector2f playervel, sf::Vector2f sourcepos)
{


		playerVelocity = { playervel.x, 0.0f, playervel.y };
		//update position & velocity of listener
		//position of listener needed for spatial & reverb effects
		//velocity of listener needed for dopper effects
		FMOD_VECTOR  playerPos = { playerpos.x, 0.0f, playerpos.y };
		//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
		FMODsys->set3DListenerAttributes(0, &playerPos, &playerVelocity, 0, 0);

		//update position of sound
		if (WaveChannel){
			sourcePos = { sourcepos.x, 0.0f, sourcepos.y };
			//source is fixed so velocity is zero
			WaveChannel->set3DAttributes(&sourcePos, 0);
		}
	
	FMODsys->update();

}

