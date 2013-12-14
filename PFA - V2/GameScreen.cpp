#include <sstream>
#include <iostream>
#include "GameScreen.h"
#include "Singleton.h"


GameScreen::GameScreen()
{
	_isRunning = true;
	//_map = new Map(std::pair<int, int>(1200, 800), 42);
	// TODO Map est bidon pour le moment, envoyer un mail a mart_u@epitech.eu pour des éventuels problèmes avec cette classe (Rémy -> LOL)

}


void GameScreen::draw(std::list<IEntity *> players, std::list<IEntity *> entities)
{
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	updateStatistics(_t);

	//this->_map->draw(Singleton::getInstance()._window);

	Singleton::getInstance()._window->draw(_statisticsText);
	Singleton::getInstance()._window->draw(_statisticsText);
	if (this->_activeInventary)
	{
		this->_inventory->draw();
		this->_crafting->draw();
		this->_stuff->draw();
		this->_inventory->update();
		this->_crafting->update();
		this->_stuff->update();
	}
	checkInput();
	Singleton::getInstance()._window->display();
}

//la clickClock est temporaire. TODO faire une gestion mieux
void GameScreen::checkInput()
{
// 	if (this->_clickClock.getElapsedTime().asMilliseconds() < 100)
// 		return  ;
// 	this->_clickClock.restart();
// 	if (Singleton::getInstance().isKeyIPressed && this->_activeInventary == false)
// 	{
// 		this->_activeInventary = true;
// 	}
// 	 else if (Singleton::getInstance().isKeyIPressed && this->_activeInventary == true)
// 		this->_activeInventary = false;
	if (Singleton::getInstance().isKeyIPressed)
		this->_activeInventary = true;
	else
	{
		this->_activeInventary = false;
	}
	if (this->_stuff->close() || this->_crafting->close() || this->_inventory->close())
		this->_activeInventary = false;

}

void GameScreen::initialize(void)
{
	for (int i = 0; i < 4; i++)
	{
		this->_players.push_back(new Player);
	}
	this->_activeInventary = false;
	this->_inventory = new Inventory(this->_players);
	this->_crafting = new Crafting;
	this->_stuff = new Stuff;
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