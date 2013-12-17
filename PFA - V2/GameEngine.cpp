#include "GameEngine.h"
#include "Singleton.h"

GameEngine::GameEngine(Map *&map, std::stack<IScreen *>&states) : _map(map), _states(states)
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	_gameEvents = new GameEvents();
	_isRunning = true;
}

void GameEngine::update(std::list<IEntity *> players, std::list<IEntity *> entities)
{
	sf::Event	event;
	while (Singleton::getInstance()._window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				_controler.handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				_controler.handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed :
				Singleton::getInstance()._window->close();
				_isRunning = false;
				break;
			case sf::Event::MouseButtonReleased :
				_controler.handlePlayerInput(event.mouseButton.button, false);
				break;
			case sf::Event::MouseButtonPressed :
				_controler.handlePlayerInput(event.mouseButton.button, true);
				break;
		}
		if (event.key.code == sf::Keyboard::Escape)
		{
			_isRunning = false;
			break;
		}
	}
	_gameEvents->update(players, entities, _map);
}

bool GameEngine::getIsRunning() const
{
	return _isRunning;
}
