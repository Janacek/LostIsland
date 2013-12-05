#include "Compartment.h"


Compartment::Compartment(float posX, float posY)
{
	this->_rect = sf::RectangleShape(sf::Vector2f(50, 50));
	this->_rect.setPosition(posX, posY);
}


Compartment::~Compartment(void)
{
}
