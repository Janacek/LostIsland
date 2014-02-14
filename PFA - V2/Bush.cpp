#include "Bush.h"

void Bush::Animate(std::string const &)
{

}

void Bush::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Bush::draw(sf::RenderTexture *tex)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	sf::Sprite tmp((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}