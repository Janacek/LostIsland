#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Meat.h"
#include "Wood.h"
#include "BunnyWhite.h"
#include "BunnyBlack.h"
#include "SheepWhite.h"
#include "SheepBlack.h"
#include "Water.h"
#include "Tree.h"
#include "MapEnvironment.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "Campfire.h"
#include "Wood.h"
#include "WoodenPlank.h"
#include "ShadersManager.h"
#include "Herb.h"
#include "Mushroom.h"
#include "WaterBucket.h"

std::string &GameScreen::serialize() const
{
	std::string toto;
	return (toto);
}

void GameScreen::deserialize(std::ifstream &) throw (MyException)
{
	//load game
}

GameScreen::GameScreen()
{

	_isRunning = true;
	_camera._position.x = 0;
	_camera._position.y = 0;
	_map = new Map(&_camera, _loadingText);

	_loadingScreen = new sf::Image;
	_loadingScreen->loadFromFile("./Media/images/loadingScreen.png");
	_loaded = false;
	_gameOver = false;
	Singleton::getInstance().gameOver = false;
	_truckPosition = sf::Vector2f(-1000, 450);
	_credit0 = sf::Vector2f(500, 1100);
	_playMusic = true;

	_Amusic = new sf::Music;
	_Amusic->openFromFile("./Media/sounds/bgm/gameTheme.ogg");
	_music = new sf::Music;
	_music->openFromFile("./Media/sounds/bgm/winTheme.ogg");
}

GameScreen::~GameScreen()
{

	Singleton::getInstance().isRunning = false;
	std::cout << "Deleting Game Screen" << std::endl;
	delete _map;
	delete _physicEngine;
	delete _inventory;
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

	_Amusic->play();
	_Amusic->setVolume(25.f);



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
			BunnyWhite *rabbit = new BunnyWhite(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 50, _map->_camera);
			this->_entities.push_back(rabbit);
			_map->setEntityMap(rabbit, x, y);
			++i;
		}
	}

	for (int i = 0; i < 15;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			Velociraptor *raptor = new Velociraptor(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 50, _map->_camera);
			this->_entities.push_back(raptor);
			_map->setEntityMap(raptor, x, y);
			++i;
		}
	}

	for (int i = 0; i < 15;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			BunnyBlack *rabbit = new BunnyBlack(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 50, _map->_camera);
			this->_entities.push_back(rabbit);
			_map->setEntityMap(rabbit, x, y);
			++i;
		}
	}

	for (int i = 0; i < 5;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			SheepWhite *sheep = new SheepWhite(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 75, _map->_camera);
			this->_entities.push_back(sheep);
			_map->setEntityMap(sheep, x, y);
			++i;
		}
	}

	for (int i = 0; i < 5;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			SheepBlack *sheep = new SheepBlack(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 75, _map->_camera);
			this->_entities.push_back(sheep);
			_map->setEntityMap(sheep, x, y);
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
		p->loadAnimation("./Media/images/finn.png", 0.05f);
		this->_players.push_back(p);

	}



	for (int i = 0; i < 50;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			Herb *herb = new Herb;
			_map->setEntityMap(herb, x, y);
			++i;
		}
	}

	for (int i = 0; i < 30;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::FOREST &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			Mushroom *mushroom = new Mushroom;
			_map->setEntityMap(mushroom, x, y);
			++i;
		}
	}

	this->_activeInventary = false;
	_loadingText = "Generating inventories";

	this->_inventory->init();
	this->_inventory->createZones(this->_players);
	_loadingText = "Generating Crafting Window";
	this->_crafting = new Crafting;
	this->_inventory->setCraftingClass(this->_crafting);
	this->_crafting->setInventoryClass(this->_inventory);
	this->_crafting->createChooseWindowContent();

	//initialisation de l'image du pointeur
	this->_mousePicture.setSize(sf::Vector2f(static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100), static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100)));
	_loaded = true;
	this->_players[0]->addEntityInInventory(new Wood);
	this->_players[0]->addEntityInInventory(new Campfire);
	this->_players[0]->addEntityInInventory(new WaterBucket);
}

