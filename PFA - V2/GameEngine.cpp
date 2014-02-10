#include "GameEngine.h"
#include "StartScreen.h"
#include "Singleton.h"
#include "GameScreen.h"

GameEngine::GameEngine(std::stack<IScreen *>&states) : _states(states)
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	_isRunning = true;
}

void GameEngine::update()
{
	sf::Event	event;

	// OPENGL COULD THROW WARNINGS HERE.

	//std::cout << _states.size() << std::endl;
	if (_states.top()->isRunning() == false)
	{
		IScreen *tmp = _states.top()->getNextState();
		if (!_states.empty())
			PopState();
		PushState(tmp);
		Singleton::getInstance().isEscapePressed = false;
		//if (state)
		//{
		//	std::cout << "toto1" << std::endl;
		//	//state->initialize();
		//}
	}
	IScreen *state = _states.top();
	if (state)
	{
		while (Singleton::getInstance()._window->pollEvent(event))
		{
			state->events(event);
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				_controler.handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				_controler.handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				Singleton::getInstance()._window->close();
				_isRunning = false;
				return;
				break;
			case sf::Event::MouseButtonReleased:
				_controler.handlePlayerInput(event.mouseButton.button, false);
				break;
			case sf::Event::MouseButtonPressed:
				_controler.handlePlayerInput(event.mouseButton.button, true);
				break;
			}
		}
		state->update();
	}
}

bool GameEngine::getIsRunning() const
{
	return _isRunning;
}

void GameEngine::PushState(IScreen *state)
{
	_states.push(state);
	_states.top()->initialize();


}	

void GameEngine::SetState(IScreen* state)
{
	PopState();

	// Add the new state
	PushState(state);
}

void GameEngine::PopState(void)
{
	if (!_states.empty())
	{
		IScreen *tmp = _states.top();
		_states.pop();
		std::cout << "On delete" << std::endl;
		//delete tmp;
	}
}