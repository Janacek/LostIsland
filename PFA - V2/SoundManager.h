#pragma once

#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>



enum soundType
{
	FIGHT,
	STEPS,
	DIE,
	WIND,
};

class SoundManager
{
	
public:
	SoundManager();
	~SoundManager();
	static SoundManager		&getSoundManager();
	void				playMusic(const std::string &filename);
	std::map<soundType, sf::Sound>			&getSounds();
private:
	static SoundManager	sounds;
	std::map<soundType, sf::SoundBuffer>		bufferEffects;
	std::map<soundType, sf::Sound>				effects;
	sf::Music			music;
};

