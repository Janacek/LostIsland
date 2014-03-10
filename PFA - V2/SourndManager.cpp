#include "SoundManager.h"
#include "SystemDefines.h"

SoundManager		SoundManager::sounds = SoundManager();


SoundManager::SoundManager()
{
	this->bufferEffects[FIGHT].loadFromFile("");
	this->bufferEffects[STEPS].loadFromFile("./Media/sounds/sfx/steps.ogg");
	this->bufferEffects[DIE].loadFromFile("");
	this->bufferEffects[WIND].loadFromFile("");
	this->effects[FIGHT].setBuffer(this->bufferEffects[FIGHT]);
	this->effects[STEPS].setBuffer(this->bufferEffects[STEPS]);
	this->effects[DIE].setBuffer(this->bufferEffects[DIE]);
	this->effects[WIND].setBuffer(this->bufferEffects[WIND]);
}

SoundManager::~SoundManager()
{

}

std::map<soundType, sf::Sound>		&SoundManager::getSounds()
{
	return (this->effects);
}

SoundManager	&SoundManager::getSoundManager()
{
	return (sounds);
}

void			SoundManager::playMusic(const std::string &filename)
{
	if (!(this->music.openFromFile(filename)))
	{
		std::cout << "Enable to load music" << std::endl;
		return;
	}
	this->music.play();
}