#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Food.h"
#include "Wood.h"
#include "Bunny.h"
#include "Water.h"
#include "Tree.h"
#include "MapEnvironment.h"
#include					"Singleton.h"
#include					"ImageSingleton.h"
GameScreen::GameScreen()
{

	_isRunning = true;
	_camera._position.x = 0;
	_camera._position.y = 0;
	_dropCompartment = NULL;
	_map = new Map(&_camera, _loadingText);
	pos.x = 100;
	pos.y = 100;

	_statisticsText.setFont((*FontManager::getInstance().getFont(SANSATION)));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

	/*TEST*/
	_one.push_back(new Food);

	_loadingScreen = new sf::Image;
	_loadingScreen->loadFromFile("./loadingScreen.png");
	_loaded = false;

	_two.push_back(new Tree);
	_two.push_back(new Wood);

	_tree.push_back(new Food);
	_tree.push_back(new Water);
	_tree.push_back(new Tree);
}

GameScreen::~GameScreen()
{

	Singleton::getInstance().isRunning = false;
	std::cout << "Deleting Game Screen" << std::endl;
	delete _map;
	delete _physicEngine;
	delete _dropCompartment;
	delete _inventory;
}

void	GameScreen::checkQuit(sf::Event &e)
{
	sf::FloatRect rect = this->_inventory->_inventoryWindow->GetAllocation();

	if (this->_inventory->_inventoryWindow->IsGloballyVisible() && e.type == sf::Event::MouseButtonPressed && rect.contains(sf::Vector2f(sf::Mouse::getPosition(*Singleton::getInstance()._window).x, sf::Mouse::getPosition(*Singleton::getInstance()._window).y)) == false)
	{
		this->_inventory->_inventoryWindow->Show(false);
		this->_activeInventary = false;
	}
}

void GameScreen::events(sf::Event &e)
{
	Singleton::getInstance()._desktop.HandleEvent(e);
	
}

static bool cmpPlayers(Player *lhs, Player *rhs)
{
	return lhs->getPosition().y < rhs->getPosition().y;
}

void GameScreen::initialize(void)
{
	std::ostringstream os;
	_loaded = false;

	_loadingText = "Initializing map";
	_map->init(std::string(""), sf::Vector2i(18, 18), 33);
	_loadingText = "Generating map";
	_map->generate();
	this->_physicEngine = new PhysicEngine(_map, &_camera);
	_loadingText = "Initializing awesome physics";
	_physicEngine->init();

	_loadingText = "Adding some animals";
	for (int i = 0; i < 15;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			Bunny *rabbit = new Bunny(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 100, _map->_camera);
			this->_entities.push_back(rabbit);
			_map->setEntityMap(rabbit, y, x);
			++i;
		}
	}

	_loadingText = "Adding players";
	auto spawnPoint = _map->_spawnPoints.begin();
	sf::Vector2f posCam = *spawnPoint;

	_map->_camera->_position.x = posCam.x - (Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL) / 2;
	_map->_camera->_position.y = posCam.y - (Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) / 2;

	if (_map->_camera->_position.x < 0)
		_map->_camera->_position.x;
	if (_map->_camera->_position.y < 0)
		_map->_camera->_position.y;

	this->_inventory = new InventoryWindow;
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f pos = *spawnPoint;
		++spawnPoint;
		Player *p = new Player(pos, &_camera);
		p->setMap(_map);
		p->setInventory(this->_inventory);
		_map->setEntityMap(p, pos.x, pos.y);
		os << (i + 1);
		p->setName("Player " + os.str());
		os.str("");
		p->loadAnimation("finn.png", 0.05f);
		this->_players.push_back(p);

	}


	this->_activeInventary = false;
	this->_activeWinRessources = false;
	_loadingText = "Generating inventories";
	
	this->_inventory->init();
	this->_inventory->createZones(this->_players);
	_loadingText = "Generating Crafting Window";
	this->_crafting = new Crafting;
	//initialisation de l'image du pointeur
	this->_mousePicture.setSize(sf::Vector2f(static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100), static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100)));
	_loaded = true;
}

std::vector<Player *> &GameScreen::getPlayers()
{
	return this->_players;
}

void GameScreen::mouseLeftPress(int index)
{
	
}

