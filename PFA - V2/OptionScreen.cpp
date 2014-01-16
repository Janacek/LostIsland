#include "OptionScreen.h"

OptionScreen::OptionScreen()
{
	_isRunning = true;
}

void OptionScreen::initialize()
{
}

void OptionScreen::draw()
{
	Singleton::getInstance()._window->clear();
	Singleton::getInstance()._window->display();
}

void OptionScreen::update()
{
	if (Singleton::getInstance().isEscapePressed)
	{
		_isRunning = false;
		_next = new StartScreen();
	}
}

stateName OptionScreen::getStateName() const
{
	return OPTIONS;
}

IScreen *OptionScreen::getNextState()
{
	return this->_next;
}

void OptionScreen::release()
{
	
}

bool OptionScreen::isRunning() const
{
	return this->_isRunning;
}