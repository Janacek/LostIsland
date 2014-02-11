#include "Bush.h"

void Bush::Animate(std::string const &)
{

}

void Bush::draw(sf::RenderTexture *tex)
{
	//std::cout << "zefzef" << std::endl;
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	//std::cout << posX << std::endl;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
	//Singleton::getInstance()._window->draw(tmp);
}