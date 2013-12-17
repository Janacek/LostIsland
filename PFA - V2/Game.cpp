#include "Player.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include "Game.h"

Game::Game(void) 
{
	
}

Game::~Game(void)
{
}

void Game::init()
{
	srand((unsigned int)time(NULL));
	Singleton& ptr1 = Singleton::getInstance();

	Map *map = NULL;
	std::list<IEntity *> _players;
	std::list<IEntity *> _entities;
	ptr1._clock = new sf::Clock();
	ptr1._clock->restart();

	this->_graphicEngine = new GraphicEngine(map, this->_states);
	this->_gameEngine = new GameEngine(map, this->_states);
	this->_physicEngine = new PhysicEngine(map, this->_states);
}


void Game::launch(void)
{
	

	while (42)
	{
		if (_graphicEngine->getIsRunning() == false)
			break;
		if (_gameEngine->getIsRunning() == false)
			break;
		//_graphicEngine->update(_players, _entities);
		_gameEngine->update(_players, _entities);
		_physicEngine->update(_players, _entities);
		
	}
}