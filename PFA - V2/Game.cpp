#include "Player.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "Game.h"

Game::Game(void) 
{

}

Game::~Game(void)
{
}

void Game::init()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	srand((unsigned int)time(NULL));
	Singleton& ptr1 = Singleton::getInstance();
	
	ImageManager::getInstance().start();
	//ptr1._window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Lost Island");
	ptr1._window = new sf::RenderWindow(*videoMode.getFullscreenModes().begin(), "Lost Island", sf::Style::Fullscreen);
	ptr1._window->setVerticalSyncEnabled(true);
	ptr1._window->setFramerateLimit(200);

	ptr1._window->setActive(false);
	ptr1._clock = new sf::Clock();
	ptr1._clock->restart();
	_states.push_front( new StartScreen() );
	_states.front()->initialize();
	
	this->_graphicEngine = new GraphicEngine( this->_states);
	this->_gameEngine = new GameEngine(this->_states);
	this->_gameEngine->init();
	
}


void Game::launch(void)
{
	this->init();

	/*
	** Instantiation du graphical engine + threading;
	*/

	sf::Thread *graphicalThread = new sf::Thread(&GraphicEngine::run, _graphicEngine);

	graphicalThread->launch();
	while (true)
	{
		if (_gameEngine->getIsRunning() == false)
		{
			std::cout << "Quitting the game" << std::endl;
			break;
		}
		
		_gameEngine->update();
		sf::sleep(sf::Time(sf::microseconds(200)));
	}
}