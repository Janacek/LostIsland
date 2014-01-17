#include "OptionScreen.h"

OptionScreen::OptionScreen()
	: _button(ClickableButton(sf::Vector2f(50, 50), sf::Vector2f(300, 400), "T"))
{
	_isRunning = true;
}

void OptionScreen::initialize()
{
}

void OptionScreen::draw()
{
	Singleton::getInstance()._window->clear();

	_button.draw();

	Singleton::getInstance()._window->display();
}

void OptionScreen::update()
{
	if (Singleton::getInstance().isEscapePressed)
	{
		_isRunning = false;
		_next = new StartScreen();
	}

	_button.update();
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