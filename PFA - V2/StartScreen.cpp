#include "StartScreen.h"

void StartScreen::draw(std::list<IEntity *> entities)
{
}

void StartScreen::initialize(void)
{
}

IScreen * StartScreen::getNextState(void)
{
	return this->_next;
}

void StartScreen::release(void)
{
}

bool StartScreen::isRunning(void) const
{
	return _isRunning;
}

void StartScreen::update(void)
{
}