#include "Player.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include "Game.h"
#include "Thread.hh"

Game::Game(void) 
{

}

Game::~Game(void)
{
}

void Game::init()
{
	srand((unsigned int)time(NULL));
	Singleton& ptr1 = Singleton::getInstance();
	ImageSingleton::getInstance().start();
	ptr1._window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Lost Island");
	ptr1._window->setFramerateLimit(60);

	ptr1._window->setActive(false);

	ptr1._clock = new sf::Clock();
	ptr1._clock->restart();

	//_states.push()
	_states.push( new StartScreen() );
	_states.top()->initialize();
	
	this->_graphicEngine = new GraphicEngine( this->_states);
	this->_gameEngine = new GameEngine(this->_states);
	//this->_physicEngine = new PhysicEngine(map, this->_states);

	//this->_graphicEngine->init();
	this->_gameEngine->init();
	
}


void Game::launch(void)
{
	this->init();

	/*
	** Instantiation du graphical engine + threading;
	*/

	Thread *graphicalThread = new Thread(&GraphicEngine::run, _graphicEngine);

	graphicalThread->launch();
	while (true)
	{
		/*if (_graphicEngine->getIsRunning() == false)
			break;*/
		if (_gameEngine->getIsRunning() == false)
		{
			break;
		}
		
		//j'aimerais savoir si on est en jeu ou pas 
		
		//_graphicEngine->update(_players, _entities);
		//_graphicEngine->draw(_players, _entities);
		_gameEngine->update();
		
	}
}