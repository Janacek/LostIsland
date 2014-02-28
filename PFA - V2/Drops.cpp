#include "Drops.h"
#include		"ImageSingleton.h"
#include		"ShadersManager.h"

Drops::Drops()
: IEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Drops::doAction(IEntity* other)
{
	
}


void Drops::getAction(IEntity* other)
{

}

void Drops::update(Map &map)
{
	
}

void Drops::loadAnimation(std::string const & string_anim, float speed)
{
}

Type Drops::getType() const
{
	return DROPS;
}

void Drops::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	sf::Sprite tmp((*ImageSingleton::getInstance().get(DROPS)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Drops::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp((*ImageSingleton::getInstance().get(DROPS)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

void Drops::addDrop(IEntity *drop)
{
	_drops.push_back(drop);
}

void Drops::addDrop(std::list<IEntity *>list)
{
	this->_drops = list;
}

std::list<IEntity *> &Drops::getDrops()
{
	return _drops;
}