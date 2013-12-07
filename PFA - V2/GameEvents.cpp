#include "GameEvents.h"

GameEvents::GameEvents()
{
	_timeElapsed = sf::Time::Zero;
}

void	GameEvents::init()
{
	_timeElapsed = sf::Time::Zero;
	
}


void GameEvents::update(std::list<IEntity *> players, std::list<IEntity *> entities, Map * map)
{
	// ON CHANGE LES POSITION ICI
}