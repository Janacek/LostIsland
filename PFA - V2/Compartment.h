#pragma once

#include "IEntity.h"
#include <list>

class Compartment
{
public:
	Compartment(float posX, float posY);
	~Compartment();
	sf::RectangleShape _rect;
	std::list<IEntity *> _elements;
};