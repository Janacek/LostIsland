#include "Game.h"

void Game::launch(void)
{
		Singleton::getInstance()._window = new sf::RenderWindow(sf::VideoMode(640, 480), "RType");
	GameScreen a;

a.initialize();

std::list<IEntity *> b;
	while (42)
	{
		Singleton::getInstance()._window->clear();
		a.draw(b);
		Singleton::getInstance()._window->display();
	}
}