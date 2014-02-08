#include "ForestTree.h"

void ForestTree::Animate(std::string const &)
{

}

void ForestTree::draw()
{
	//std::cout << "zefzef" << std::endl;
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	//std::cout << posX << std::endl;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(TREE)));
	tmp.setPosition(_position.x, _position.y);
	Singleton::getInstance()._window->draw(tmp);
}