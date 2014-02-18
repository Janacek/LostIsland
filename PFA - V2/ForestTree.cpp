#include "ForestTree.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include "Map.h"

void ForestTree::Animate(std::string const &)
{

}

void ForestTree::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	sf::Sprite tmp((*ImageSingleton::getInstance().get(TREE)));
	tmp.setPosition(_position.x, _position.y);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void ForestTree::draw(sf::RenderTexture *tex)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	sf::Sprite tmp((*ImageSingleton::getInstance().get(TREE)));
	tmp.setPosition(_position.x, _position.y);
	tex->draw(tmp);
}

void ForestTree::update(Map &map)
{
	if (_duration <= 0)
	{
		//map.getEntitiesMap[_position.x][_position.y] = NULL;
	}
}

void ForestTree::doAction(IEntity *other)
{
	// Do nothing
}

void ForestTree::getAction(IEntity *other)
{
	_duration -= other->getDamage();
}