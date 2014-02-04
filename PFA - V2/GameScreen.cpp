#include <sstream>
#include <iostream>
#include <stdlib.h>
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
	_pathToGo = 0.f;
}

void GameScreen::events(sf::Event &e)
{
	//this->_inventory->_desktop.HandleEvent(e);
}

void GameScreen::initialize(void)
{
	_pathToGo = 0.f;


	for (int i = 0; i < 2; i++)
	{
		Player *p = new Player(sf::Vector2f(60 + i * 3, 100), &_camera);
		p->loadAnimation("zelda.png", 0.1f);
		this->_players.push_back(p);

	}

	this->_activeInventary = false;
	//Inventaire non fonctionnel
	/*this->_inventory = new InventoryWindow;
	this->_inventory->init();
	this->_inventory->createTabs(this->_players);*/
	_statisticsText.setFont((*FontManager::getInstance().getFont(SANSATION)));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

	//initialisation de l'image du pointeur

	this->_mousePicture.setSize(sf::Vector2f(Singleton::getInstance()._window->getSize().x * 10 / 100, Singleton::getInstance()._window->getSize().x * 10 / 100));
	_isPathNotFound = false;

}

void				GameScreen::checkEntitySelection()
{
	int				i = 0;

	//if (!Singleton::getInstance().isLeftClicking)
	//{
		/*if (!this->_selectEnable)
		{
			this->_selectEnable = true;
			_savedPostion.x = sf::Mouse::getPosition(*this->_app).x;
			_savedPostion.y = sf::Mouse::getPosition(*this->_app).y;
		}

		_rectSelection[0].position = this->_app->mapPixelToCoords(this->_savedPostion);
		_rectSelection[1].position = this->_app->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*this->_app).x, _savedPostion.y));
		_rectSelection[2].position = this->_app->mapPixelToCoords(sf::Vector2i((sf::Mouse::getPosition(*this->_app).x), sf::Mouse::getPosition(*this->_app).y));
		_rectSelection[3].position = this->_app->mapPixelToCoords(sf::Vector2i(this->_savedPostion.x, sf::Mouse::getPosition(*this->_app).y));
		while (i < 1)
		{
			if (isInSelection(i))
				dynamic_cast<Human *>(this->_livingEntities[i])->_isSelected = true;
			else
				dynamic_cast<Human *>(this->_livingEntities[i])->_isSelected = false;
			++i;
		}
		_rectSelection[0].color = this->_color;
		_rectSelection[1].color = this->_color;
		_rectSelection[2].color = this->_color;
		_rectSelection[3].color = this->_color;
		this->_app->draw(_rectSelection);
	}
	else
		this->_selectEnable = false;*/
}

void GameScreen::draw()
{
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	Singleton::getInstance()._animClock->restart();
	//updateStatistics(_t);
	this->_map->draw(Singleton::getInstance()._window);

	//Singleton::getInstance()._window->draw(_statisticsText);

	//tmp.setPosition((pos.x-_map->getCamPos().x) * Chunk::SIZE_OF_CELL,(pos.y-_map->getCamPos().y) * Chunk::SIZE_OF_CELL);
	for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it)
	{
		(*it)->draw();
		//break;
	}
	this->_map->drawMiniMap(Singleton::getInstance()._window);
	_physicEngine->setCamPos(_map->getCamPos());
	_physicEngine->update();
	static bool test = true;
	/*if (Singleton::getInstance().isKeyIPressed)
	{
	this->_inventory->_firstN->Show(test);
	test = !test;
	Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	}*/
	checkInput();

	if (Singleton::getInstance().isLeftClicking)
	{
		sf::Vector2i tmp = Singleton::getInstance().posLeftClickPressed;
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		tmp.x -= Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL;
		tmp.y -= Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL;

		sf::RectangleShape selectionZone(sf::Vector2f(mousePos.x - tmp.x, mousePos.y - tmp.y));
		selectionZone.setFillColor(sf::Color(255, 255, 255, 100));
		selectionZone.setOutlineColor(sf::Color::White);
		selectionZone.setOutlineThickness(2);
		selectionZone.setPosition(tmp.x,
			tmp.y);
		Singleton::getInstance()._window->draw(selectionZone);
	}

	Singleton::getInstance()._window->display();

}

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f)
{
	return a + f * (b - a);
}


void GameScreen::update(void)
{
	if (!Singleton::getInstance().isRightClicking)
	{
		_isFirst = true;
	}
	if ((Singleton::getInstance().isRightClicking && this->_isFirst) || _isPathNotFound)
	{
		this->_isFirst = false;
		sf::Vector2i tmp_begin = sf::Mouse::getPosition(*Singleton::getInstance()._window);
		sf::Vector2i tmp_end;
		if (_isPathNotFound && _pathToGo <= 1)
		{
			sf::Vector2f tmp_lerp_begin;
			sf::Vector2f tmp_lerp_end;
			tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
			tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
			tmp_lerp_begin.x = tmp_begin.x;
			tmp_lerp_begin.y = tmp_begin.y;
			tmp_end.x = _players[0]->getPosition().x; // player en selec
			tmp_end.y = _players[0]->getPosition().y;
			tmp_lerp_end.x = tmp_end.x;
			tmp_lerp_end.y = tmp_end.y;
			tmp_lerp_begin = lerp(tmp_lerp_begin, tmp_lerp_end, _pathToGo);
			tmp_begin.x = tmp_lerp_begin.x;
			tmp_begin.y = tmp_lerp_begin.y;
			_pathToGo += 0.01;		
			_isPathNotFound = false;
		}
		else
		{
			tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
			tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
		}
		if (_map->getCellMap()[tmp_begin.y][tmp_begin.x]._cellType == Cell::OCEAN
			|| _map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component != NULL)
		{
			_isPathNotFound = true;
		}
		else
		{
			_pathToGo = 0;
			tmp_end.x = _players[0]->getPosition().x; // player en selec
			tmp_end.y = _players[0]->getPosition().y;
			_physicEngine->findMeAPath(tmp_end, tmp_begin, *_players[0]);
		}
	}
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		(*it)->update();
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

}
void GameScreen::checkClicks()
{

}


bool GameScreen::checkImpossibleCase() const
{
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

}

void GameScreen::checkClose()
{

}

void GameScreen::checkInput()
{

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

