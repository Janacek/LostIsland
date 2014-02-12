#include "PalmTree.h"

void PalmTree::Animate(std::string const &)
{

}

void PalmTree::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	//std::cout << "zefzef" << std::endl;
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	//std::cout << posX << std::endl;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(PALMTREE)));
	tmp.setPosition(_position.x, _position.y);
	Singleton::getInstance()._glowShader.setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(tmp, &Singleton::getInstance()._glowShader);
	//Singleton::getInstance()._window->draw(tmp);
}

void PalmTree::draw(sf::RenderTexture *tex)
{
	//std::cout << "zefzef" << std::endl;
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	//std::cout << posX << std::endl;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(PALMTREE)));
	tmp.setPosition(_position.x, _position.y);
	tex->draw(tmp);
	//Singleton::getInstance()._window->draw(tmp);
}