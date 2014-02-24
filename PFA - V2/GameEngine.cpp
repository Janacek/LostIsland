#include "GameEngine.h"
#include "StartScreen.h"
#include "Singleton.h"
#include "GameScreen.h"

GameEngine::GameEngine(std::list<IScreen *>&states) : _states(states)
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	_isRunning = true;
	this->_stateClock.restart();
	_timeToLive = 0;
}

void GameEngine::update()
{
	sf::Event	event;

	static float oldTime = _stateClock.getElapsedTime().asSeconds();
	float time = _stateClock.getElapsedTime().asSeconds();
	float dt = time - oldTime;
	oldTime = time;

	_timeToLive += dt;

	if (_states.front()->isRunning() == false)
	{
		IScreen *tmp = _states.front()->getNextState();
		PushState(tmp);
		Singleton::getInstance().isEscapePressed = false;
	}
	IScreen *state = _states.front();
	if (state)
	{
		while (Singleton::getInstance()._window->pollEvent(event))
		{
			state->events(event);
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				Singleton::getInstance().isKeyPressed = true;
				_controler.handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				_controler.handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::MouseWheelMoved:
				Singleton::getInstance().deltaMouseWeel = event.mouseWheel.delta;
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
			default:
				Singleton::getInstance().isKeyPressed = false;
				break;
			}
		}
		state->update();
	}

	if (_timeToLive > 3) {
		_timeToLive = 0;
		while (_states.size() > 1) {
			std::cout << _states.size() << std::endl;
			IScreen *tmp;
			tmp = _states.back();
			_states.pop_back();
			delete tmp;
		}
	}
}

bool GameEngine::getIsRunning() const
{
	return _isRunning;
}

void GameEngine::PushState(IScreen *state)
{
	_states.push_front(state);
	_states.front()->initialize();


}	

void GameEngine::SetState(IScreen* state)
{
	PopState();

	// Add the new state
	PushState(state);
}

void GameEngine::PopState(void)
{
	//if (!_states.empty())
	//{
	//	IScreen *tmp = _states.top();
	//	_states.pop();
	//	tmp = NULL;
	//	std::cout << "On delete" << std::endl;
	//	//delete tmp
	//}
}