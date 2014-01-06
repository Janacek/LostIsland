#include "GameEngine.h"
#include "StartScreen.h"
#include "Singleton.h"

GameEngine::GameEngine(std::stack<IScreen *>&states) : _states(states)
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

void GameEngine::update(std::vector<IEntity *> &players, std::list<IEntity *> &entities)
{
	sf::Event	event;

	// OPENGL COULD THROW WARNINGS HERE.
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
				exit(42);
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

	if (_states.top()->isRunning() == false)
	{
		PushState(_states.top()->getNextState());
	}
	_gameEvents->update(players, entities);
	IScreen *state = _states.top();
	if (state)
		state->update();
	
}

bool GameEngine::getIsRunning() const
{
	return _isRunning;
}

void GameEngine::PushState(IScreen *state)
{
	_states.push( state );
	_states.top()->initialize();
}

void GameEngine::SetState(IScreen* state)
{
	PopState ();

	// Add the new state
	PushState(state);
}

void GameEngine::PopState(void)
{
	if ( !_states.empty() )
	{
		_states.top()->release();
		_states.pop();
	}
}