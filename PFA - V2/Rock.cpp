#include "Rock.h"

void Rock::doAction(IEntity* other)
{
	//L'arbre ne fait rien
}


void Rock::getAction(IEntity* other)
{

}

void Rock::update(Map &map)
{
}

void Rock::loadAnimation(std::string const & string_anim, float speed)
{
}

//Pas de dommages
int Rock::getDamage(void) const
{
	return this->_damages;
}

Type Rock::getType() const
{
	return ROCK;
}

void Rock::setPosition(sf::Vector2f &pos)
{
	_position = pos;
}

sf::Vector2f Rock::getPosition() const
{
	return (_position);
}

void Rock::setPath(std::list<std::pair<float, float> >& path)
{

}

void Rock::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	sf::Sprite tmp((*ImageSingleton::getInstance().get(ROCK)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Rock::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp((*ImageSingleton::getInstance().get(ROCK)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}


/*sf::Rect & Rock::getCollisionBox(void)
{
}*/