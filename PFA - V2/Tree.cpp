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

void Tree::Animate(std::string const & string_anim)
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

/*sf::Rect & Tree::getCollisionBox(void)
{
}*/
