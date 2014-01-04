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

void GameScreen::initialize(void)
{
	for (int i = 0; i < 4; i++)
	{
		this->_players.push_back(new Player);
	}
	this->_activeInventary = false;
	this->_inventory = new InventaryWindow(this->_players);
	this->_inventory->init();
	this->_crafting = new Crafting;
	this->_stuff = new Stuff;
	_font.loadFromFile("./Media/Sansation.ttf");
	_statisticsText.setFont(_font);
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

	//initialisation de l'image du pointeur
	this->_mousePicture.setSize(sf::Vector2f(Singleton::getInstance()._window->getSize().x * 10 / 100, Singleton::getInstance()._window->getSize().x * 10 / 100));

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
		drawMouse();
		this->_inventory->update();
		this->_crafting->update();
		this->_stuff->update();
		checkClicks();
	}
	checkInput();
	Singleton::getInstance()._window->display();
}

void GameScreen::drawMouse()
{
	if (this->_activeInventary)
	{
		if (Singleton::getInstance().isLeftClicking && this->_leftClickPressed._compartment != NULL && this->_leftClickPressed._compartment->_elements.size() > 0)
		{
			sf::Vector2i tmp = sf::Mouse::getPosition(*Singleton::getInstance()._window);
			this->_mousePicture.setPosition(tmp.x, tmp.y);
			Singleton::getInstance()._window->draw(this->_mousePicture);
		}
	}
}

void GameScreen::checkClicks()
{
	static int stillClicking = 0;
	if (Singleton::getInstance().isLeftClicking && stillClicking == 0)
	{
		saveClick(true);
		if (this->_leftClickPressed._compartment != NULL &&  this->_leftClickPressed._screen != NONE)
			this->_mousePicture.setTexture(this->_leftClickPressed._compartment->_rect.getTexture());
		++stillClicking;
	}
	else if (Singleton::getInstance().isLeftClicking == true && stillClicking < 10)
	{
		++stillClicking;
	}
	else if (Singleton::getInstance().isLeftClicking == false && stillClicking >= 10)
	{
		saveClick(false);
		this->_mousePicture.setTexture(NULL);
		updateObjectsPos();
		stillClicking = 0;
	}
	else if (Singleton::getInstance().isLeftClicking == false && stillClicking <= 10)
		stillClicking = 0;
}

void GameScreen::updateObjectsPos()
{
	std::cout << "RELAS : " << this->_leftClickReleased._screen << std::endl;
	if (this->_leftClickPressed._compartment != NULL)
		_gc.callFunction(this->_leftClickPressed, this->_leftClickReleased);
}

void GameScreen::saveClick(bool click)
{
	if (click)
	{
		if (this->_inventory->clickInWindow(Singleton::getInstance().posLeftClickPressed))
		{
			this->_leftClickPressed = this->_inventory->clickInCompartment(Singleton::getInstance().posLeftClickPressed);
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
		if (this->_inventory->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{
			//std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_inventory->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
		if (this->_crafting->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{
			//std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_crafting->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
		if (this->_stuff->clickInWindow(Singleton::getInstance().posLeftClickReleased))
		{			
			//std::cout << "click released pos : " << Singleton::getInstance().posLeftClickReleased.x << std::endl;
			this->_leftClickReleased = this->_stuff->clickInCompartment(Singleton::getInstance().posLeftClickReleased);
			return ;
		}
		
		this->_mousePicture.setTexture(NULL);
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