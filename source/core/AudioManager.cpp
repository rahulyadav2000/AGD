#include "../../include/core/AudioManager.h"

AudioManager::~AudioManager() {};

void AudioManager::PlayPotionSound()
{
	if (!potionBuffer.loadFromFile("audio/potion.wav"))  // Link of the potion sound: https://freesound.org/people/ValentinPetiteau/sounds/574077/
	{
		std::cout << "Error in playing sound!!" << std::endl;
	}
	potionSound.setBuffer(potionBuffer);
	potionSound.play();
}

void AudioManager::PlayFireSound()
{
	if (!fireballBuffer.loadFromFile("audio/fireball.wav")) // Link of the fireball sound: https://freesound.org/people/Julien%20Matthey/sounds/105016/
	{
		std::cout << "Error in playing sound!!" << std::endl;
	}
	fireballSound.setBuffer(fireballBuffer);
	fireballSound.play();
}

void AudioManager::PlayAxeSound()
{
	if (!axeBuffer.loadFromFile("audio/axe.wav"))	// Link of the axe sound: https://freesound.org/people/smokebomb99/sounds/147289/
	{
		std::cout << "Error in playing sound!!" << std::endl;
	}
	axeSound.setBuffer(axeBuffer);
	axeSound.play();
}