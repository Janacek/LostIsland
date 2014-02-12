#include "SoundManager.h"

SoundManager		SoundManager::sounds = SoundManager();


SoundManager::SoundManager()
{
	this->bufferEffects[FIGHT].loadFromFile("");
	this->bufferEffects[STEPS].loadFromFile("");
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

SoundManager	&SoundManager::getSoundManager() const
{
	return (this->sounds);
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