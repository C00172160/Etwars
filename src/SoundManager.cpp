




#include "SoundManager.h"


SoundManager::SoundManager()
{

}

void SoundManager::init(bool playBGM)
{

	//setup FMOD
	result = FMOD::System_Create(&FMODsys);     // Create the main system object.

	prop1 = FMOD_PRESET_AUDITORIUM;
	//      FMODsys->setReverbAmbientProperties(&prop1);

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

////////////////////////////////////////////////////////BACKGROUND SETUP ////////////////////////////////////////////////////////////////////////////////
	if (playBGM == true)
	{
		result = FMODsys->createStream("Resources/song.mp3", FMOD_LOOP_NORMAL, 0, &BackgroundMusic);

		FMODsys->playSound(
			FMOD_CHANNEL_FREE,
			BackgroundMusic,
			true,
			&Backgroundchannel);
		Backgroundchannel->setVolume(0.5f);       // Set the volume while it is paused.
		Backgroundchannel->setPaused(false);
	}
///////////////////////////////////////////////////////////WAVE SOUND SETUP///////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////TEST SETUP ////////////////////////////////////////////////////////////////////////////////
	result = FMODsys->createSound("Resources/test.wav", FMOD_LOOP_NORMAL | FMOD_3D, 0, &TestSound);


	TestChannel = 0;
	volume = 0.5f;
	FMODsys->playSound(
		FMOD_CHANNEL_FREE,
		TestSound,
		true,
		&TestChannel);
	// Set the volume while it is paused.
	TestChannel->setPaused(true);
	result = TestChannel->setVolume(volume);
	//need this for sound fall off
	TestChannel->set3DMinMaxDistance(50, 1000);
	TestChannel->set3DDopplerLevel(1000);
	TestPos = {1000, 0, 0};

	///////////////////////////////////////////////////////////////////// ////////////////////////////////////////////////////////////////////////////////
	
	
	result = FMODsys->createStream("Resources/gun.mp3", FMOD_DEFAULT | FMOD_3D, 0, &fireSound);
	result = FMODsys->createStream("Resources/explosion.mp3", FMOD_DEFAULT | FMOD_3D, 0, &explosionSound);

	////////////////////////////////////////////////////////REVERB SETUP ////////////////////////////////////////////////////////////////////////////////
			reverbpos = sf::Vector2f(1000, 300);
			reverbActive = true;
			result = FMODsys->createReverb(&reverb);
			FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
		
			reverb->setProperties(&prop);
			reverbPosition = {reverbpos.x, reverbpos.y, 0 };
			 mindistance = 100.0f;
			 maxdistance = 300.0f;
			
		

}

void SoundManager::playFireSound(){

	FMODsys->playSound(FMOD_CHANNEL_FREE, fireSound, false, &fireChannel);


}
void SoundManager::playExplosionSound(sf::Vector2f rocketpos){

	explosionChannel = 0;
	volume = 3.5f;
	FMODsys->playSound(FMOD_CHANNEL_FREE,explosionSound,true,&explosionChannel);
	explosionChannel->setPaused(false);
	result = explosionChannel->setVolume(volume);
	explosionChannel->set3DMinMaxDistance(100, 1000);
	explosionChannel->set3DDopplerLevel(0);
	rocketPosition = { rocketpos.x, 0.0f, rocketpos.y };
}




void SoundManager::update(sf::Vector2f playerpos, sf::Vector2f playervel, sf::Vector2f sourcepos)
{

	playerVelocity = { playervel.x, 0.0f, playervel.y };
	playerPos = { playerpos.x, 0.0, playerpos.y };
	FMODsys->set3DListenerAttributes(0, &playerPos, &playerVelocity, 0, 0);

	//update position of sound
	if (WaveChannel){
		sourcePos = { sourcepos.x, 0.0f, sourcepos.y };
		//source is fixed so velocity is zero
		WaveChannel->set3DAttributes(&sourcePos, 0);
	}
	if (explosionChannel){

		explosionChannel->set3DAttributes(&rocketPosition, 0);

	}
	if (TestChannel){

		TestChannel->set3DAttributes(&TestPos, 0);

	}
	
	reverb->set3DAttributes(&reverbPosition, mindistance, maxdistance);
	reverb->setActive(reverbActive);

	FMODsys->update();

}


sf::Vector2f SoundManager::getReverbPosition()
{

	return reverbpos;
}
bool SoundManager::getReverbActive()
{
	return reverbActive;
}
void SoundManager::pauseBackground(bool toggle)
{
	Backgroundchannel->setPaused(toggle);
}
void SoundManager::stopAll()
{
	Backgroundchannel->stop();
	fireChannel->stop();
	RocketChannel->stop();
	WaveChannel->stop();
	TestChannel->stop();
}
void  SoundManager::ToggleReverb(bool toggle)
{
	reverbActive = toggle;
	
}
void  SoundManager::pauseWave(bool toggle)
{
	WaveChannel->setPaused(toggle);

}
void  SoundManager::ToggleTest(bool toggle)
{
	TestChannel->setPaused(toggle);
}
void SoundManager::ToggleDoppler(int level)
{
		TestChannel->set3DDopplerLevel(level);	
}

