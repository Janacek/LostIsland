#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "GameScreen.h"
#include "Food.h"

GameScreen::GameScreen()
{
	_isRunning = true;
	_camera._position.x = 0;
	_camera._position.y = 0;
	_dropCompartment = NULL;
	_map = new Map(&_camera);
	pos.x = 100;
	pos.y = 100;
	_map->init(std::string("Babar"), sf::Vector2i(18, 18), 33);
	_map->generate();
	this->_physicEngine = new PhysicEngine(_map, &_camera);
	_physicEngine->init();
	_statisticsText.setFont((*FontManager::getInstance().getFont(SANSATION)));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
	_statisticsText.setPosition(0, 30);

	
}

void GameScreen::events(sf::Event &e)
{
	this->_inventory->_desktop.HandleEvent(e);
	checkDrop(e);
}

//Ici on obtient la ressource sur laquelle le playeur a appuyé dans l'inventaire
void GameScreen::checkDrop(sf::Event &e)
{
	if (e.type == sf::Event::MouseButtonReleased)
	{
		this->_dropCompartment = this->_inventory->dropRessource();
		if (this->_dropCompartment != NULL)
		{
			std::cout << "DROP : " << this->_dropCompartment->getSize() << std::endl;
			this->validDrop(1);
			//En cours d'implémentation
			//if (this->_dropCompartment->getSize() > 1)
				//this->_inventory->chooseNumber(this);
		}
	}
}

void GameScreen::validDrop(int nbrDrop)
{
	//Fonction appelée lorsque qu'on a choisi le nbr de ressources qu'on voulait jeter de l'inventaire
	//list contient mtn le bon nombre de ressources 
	std::list<IEntity *> list = this->_dropCompartment->getElements(nbrDrop);
	this->_dropCompartment->delAllElement();
	this->_inventory->_gestionClick.reset();
}

void GameScreen::initialize(void)
{
	for (int i = 0; i < 2; i++)
	{
		Player *p = new Player(sf::Vector2f(static_cast<float>(60 + i * 3), static_cast<float>(100)), &_camera);
		if (i == 0)
			p->setName("Player 1");
		else
			p->setName("Player 2");
		p->loadAnimation("zelda.png", 0.1f);
		this->_players.push_back(p);

	}

	for (int i = 0; i < 15;) {
		int x = rand() % (_map->getSize().x * Chunk::NB_CELLS);
		int y = rand() % (_map->getSize().y * Chunk::NB_CELLS);

		if (_map->getCellMap()[x][y]._cellType == Cell::GRASS &&
			_map->getEntitiesMap()[x][y]._component == NULL) {
			this->_entities.push_back(new Bunny(sf::Vector2f(static_cast<float>(y), static_cast<float>(x)), 100, _map->_camera));
			++i;
		}

	}

	this->_activeInventary = false;
	
	this->_inventory = new InventoryWindow;
	this->_inventory->init();
	this->_inventory->createTabs(this->_players);
	

	//initialisation de l'image du pointeur
	this->_mousePicture.setSize(sf::Vector2f(static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100), static_cast<float>(Singleton::getInstance()._window->getSize().x * 10 / 100)));

}

void GameScreen::mouseLeftPress(int index)
{
	std::cout << "index du clique !" << std::endl;
}

void GameScreen::draw()
{
	Singleton::getInstance()._window->clear();
	_t = Singleton::getInstance()._clock->restart();
	Singleton::getInstance()._animClock->restart();
	this->_map->draw(Singleton::getInstance()._window);

	//Singleton::getInstance()._window->draw(_statisticsText);

	//tmp.setPosition((pos.x-_map->getCamPos().x) * Chunk::SIZE_OF_CELL,(pos.y-_map->getCamPos().y) * Chunk::SIZE_OF_CELL);
	for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it)
	{
		(*it)->draw();
		//break;
	}

	for (auto it = _entities.begin(); it != _entities.end(); ++it)
	{
		(*it)->draw();
	}

	this->_map->drawMiniMap(Singleton::getInstance()._window);
	_physicEngine->setCamPos(_map->getCamPos());
	static bool test = true; //NNNNNNNNuuuuuuuuuuuuul²
	
	if (Singleton::getInstance().isKeyIPressed)
	{
		this->_inventory->_inventoryWindow->Show(test);
		if (test)
			switchTabs();
	
		test = !test;
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	}
	checkInput();

	if (Singleton::getInstance().isLeftClicking)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		sf::Vector2i _posSelectedArea = Singleton::getInstance().posLeftClickPressed;

		_posSelectedArea.x -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL);
		_posSelectedArea.y -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL);

		sf::RectangleShape selectionZone(sf::Vector2f(static_cast<float>(mousePos.x - _posSelectedArea.x),
			static_cast<float>(mousePos.y - _posSelectedArea.y)));
		selectionZone.setFillColor(sf::Color(255, 255, 255, 100));
		selectionZone.setOutlineColor(sf::Color::White);
		selectionZone.setOutlineThickness(2);
		selectionZone.setPosition(static_cast<float>(_posSelectedArea.x),
			static_cast<float>(_posSelectedArea.y));
		Singleton::getInstance()._window->draw(selectionZone);

	}
	this->_inventory->draw();
	updateStatistics(_t);

	Singleton::getInstance()._window->display();
}

