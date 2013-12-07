#include <sstream>
#include <iostream>
#include "GameScreen.h"
#include "Singleton.h"


GameScreen::GameScreen()
{
	_isRunning = true;
}


void GameScreen::draw(std::list<IEntity *> players, std::list<IEntity *> entities)
{
	this->_inventory->draw();
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	updateStatistics(_t);
	
	Singleton::getInstance()._window->draw(_statisticsText);
	Singleton::getInstance()._window->draw(_statisticsText);
	Singleton::getInstance()._window->display();
}

void GameScreen::initialize(void)
{
this->_inventory = new Inventory;
	_font.loadFromFile("./Media/Sansation.ttf");
	_statisticsText.setFont(_font);
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

}
void GameScreen::updateStatistics(sf::Time &elapsedTime)
{
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		std::ostringstream oss;
		std::ostringstream oss2;
		oss << _statisticsNumFrames;
		oss2 << _statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames;
		_statisticsText.setString(
			"Frames / Second = " + oss.str() + "\n" 
			"Time / Update = " + oss2.str() + "us");

		_statisticsUpdateTime -= sf::seconds(1.0f);
		_statisticsNumFrames = 0;
	}
}

IScreen * GameScreen::getNextState(void)
{
	return this->_next;
}

void GameScreen::release(void)
{
}

bool GameScreen::isRunning(void) const
{
	return this->_isRunning;
}

void GameScreen::update(void)
{
}