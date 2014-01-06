#include "GameEvents.h"

GameEvents::GameEvents()
{
	_timeElapsed = sf::Time::Zero;
}

void	GameEvents::init()
{
	_timeElapsed = sf::Time::Zero;
	
}


void GameEvents::update(std::vector<IEntity *> &players, std::list<IEntity *> &entities)
{
	// ON CHANGE LES POSITION ICI
}