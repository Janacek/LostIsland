#include "GraphicEngine.h"
#include "Singleton.h"

GraphicEngine::GraphicEngine( std::stack<IScreen *> &states,
							 std::vector<IEntity *> &players, std::list<IEntity *> &entities)
							 : _states(states), _players(players), _entities(entities)
{

}

void GraphicEngine::run()
{
	Singleton::getInstance()._window->setActive(true);
	this->init();
	while (true)
	{
		this->draw(_players, _entities);
	}
}

void GraphicEngine::draw(std::vector<IEntity *> &players, std::list<IEntity *> &entities)
{
	IScreen *state = _states.top();
	if (state)
		state->draw(players, entities);
}

void GraphicEngine::init()
{
	_isRunning = true;

	//_startScreen = new StartScreen();

	//_gameScreen->initialize();
	//PushState(*_gameScreen);
	//PushState(_startScreen);
}


void GraphicEngine::update(std::vector<IEntity *> &players, std::list<IEntity *> &entities)
{

}

bool GraphicEngine::getIsRunning() const
{
	return _isRunning;
}