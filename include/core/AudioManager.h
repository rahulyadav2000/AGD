#pragma once
#include "SFML/Audio.hpp"
#include <iostream>

class AudioManager {
public:
	~AudioManager();

	void PlayPotionSound();

	void PlayFireSound();

	void PlayAxeSound();

private:
	sf::SoundBuffer potionBuffer;
	sf::SoundBuffer axeBuffer;
	sf::SoundBuffer fireballBuffer;

	sf::Sound potionSound;
	sf::Sound axeSound;
	sf::Sound fireballSound;
};

class Locator {
public:
	static AudioManager& getAudioManager()
	{
		static AudioManager instance;
		return instance;
	}
};