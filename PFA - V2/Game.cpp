#include "Player.h"
#include "Singleton.h"
#include "Game.h"

Game::Game(void) 
{
	_graphicEngine = new GraphicEngine();
	_gameEngine = new GameEngine();
	_physicEngine = new PhysicEngine();
}

Game::~Game(void)
{
}

void Game::launch(void)
{
	srand(time(NULL));
	sf::Time t;
	Singleton& ptr1 = Singleton::getInstance();
	std::list<IEntity *> _players;
	std::list<IEntity *> _entities;
	Map *_map = new Map(); // TODO Map est bidon pour le moment, envoyer un mail a mart_u@epitech.eu pour des éventuels problèmes avec cette classe
	ptr1._clock = new sf::Clock();
	ptr1._clock->restart();
	_gameEngine->init(_map);
	_physicEngine->init(_map);
	_graphicEngine->init(_map);
	IEntity *player = new Player();
	//set les attributs du player
	_players.push_back(player);
	while (42)
	{
		if (_graphicEngine->getIsRunning() == false)
			break;
		if (_gameEngine->getIsRunning() == false)
			break;
		_graphicEngine->update(_players, _entities);
		_gameEngine->update(_players, _entities);
		_physicEngine->update(_players, _entities);
		
	}
}