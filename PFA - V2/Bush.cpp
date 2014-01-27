#include "Bush.h"

void Bush::Animate(std::string const &)
{

}

void Bush::draw()
{
	//std::cout << "zefzef" << std::endl;
	int posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	int posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20;

	//std::cout << posX << std::endl;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y);
	Singleton::getInstance()._window->draw(tmp);
}