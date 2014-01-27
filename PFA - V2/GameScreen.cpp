#include <sstream>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GameScreen.h"

GameScreen::GameScreen()
{
	_isRunning = true;
	_camera._position.x = 0;
	_camera._position.y = 0;
	_map = new Map(&_camera);
	pos.x = 100;
	pos.y = 100;
	_map->init(std::string("Babar"), sf::Vector2i(18, 18), 33);
	_map->generate();
	this->_physicEngine = new PhysicEngine(_map, &_camera);
	this->_isFirst = true;
	_physicEngine->init();
}

void GameScreen::events(sf::Event &e)
{
	this->_inventory->_desktop.HandleEvent(e);
}

void GameScreen::initialize(void)
{
	for (int i = 0; i < 2; i++)
	{
		this->_players.push_back(new Player(sf::Vector2f(60 + i * 3, 100), &_camera));
	}
	this->_activeInventary = false;
	this->_inventory = new InventoryWindow;
	this->_inventory->init();
	this->_inventory->createTabs(this->_players);
	_statisticsText.setFont((*FontManager::getInstance().getFont(SANSATION)));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

	//initialisation de l'image du pointeur
	this->_mousePicture.setSize(sf::Vector2f(Singleton::getInstance()._window->getSize().x * 10 / 100, Singleton::getInstance()._window->getSize().x * 10 / 100));

}

void GameScreen::draw()
{
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	//updateStatistics(_t);
	this->_map->draw(Singleton::getInstance()._window);
	this->_map->drawMiniMap(Singleton::getInstance()._window);

	//Singleton::getInstance()._window->draw(_statisticsText);

	//tmp.setPosition((pos.x-_map->getCamPos().x) * Chunk::SIZE_OF_CELL,(pos.y-_map->getCamPos().y) * Chunk::SIZE_OF_CELL);
	for (std::vector<Player *>::iterator it = _players.begin() ; it != _players.end() ; ++it)
	{
		//(*it)->setCamPos(_map->getCamPos()); // tmp wait for class
		(*it)->draw();
	}
	_physicEngine->setCamPos(_map->getCamPos());
	_physicEngine->update();

	if (this->_activeInventary)
	{
		this->_inventory->draw();
	}
	checkInput();
	Singleton::getInstance()._window->display();
}

void GameScreen::update(void)
{
	if (_activeInventary)
		this->_inventory->update();
	if (!Singleton::getInstance().isRightClicking)
	{
		_isFirst = true;
	}
	if (Singleton::getInstance().isRightClicking && this->_isFirst)
	{
		this->_isFirst = false;
		sf::Vector2i tmp_begin = sf::Mouse::getPosition(*Singleton::getInstance()._window);
		sf::Vector2i tmp_end;
		//std::cout << "AVANT CLICK x " << tmp.x << " y " << tmp.y << std::endl; 
		
		tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL ; // ISOK
		tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;

		tmp_end.x = _players[0]->getPosition().x  ; // player en selec
		tmp_end.y = _players[0]->getPosition().y ;
		
		std::cout << "LE CLICK x "  << tmp_begin.x << " y " << tmp_begin.y << std::endl;
		std::cout << "LE JOUEUR  x "  << tmp_end.x << " y " << tmp_end.y << std::endl;
		_physicEngine->findMeAPath(tmp_end, tmp_begin, *_players[0]);
		//_physicEngine->addVertexPoint(tmp);

		//_physicEngine->addVertexPoint(_players.front->getPosition());

		//on click sur une case donc du coup le waypoint existe et pareil pour la pos du player
	}
	_map->update();

	if (Singleton::getInstance().isEscapePressed)
	{
		_isRunning = false;
		_next = new StartScreen();
	}
}

stateName GameScreen::getStateName() const
{
	return GAME;
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
		if (this->_leftClickPressed._compartment != NULL &&  this->_leftClickPressed._screen != WINDOW)
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


bool GameScreen::checkImpossibleCase() const
{
	if (this->_leftClickPressed._compartment == NULL || this->_leftClickPressed._compartment->_elements.size() == 0)
		return false;
	if (this->_leftClickPressed._compartment == this->_leftClickReleased._compartment)
	{
		return false;
	}
	return true;
}


void GameScreen::updateObjectsPos()
{
	if (this->checkImpossibleCase() == true)
	{
		if (this->_leftClickPressed._compartment != NULL)
			_gc.callFunction(this->_leftClickPressed, this->_leftClickReleased);
	}
}

void GameScreen::saveClick(bool click)
{
	/*if (click)
	{
		std::cout << "Je clique : " << Singleton::getInstance().posLeftClickPressed.x << " " << Singleton::getInstance().posLeftClickPressed.y << std::endl;
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
	}*/
}

void GameScreen::checkClose()
{
	/*if (this->_stuff->close() == true || this->_crafting->close() == true || this->_inventory->close() == true)
	{
		this->_activeInventary = false;
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	}*/
}

void GameScreen::checkInput()
{
	if (Singleton::getInstance().isKeyIPressed)
		this->_activeInventary = true;
	else
	{
		this->_activeInventary = false;
	}
}

void GameScreen::updateStatistics(sf::Time &elapsedTime)
{
	//_statisticsUpdateTime += elapsedTime;
	//_statisticsNumFrames += 1;

	//if (_statisticsUpdateTime >= sf::seconds(1.0f))
	//{
	//	std::ostringstream oss;
	//	std::ostringstream oss2;
	//	oss << _statisticsNumFrames;
	//	oss2 << _statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames;
	//	_statisticsText.setString(
	//		"Frames / Second = " + oss.str() + "\n" 
	//		"Time / Update = " + oss2.str() + "us");

	//	_statisticsUpdateTime -= sf::seconds(1.0f);
	//	_statisticsNumFrames = 0;
	//}
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

