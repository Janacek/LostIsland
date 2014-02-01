#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "GameScreen.h"

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
	this->_isFirst = true;
	_physicEngine->init();
}

void GameScreen::events(sf::Event &e)
{
	this->_inventory->_desktop.HandleEvent(e);
	checkDrop(e);
}

///Ici on obtient la ressource sur laquelle le playeur a appuyé dans l'inventaire
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
	std::cout << "Avant de valdierjfirff " << this->_dropCompartment->getSize() << std::endl;
	std::cout << "Je valide !!!! f!f!eikerjfgerujuj" << std::endl;
	//Fonction appelée lorsque qu'on a choisi le nbr de ressources qu'on voulait jeter de l'inventaire
	//list contient mtn le bon nombre de ressources 
	std::list<IEntity *> list = this->_dropCompartment->getElements(nbrDrop);
	this->_dropCompartment->delAllElement();
}

void GameScreen::initialize(void)
{
	for (int i = 0; i < 2; i++)
	{
		Player *p = new Player(sf::Vector2f(60 + i * 3, 100), &_camera);
		p->loadAnimation("zelda.png", 0.1f);
		this->_players.push_back(p);
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

void GameScreen::mouseLeftPress(int index)
{
	std::cout << "index du clique !" << std::endl;
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
	for (std::vector<Player *>::iterator it = _players.begin() ; it != _players.end() ; ++it)
	{
		(*it)->draw();
		//break;
	}
	this->_map->drawMiniMap(Singleton::getInstance()._window);
	_physicEngine->setCamPos(_map->getCamPos());
	_physicEngine->update();
	static bool test = true;
	if (Singleton::getInstance().isKeyIPressed)
	{
		this->_inventory->_inventoryWindow->Show(test);
		test = !test;
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	}
	checkInput();
	this->_inventory->draw();
	Singleton::getInstance()._window->display();
}


void GameScreen::update(void)
{
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
	for(std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it)
	{
		(*it)->update();
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