std::vector<Player *> &GameScreen::getPlayers()
{
	return this->_players;
}

void GameScreen::drawPlayerInformations(Player *player, sf::Vector2f const &pos) const
{
	sf::RectangleShape playerInfo(sf::Vector2f(300, 200));
	playerInfo.setTexture(ImageManager::getInstance().get(PLAYER_INFOS_BACKGROUND));
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

	sf::RectangleShape healthBar(sf::Vector2f(player->getLife() * 1.9, 20));
	healthBar.setFillColor(sf::Color(196, 0, 0));
	healthBar.setPosition(pos.x + 85, pos.y + 55);

	sf::Text healthNbr;
	healthNbr.setCharacterSize(20);
	healthNbr.setString(std::to_string((int)player->getLife()) + " %");
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

void GameScreen::drawEntities()
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		if (!(*it)->getIsDead())
		{
			sf::Vector2f savePos;
			savePos = (*it)->getPosition();
			sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);
			sf::Vector2f finalPos;

			finalPos.x = (float)mousePos.x / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.x);
			finalPos.y = (float)mousePos.y / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.y);

			sf::FloatRect mouseRect(sf::Vector2f(mousePos), sf::Vector2f(2, 2));
			if (mouseRect.intersects((*it)->getBoxCollider()))
				(*it)->draw(_map->_mapTexture, *ShadersManager::getInstance().get(BLOOM));
			else
				(*it)->draw(_map->_mapTexture);
		}
	}
	for (auto it = _entities.begin(); it != _entities.end(); ++it)
	{
		if (!(*it)->getIsDead())
		{
			sf::Vector2f savePos;
			savePos = (*it)->getPosition();
			sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);
			sf::Vector2f finalPos;

			finalPos.x = (float)mousePos.x / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.x);
			finalPos.y = (float)mousePos.y / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.y);

			sf::FloatRect mouseRect(sf::Vector2f(mousePos), sf::Vector2f(2, 2));
			if (mouseRect.intersects((*it)->getBoxCollider()))
				(*it)->draw(_map->_mapTexture, *ShadersManager::getInstance().get(BLOOM));
			else
				(*it)->draw(_map->_mapTexture);
		}
	}
}

void GameScreen::redrawEntities()
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		if (!(*it)->getIsDead())
		{
			if (_map->getEntityAt((int)(*it)->getPosition().y - 1, (int)(*it)->getPosition().x) != NULL ||
				(_map->getEntityAt((int)(*it)->getPosition().y, (int)(*it)->getPosition().x) != NULL &&
				_map->getEntityAt((int)(*it)->getPosition().y, (int)(*it)->getPosition().x)->getType() != PLAYER))
			{
				sf::Vector2f savePos;
				savePos = (*it)->getPosition();
				sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);
				sf::Vector2f finalPos;

				finalPos.x = (float)mousePos.x / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.x);
				finalPos.y = (float)mousePos.y / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.y);

				sf::FloatRect mouseRect(sf::Vector2f(mousePos), sf::Vector2f(2, 2));
				if (mouseRect.intersects((*it)->getBoxCollider()))
					(*it)->draw(_map->_mapTexture, *ShadersManager::getInstance().get(BLOOM));
				else
					(*it)->draw(_map->_mapTexture);
			}
		}
	}

	for (auto it = _entities.begin(); it != _entities.end(); ++it)
	{
		if (!(*it)->getIsDead())
		{
			if (_map->getEntityAt((int)(*it)->getPosition().y - 1, (int)(*it)->getPosition().x) != NULL ||
				(_map->getEntityAt((int)(*it)->getPosition().y, (int)(*it)->getPosition().x) != NULL &&
				_map->getEntityAt((int)(*it)->getPosition().y, (int)(*it)->getPosition().x)->getType() != (*it)->getType()))
			{
				sf::Vector2f savePos;
				savePos = (*it)->getPosition();
				sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);
				sf::Vector2f finalPos;

				finalPos.x = (float)mousePos.x / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.x);
				finalPos.y = (float)mousePos.y / (float)Chunk::SIZE_OF_CELL + static_cast<float>(_map->_camera->_position.y);

				sf::FloatRect mouseRect(sf::Vector2f(mousePos), sf::Vector2f(2, 2));
				if (mouseRect.intersects((*it)->getBoxCollider()))
					(*it)->draw(_map->_mapTexture, *ShadersManager::getInstance().get(BLOOM));
				else
					(*it)->draw(_map->_mapTexture);
			}
		}
	}
}