void GameScreen::drawPlayerInformations(Player *player, sf::Vector2f const &pos) const
{
	sf::RectangleShape playerInfo(sf::Vector2f(300, 200));
	playerInfo.setTexture(ImageSingleton::getInstance().get(PLAYER_INFOS_BACKGROUND));
	playerInfo.setPosition(pos);

	sf::Text name;
	name.setCharacterSize(20);
	name.setString(player->getName());
	name.setPosition(sf::Vector2f(pos.x + 10, pos.y + 10));
	name.setColor(sf::Color::Black);
	name.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::Text health;
	health.setCharacterSize(20);
	health.setString("Health");
	health.setPosition(sf::Vector2f(pos.x + 10, pos.y + 50));
	health.setColor(sf::Color::Black);
	health.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::Text hunger;
	hunger.setCharacterSize(20);
	hunger.setString("Hunger");
	hunger.setPosition(sf::Vector2f(pos.x + 10, pos.y + 100));
	hunger.setColor(sf::Color::Black);
	hunger.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::Text thirst;
	thirst.setCharacterSize(20);
	thirst.setString("Thirst");
	thirst.setPosition(sf::Vector2f(pos.x + 10, pos.y + 150));
	thirst.setColor(sf::Color::Black);
	thirst.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::RectangleShape thirstBar(sf::Vector2f(player->_water * 1.9, 20));
	thirstBar.setFillColor(sf::Color(32, 178, 170));
	thirstBar.setPosition(pos.x + 85, pos.y + 155);

	sf::Text thirstNbr;
	thirstNbr.setCharacterSize(20);
	thirstNbr.setString(std::to_string((int)player->_water) + " %");
	thirstNbr.setPosition(sf::Vector2f(pos.x + 85 + 70, pos.y + 152));
	thirstNbr.setColor(sf::Color::Black);
	thirstNbr.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::RectangleShape hungerBar(sf::Vector2f(player->_food * 1.9, 20));
	hungerBar.setFillColor(sf::Color(139, 69, 19));
	hungerBar.setPosition(pos.x + 85, pos.y + 105);

	sf::Text hungerNbr;
	hungerNbr.setCharacterSize(20);
	hungerNbr.setString(std::to_string((int)player->_food) + " %");
	hungerNbr.setPosition(sf::Vector2f(pos.x + 85 + 70, pos.y + 102));
	hungerNbr.setColor(sf::Color::Black);
	hungerNbr.setFont(*FontManager::getInstance().getFont(SANSATION));

	sf::RectangleShape healthBar(sf::Vector2f(player->_life * 1.9, 20));
	healthBar.setFillColor(sf::Color(196, 0, 0));
	healthBar.setPosition(pos.x + 85, pos.y + 55);

	sf::Text healthNbr;
	healthNbr.setCharacterSize(20);
	healthNbr.setString(std::to_string((int)player->_life) + " %");
	healthNbr.setPosition(sf::Vector2f(pos.x + 85 + 70, pos.y + 52));
	healthNbr.setColor(sf::Color::Black);
	healthNbr.setFont(*FontManager::getInstance().getFont(SANSATION));

	Singleton::getInstance()._window->draw(playerInfo);
	Singleton::getInstance()._window->draw(name);
	Singleton::getInstance()._window->draw(health);
	Singleton::getInstance()._window->draw(healthBar);
	Singleton::getInstance()._window->draw(healthNbr);
	Singleton::getInstance()._window->draw(hunger);
	Singleton::getInstance()._window->draw(hungerBar);
	Singleton::getInstance()._window->draw(hungerNbr);
	Singleton::getInstance()._window->draw(thirst);
	Singleton::getInstance()._window->draw(thirstBar);
	Singleton::getInstance()._window->draw(thirstNbr);

}

void GameScreen::draw()
{
	if (!_loaded)
	{
		sf::Texture loadingScreen;
		loadingScreen.loadFromImage(*_loadingScreen);
		sf::Sprite spriteLoad;
		spriteLoad.setTexture(loadingScreen);
		Singleton::getInstance()._window->draw(spriteLoad);
		_loadingSfText.setFont(*FontManager::getInstance().getFont(SANSATION));
		_loadingSfText.setPosition(150, 150);
		_loadingSfText.setString(_loadingText);
		Singleton::getInstance()._window->draw(_loadingSfText);
	}
	else
	{
		Singleton::getInstance()._window->clear();
		_t = Singleton::getInstance()._clock->restart();
		Singleton::getInstance()._animClock->restart();

		////

		this->_map->draw(Singleton::getInstance()._window);

		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			(*it)->draw(NULL);
		}
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			(*it)->draw(NULL);
		}
		drawSelectionZone();
		
		/*
		** Draw of the players informations
		*/
		sf::Vector2f infosPos(400, 0);
		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			if ((*it)->_isSelected) {
				drawPlayerInformations(*it, infosPos);
				infosPos.x += 320;
			}
		}
	
		this->_map->drawMiniMap(Singleton::getInstance()._window, _players);
		checkDrawInventory();
		this->_inventory->update();
		this->_inventory->draw();
	}
	Singleton::getInstance()._window->display();
}

