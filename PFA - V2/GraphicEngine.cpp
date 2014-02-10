#include "GraphicEngine.h"
#include "Singleton.h"

GraphicEngine::GraphicEngine(std::list<IScreen *> &states) : _states(states)
{

}

void GraphicEngine::run()
{
	Singleton::getInstance()._window->setActive(true);
	this->init();
	while (true)
	{
			this->draw();
	}
}

void GraphicEngine::draw()
{


	IScreen *state = _states.front();
	if (state && state->isRunning())
		state->draw();
}

void GraphicEngine::init()
{
	_isRunning = true;
}


void GraphicEngine::update()
{

}

bool GraphicEngine::getIsRunning() const
{
	return _isRunning;
}