void GameScreen::drawEntitiesInfos()
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		if (!(*it)->getIsDead())
		{
			(*it)->drawInfos(_map->_mapTexture);
		}
	}
}

void GameScreen::drawText(std::string text, int x, int y, int size)
{
	sf::Text t;
	t.setPosition(x, y);
	t.setString(text);
	t.setFont(*FontManager::getInstance().getFont(SANSATION));
	t.setCharacterSize(size);
	t.setColor(sf::Color::Black);
	Singleton::getInstance()._window->draw(t);
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
	else if (!Singleton::getInstance().gameOver)
	{
		Singleton::getInstance()._window->clear();
		_t = Singleton::getInstance()._clock->restart();
		Singleton::getInstance()._animClock->restart();

		this->_map->draw();
		this->drawEntities();
		this->_map->drawEnv();
		this->drawEntitiesInfos();
		this->redrawEntities();
		this->_map->display();


		drawSelectionZone();

		/*
		** Draw of the players informations
		*/
		sf::Vector2f infosPos(400, 0);
		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			if ((*it)->getIsSelected()) {
				drawPlayerInformations(*it, infosPos);
				infosPos.x += 320;
			}
		}

		this->_map->drawMiniMap(Singleton::getInstance()._window, _players);
		checkDrawInventory();
		this->_inventory->update();
		this->_inventory->draw();
	}
	else
	{
		this->_map->draw();
		this->drawEntities();
		this->_map->drawEnv();
		this->drawEntitiesInfos();
		this->redrawEntities();
		this->_map->display();
		this->_map->drawMiniMap(Singleton::getInstance()._window, _players);


		sf::Sprite spriteLoad(*ImageManager::getInstance().get(TRUCK));
		spriteLoad.setPosition(_truckPosition);
		Singleton::getInstance()._window->draw(spriteLoad);

		drawText("THANK YOU FOR PLAYING LOST ISLAND,", _credit0.x - 150, _credit0.y, 75);
		drawText("SINCERLY, THE LOST TEAM", _credit0.x - 150, _credit0.y + 100, 75);
		drawText("THOMAS MARTIN", _credit0.x - 150, _credit0.y + 200, 75);
		drawText("RONAN GUINOT", _credit0.x - 150, _credit0.y + 300, 75);
		drawText("REMY THULIE", _credit0.x - 150, _credit0.y + 400, 75);
		drawText("GUILLAUME MARCHAND", _credit0.x - 150, _credit0.y + 500, 75);
		drawText("YOU CAN SKIP THE", _credit0.x - 150, _credit0.y + 700, 75);
		drawText("CREDITS BY PRESSING", _credit0.x - 150, _credit0.y + 800, 75);
		drawText("THE ESCAPE KEY", _credit0.x - 150, _credit0.y + 900, 75);
		drawText("MAIN DIRECTOR", _credit0.x - 150, _credit0.y + 1100, 75);
		drawText("THOMAS MARTIN", _credit0.x - 150, _credit0.y + 1200, 60);
		drawText("MAP DIRECTOR", _credit0.x - 150, _credit0.y + 1300, 75);
		drawText("THOMAS MARTIN", _credit0.x - 150, _credit0.y + 1400, 60);
		drawText("PHYSICS DUDE", _credit0.x - 150, _credit0.y + 1500, 75);
		drawText("RONAN GUINOT", _credit0.x - 150, _credit0.y + 1600, 60);
		drawText("SOUND COMPOSER", _credit0.x - 150, _credit0.y + 1700, 75);
		drawText("GUILLAUME MARCHAND", _credit0.x - 150, _credit0.y + 1800, 60);
		drawText("BUG DESIGNER", _credit0.x - 150, _credit0.y + 1900, 75);
		drawText("RONAN GUINOT", _credit0.x - 150, _credit0.y + 2000, 60);
		drawText("LEAD UI DESIGNER", _credit0.x - 150, _credit0.y + 2100, 75);
		drawText("REMY THULIE", _credit0.x - 150, _credit0.y + 2200, 60);
		drawText("SPECIAL THANKS", _credit0.x - 150, _credit0.y + 2400, 75);
		drawText("GARY HOUBRE", _credit0.x - 150, _credit0.y + 2500, 60);
		drawText("TAKASHI TEZUKA", _credit0.x - 150, _credit0.y + 2600, 60);
		drawText("STEVEN SPIELBERG", _credit0.x - 150, _credit0.y + 2700, 60);
		drawText("STARING", _credit0.x - 150, _credit0.y + 2900, 75);
		drawText("FINN AND JAKE", _credit0.x - 150, _credit0.y + 3000, 60);
		drawText("HECTOR THE VELOCIRAPTOR", _credit0.x - 150, _credit0.y + 3100, 60);
		drawText("ROGER RABBIT", _credit0.x - 150, _credit0.y + 3200, 60);
		drawText("SHEEP N DALES", _credit0.x - 150, _credit0.y + 3300, 60);

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

			if (!(*it)->getIsDead())
			{
				if (selectionZone.getGlobalBounds().intersects(tmp.getGlobalBounds()))
				{
					(*it)->setIsSelected(true);
				}
				else if (!Singleton::getInstance().isShiftPressed)
				{
					(*it)->setIsSelected(false);
				}
			}
		}
	}
}