void GameScreen::switchTabs()
{
	int compt = 0;
	for (Player *u : this->_players)
	{
		if (u->getSelected() == true)
		{
			if (this->_inventory->_tables[compt]->IsGloballyVisible() == false)
			{
				this->_inventory->_notebookfirst->Remove(this->_inventory->_tables[compt]);
				this->_inventory->_tables[compt]->Show(false);
				this->_inventory->_notebookfirst->InsertPage(this->_inventory->_tables[compt], sfg::Label::Create(u->getName()), compt);
				this->_inventory->_tables[compt]->Show(true);
			}
		}
		else
		{
			if (this->_inventory->_tables[compt]->IsGloballyVisible() == true)
			{
				this->_inventory->_notebookfirst->Remove(this->_inventory->_tables[compt]);
				this->_inventory->_tables[compt]->Show(false);
			}
		}
		++compt;
	}
	/*this->_inventory->_notebookfirst->

		this->_inventory->_notebookfirst->InsertPage(this->_inventory->_tableTest, sfg::Label::Create("label test"), 1);

	
		this->_inventory->_notebookfirst->Remove(this->_inventory->_tableTest);
		this->_inventory->_tableTest->Show(false);*/
	
	/*if (Singleton::getInstance().isKey1Pressed)
	{
		if (this->_inventory->_tableTest->IsGloballyVisible() == true)
			std::cout << "TRUUUUUUUUUUUUUUUUUUUUUUE" << std::endl;
		else
			std::cout << "FALLLLLLLLLLLLLLLLLLLLLLLLLLLLLSE" << std::endl;
		Singleton::getInstance().isKey1Pressed = !Singleton::getInstance().isKey1Pressed;
	}
	else if (Singleton::getInstance().isKey2Pressed)
	{
		Singleton::getInstance().isKey2Pressed = !Singleton::getInstance().isKey2Pressed;
	}
	else if (Singleton::getInstance().isKey3Pressed)
	{
		Singleton::getInstance().isKey3Pressed = !Singleton::getInstance().isKey3Pressed;
	}
	else if (Singleton::getInstance().isKey4Pressed)
	{
		Singleton::getInstance().isKey4Pressed = !Singleton::getInstance().isKey4Pressed;
	}*/
}


void GameScreen::update(void)
{


	_physicEngine->updatePos(_players, _entities);

	if (Singleton::getInstance().isLeftClicking)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		sf::Vector2i _posSelectedArea = Singleton::getInstance().posLeftClickPressed;

		_posSelectedArea.x -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL);
		_posSelectedArea.y -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL);

		sf::RectangleShape selectionZone(sf::Vector2f(static_cast<float>(mousePos.x - _posSelectedArea.x),
			static_cast<float>(mousePos.y - _posSelectedArea.y)));
		selectionZone.setPosition(static_cast<float>(_posSelectedArea.x),
			static_cast<float>(_posSelectedArea.y));


	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
			sf::RectangleShape tmp(sf::Vector2f(32, 32));

			sf::Vector2f posDisp;
			posDisp.x = (((*it)->getPosition().x - _map->_camera->_position.x) * Chunk::SIZE_OF_CELL);
			posDisp.y = (((*it)->getPosition().y - _map->_camera->_position.y) * Chunk::SIZE_OF_CELL);

			tmp.setPosition(posDisp);
			std::cout << tmp.getGlobalBounds().top << " / " << tmp.getGlobalBounds().left << std::endl;

			if (selectionZone.getGlobalBounds().intersects(tmp.getGlobalBounds()))
			{
				(*it)->setSelected(true);
			}
			else
			{
				(*it)->setSelected(false);
			}
		}

		std::cout << _posSelectedArea.x << ", " << std::endl;
	}

	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		
		(*it)->update();
	}
	for (auto it2 = _entities.begin(); it2 != _entities.end(); ++it2)
	{
		(*it2)->update();
	}
	_map->update();
	this->_inventory->update();
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
		std::cout << "Frames / Second = " <<  oss.str() << "\n" <<
			"Time / Update = " << oss2.str() << "us" << std::endl;;

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

