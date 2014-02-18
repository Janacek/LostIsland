#include "Bush.h"
#include "Singleton.h"
#include "ImageSingleton.h"

Bush::Bush()
{
	_grown = false;
	_bushClock.restart();
	_oldDt = 0.f;
	_timeToGrow = rand() % 60 + 15;
	_growthTime = 0.f;
}

void Bush::Animate(std::string const &)
{

}

void Bush::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	sf::Sprite tmp;
	if (_grown)
		tmp.setTexture((*ImageSingleton::getInstance().get(BUSH_FRUITS)));
	else
		tmp.setTexture((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Bush::draw(sf::RenderTexture *tex)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	sf::Sprite tmp;
	if (_grown)
		tmp.setTexture((*ImageSingleton::getInstance().get(BUSH_FRUITS)));
	else
		tmp.setTexture((*ImageSingleton::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

void Bush::update(Map &)
{
	double dt = 0;
	double time;

	time = _bushClock.getElapsedTime().asSeconds();
	dt = time - _oldDt;

	_oldDt = time;
	_growthTime += dt;
	if (_growthTime > _timeToGrow)
	{
		_grown = true;
	}
}

void Bush::doAction(IEntity *other)
{
	// do nothing
}

void Bush::getAction(IEntity *other)
{
	_grown = false;
	_growthTime = 0.f;
	// GIVE FOOD TO THE OTHER ENTITY
}