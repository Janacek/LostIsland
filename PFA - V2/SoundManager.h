#pragma once

#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

class SoundManager
{
	enum soundType
	{
		FIGHT,
		STEPS,
		DIE,
		WIND,
	};
public:
	SoundManager();
	~SoundManager();
	SoundManager		&getSoundManager() const;
	void				playMusic(const std::string &filename);
private:
	static SoundManager	sounds;
	sf::SoundBuffer		bufferEffects[4];
	sf::Sound			effects[4];
	sf::Music			music;
};
