#include "Food.h"


Food::Food(void)
{
	_pos = sf::Vector2f(0,0);
}

void Food::doAction(IEntity* other)
{
	//De la food sauvage apparait
}

void Food::getAction(IEntity* other)
{

}

void Food::Animate(std::string const & string_anim)
{

}

int Food::getDamage() const
{
	return 0;
}

void Food::draw()
{

}

void Food::setPosition(sf::Vector2f &pos)
{
	_pos = pos;
}

sf::Vector2f  Food::getPosition() const
{
	return _pos;
}

void Food::setPath(std::list<sf::Vector2f > &path)
{
	_path = path;
}


Type Food::getType() const
{
	return FOOD;
}

Food::~Food(void)
{
}