void GameScreen::update(void)
{
	if (Singleton::getInstance().gameOver)
	{
		_Amusic->stop();
		// code the end here
		//exit(1);
		if (_playMusic)
		{
			_music->play();
			_playMusic = false;
		}

		_truckPosition.x += 0.006;

		if (_truckPosition.x >= 1920)
		{
			_credit0.y -= 0.0025;
		}

		if (Singleton::getInstance().isEscapePressed)
		{
			_isRunning = false;
			_music->stop();
			_Amusic->stop();
			_next = new StartScreen();
		}
		if (_music->getStatus() == sf::Music::Status::Stopped)
		{
			_isRunning = false;
			_next = new StartScreen;
			return;
		}
	}
	else
	{
		_physicEngine->updatePos(_players, _entities);

		updateSelectionZone();
		//std::sort(_players.begin(), _players.end(), cmpPlayers);
		int gameOver = 0;

		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			if (!(*it)->getIsDead())
			{
				(*it)->update(*_map);
				if ((*it)->_objective)
				if ((*it)->_objective->getLife() <= 0 && (*it)->_objective->getIsAMovingEntity())
					(*it)->_objective = NULL;
			}

			if ((*it)->getIsDead())
				++gameOver;
		}

		if (gameOver == 4)
		{
			_next = new GameOverScreen;
			_isRunning = false;
			return;
		}

		for (auto it2 = _entities.begin(); it2 != _entities.end(); ++it2)
		{
			if (!(*it2)->getIsDead())
				(*it2)->update(*_map);
		}

		_map->update();


		for (int i = 0; i < _map->getSize().y * Chunk::NB_CELLS; ++i)
		{
			for (int j = 0; j < _map->getSize().x * Chunk::NB_CELLS; ++j)
			{
				if (_map->getEntitiesMap()[i][j]._component && _map->getEntitiesMap()[i][j]._component->getIsDead())
				{
					_map->getEntitiesMap()[i][j]._component = NULL;
				}
			}
		}


		if (Singleton::getInstance().isEscapePressed)
		{
			_isRunning = false;
			_next = new StartScreen();
		}
	}
}

void		GameScreen::checkDrawInventory()
{
	if (Singleton::getInstance().isKeyIPressed)
	{
		this->_activeInventary = !this->_activeInventary;
		if (this->_activeInventary == true)
		{
			this->_inventory->showBox(this->_players);
		}
		this->_inventory->Show(this->_activeInventary);
		this->_crafting->Show(this->_activeInventary);
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	}
}

stateName GameScreen::getStateName() const
{
	return GAME;
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
