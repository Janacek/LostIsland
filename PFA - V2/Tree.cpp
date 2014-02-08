#include "Tree.h"

void Tree::doAction(IEntity* other)
{
	//L'arbre ne fait rien
}


void Tree::getAction(IEntity* other)
{
	if (this->_damages < other->getDamage())
		this->_damages = 0;
	if (this->_damages == 0)
	{
		//On doit faire apparaitre de la Wood
	}
}

void Tree::update(Map &map)
{
	
}

void Tree::loadAnimation(std::string const & string_anim, float speed)
{
}

//Pas de dommages
int Tree::getDamage(void) const
{
	return this->_damages;
}

Type Tree::getType() const
{
	return TREE;
}

void Tree::setPosition(sf::Vector2f &pos)
{
	_position = pos;
}

sf::Vector2f Tree::getPosition() const
{
	return (_position);
}

void Tree::setPath(std::list<std::pair<float, float> >& path)
{
		
}

void Tree::draw()
{

}


/*sf::Rect & Tree::getCollisionBox(void)
{
}*/
