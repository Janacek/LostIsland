#include "GraphicEngine.h"
#include "Singleton.h"

void GraphicEngine::init(Map * map)
{
	_isRunning = true;
	_map = map;
	_startScreen = new StartScreen();
	Singleton &ptr1=  Singleton::getInstance();
	ptr1._window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RType");
	_gameScreen = new GameScreen();
	ptr1._window->setFramerateLimit(60);
	//_gameScreen->initialize();
	//PushState(*_gameScreen);
	PushState(_startScreen);

}


void GraphicEngine::update(std::list<IEntity *> players, std::list<IEntity *> entities)
{
	if (_states.top()->isRunning() == false)
		PushState(_states.top()->getNextState());
	_states.top()->draw(players, entities);
	
}

void GraphicEngine::PushState(IScreen *state)
{
	_states.push( state );
    _states.top()->initialize();
}

void GraphicEngine::SetState(IScreen* state)
{
	PopState ();
 
    // Add the new state
    PushState(state);
}

bool GraphicEngine::getIsRunning() const
{
	return _isRunning;
}

void GraphicEngine::PopState(void)
{
	 if ( !_states.empty() )
    {
        _states.top()->release();
        _states.pop();
    }
}