void	GameScreen::drawSelectionZone()
{
	if (Singleton::getInstance().isLeftClicking && this->_activeInventary == false)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		sf::Vector2i _posSelectedArea = Singleton::getInstance().posLeftClickPressed;

		_posSelectedArea.x -= Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL;
		_posSelectedArea.y -= Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL;

		sf::RectangleShape selectionZone(sf::Vector2f(mousePos.x - _posSelectedArea.x,
			mousePos.y - _posSelectedArea.y));
		selectionZone.setFillColor(sf::Color(255, 255, 255, 100));
		selectionZone.setOutlineColor(sf::Color::White);
		selectionZone.setOutlineThickness(2);
		selectionZone.setPosition(_posSelectedArea.x,
			_posSelectedArea.y);
		Singleton::getInstance()._window->draw(selectionZone);

	}
}

void	GameScreen::updateSelectionZone()
{
	if (Singleton::getInstance().isLeftClicking && this->_activeInventary == false)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		sf::Vector2i _posSelectedArea = Singleton::getInstance().posLeftClickPressed;

		_posSelectedArea.x -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL);
		_posSelectedArea.y -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL);

		sf::RectangleShape selectionZone(sf::Vector2f(static_cast<float>(mousePos.x - _posSelectedArea.x),
			static_cast<float>(mousePos.y - _posSelectedArea.y)));
		selectionZone.setPosition(static_cast<float>(_posSelectedArea.x),
			static_cast<float>(_posSelectedArea.y));

		if (selectionZone.getSize().x == 0 && selectionZone.getSize().y == 0) {
			selectionZone.setSize(sf::Vector2f(1, 1));
		}

		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			sf::RectangleShape tmp(sf::Vector2f(32, 32));

			sf::Vector2f posDisp;
			posDisp.x = (((*it)->getPosition().x - _map->_camera->_position.x) * Chunk::SIZE_OF_CELL);
			posDisp.y = (((*it)->getPosition().y - _map->_camera->_position.y) * Chunk::SIZE_OF_CELL);

			tmp.setPosition(posDisp);

			if (selectionZone.getGlobalBounds().intersects(tmp.getGlobalBounds()))
			{
				(*it)->setSelected(true);
			}
			else if (!Singleton::getInstance().isShiftPressed)
			{
				(*it)->setSelected(false);
			}
		}
	}
}

void GameScreen::update(void)
{
	_physicEngine->updatePos(_players, _entities);

	updateSelectionZone();
	std::sort(_players.begin(), _players.end(), cmpPlayers);

	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		(*it)->update(*_map);
		if ((*it)->_life <= 0)
		{
			for (int i = 0; i < _map->getSize().y * Chunk::NB_CELLS; ++i)
			{
				for (int j = 0; j < _map->getSize().x * Chunk::NB_CELLS; ++j)
				{
					if (_map->getEntitiesMap()[i][j]._component && _map->getEntitiesMap()[i][j]._component->_id == (*it)->_id &&
						_map->getEntitiesMap()[i][j]._component->getType() == PLAYER)
					{
						_map->getEntitiesMap()[i][j]._component->_id = -1;
						_map->getEntitiesMap()[i][j]._component = NULL;
						Player *tmp = (*it);
						it = _players.erase(it);
						delete tmp;
					}
				}
			}
		}
		if (_players.size() <= 0)
		{
			_next = new GameOverScreen;
			_isRunning = false;
			return;
		}
	}
	
	for (auto it2 = _entities.begin(); it2 != _entities.end(); ++it2)
	{
		(*it2)->update(*_map);
	}
	_map->update();
	if (Singleton::getInstance().isEscapePressed)
	{
		_isRunning = false;
		_next = new StartScreen();
	}
}

void		GameScreen::checkDrawInventory()
{
	if (Singleton::getInstance().isKeyIPressed)
	{
		this->_activeInventary = !this->_activeInventary;
		if (this->_activeInventary == true)
			this->_inventory->showBox(this->_players);
		this->_inventory->_inventoryWindow->Show(this->_activeInventary);
		this->_crafting->Show(this->_activeInventary);
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
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
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		std::ostringstream oss;
		std::ostringstream oss2;
		oss << _statisticsNumFrames;
		oss2 << _statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames;

		std::cout << oss2.str() << std::endl;

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
