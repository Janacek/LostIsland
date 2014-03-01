#include "Drops.h"
#include		"ImageManager.h"
#include		"ShadersManager.h"

Drops::Drops()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Drops::doAction(AEntity* other)
{
	
}


void Drops::getAction(AEntity* other)
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
	sf::Sprite tmp((*ImageManager::getInstance().get(DROPS)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Drops::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp((*ImageManager::getInstance().get(DROPS)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

void Drops::addDrop(AEntity *drop)
{
	_drops.push_back(drop);
}

void Drops::addDrop(std::list<AEntity *>list)
{
	this->_drops = list;
}

std::list<AEntity *> &Drops::getDrops()
{
	return _drops;
}