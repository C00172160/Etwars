

#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}

void SoundManager::init()
{
	result = FMOD::System_Create(&FMODsys);         // Create the main system object

	if (result != FMOD_OK)

	{

		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);

		exit(-1);

	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);
		exit(-1);
	}

	
	result = FMODsys->createSound("Resources/song.mp3", FMOD_DEFAULT, 0, &sound);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);

	}
	
	FMODsys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);

}
void SoundManager::update()
{
	FMODsys->update();
}
