#include "Drops.h"
#include		"ImageSingleton.h"
#include		"ShadersManager.h"

void Drops::doAction(IEntity* other)
{
	//L'arbre ne fait rien
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

void Drops::setPosition(sf::Vector2f &pos)
{
	_position = pos;
}

sf::Vector2f Drops::getPosition() const
{
	return (_position);
}

void Drops::setPath(std::list<std::pair<float, float> >& path)
{

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

std::vector<IEntity *> &Drops::getDrops()
{
	return _drops;
}