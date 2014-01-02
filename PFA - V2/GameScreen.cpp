#include <sstream>
#include <iostream>
#include "GameScreen.h"

GameScreen::GameScreen()
{
	_isRunning = true;
	_map = new Map();
	_map->init(std::string(""), sf::Vector2i(18, 18), 33);
	_map->generate();
}

void GameScreen::draw(std::vector<IEntity *> &players, std::list<IEntity *> &entities)
{
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	updateStatistics(_t);

	this->_map->draw(Singleton::getInstance()._window);
	this->_map->drawMiniMap(Singleton::getInstance()._window);

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
		checkClicks();
	}
	checkInput();
	Singleton::getInstance()._window->display();
}

void GameScreen::checkClicks()
{
	static int stillClicking = 0;
	if (Singleton::getInstance().isLeftClicking && stillClicking == 0)
	{
		saveClick(true);
		std::cout << "CLICK : " << this->_leftClickPressed._screen << std::endl;
		++stillClicking;
	}
	else if (Singleton::getInstance().isLeftClicking == true && stillClicking < 10)
	{
		++stillClicking;
	}
	else if (Singleton::getInstance().isLeftClicking == false && stillClicking >= 10)
	{
		std::cout << "CLICK DETACH: " << this->_leftClickReleased._screen << std::endl;
		saveClick(false);
		updateObjectsPos();
		stillClicking = 0;
	}
	else if (Singleton::getInstance().isLeftClicking == false && stillClicking <= 10)
		stillClicking = 0;
}

void GameScreen::updateObjectsPos()
{
	// MODIFICATIONS MADE HERE. SHOULD WORK NOW.
	if (this->_leftClickPressed._compartment != NULL)
		_gc.callFunction(this->_leftClickPressed, this->_leftClickReleased);
}

void GameScreen::saveClick(bool click)
{
	if (click)
	{
		if (this->_inventory->_mainInventory->clickInWindow(Singleton::getInstance().posLeftClickPressed))
		{
			this->_leftClickPressed = this->_inventory->_mainInventory->clickInCompartment(Singleton::getInstance().posLeftClickPressed);
			return ;
		}
		if (this->_crafting->clickInWindow(Singleton::getInstance().posLeftClickPressed))
		{
			this->_leftClickPressed = this->_crafting->clickInCompartment(Singleton::getInstance().posLeftClickPressed);
			return ;
		}
		if (this->_stuff->clickInWindow(Singleton::getInstance().posLeftClickPressed))
		{
			this->_leftClickPressed = this->_stuff->clickInCompartment(Singleton::getInstance().posLeftClickPressed);
			return ;
		}
	}
	else
	{
		if (this->_inventory->_mainInventory->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{
			std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_inventory->_mainInventory->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
		if (this->_crafting->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{
			std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_crafting->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
		if (this->_stuff->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{			
			std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_stuff->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
	}
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
	//if (this->_stuff->close() || this->_crafting->close() || this->_inventory->close())
	//	this->_activeInventary = false;

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
	//_map->update();
}