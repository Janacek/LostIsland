#include "Compartment.h"


Compartment::Compartment(float posX, float posY)
{
	this->_rect = sf::RectangleShape(sf::Vector2f(50, 50));
	this->_rect.setPosition(posX, posY);
}

void Compartment::draw()
{
	Singleton::getInstance()._window->draw(this->_rect);
}

void Compartment::addElement(IEntity *entity)
{
	this->_elements.push_back(entity);
	if (this->_elements.size() == 0)
		applyPicture(entity->getType());
}

void Compartment::applyPicture(Type type)
{
	
}

Compartment::~Compartment(void)
{
	for (IEntity *u : this->_elements)
	{
		delete(u);
	}
	while (!this->_elements.size())
		this->_elements.pop_back();
}
