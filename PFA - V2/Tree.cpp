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

void Tree::update()
{
	
}

void Tree::loadAnimation(std::string const & string_anim)
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
	//std::cout << "zefzef" << std::endl;
	int posX = _position.x - Singleton::getInstance()._window->getSize().x;
	int posY = _position.y - Singleton::getInstance()._window->getSize().y;

	//std::cout << posX << std::endl;
	
	sf::Sprite tmp((*ImageSingleton::getInstance().get(TREE)));
	tmp.setPosition(posX, posY);
	Singleton::getInstance()._window->draw(tmp);
}


/*sf::Rect & Tree::getCollisionBox(void)
{
}*/
