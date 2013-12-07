#pragma once

#include "Singleton.h"
#include "IEntity.h"
#include <list>

//Attention : Type T shall be copy-constructible and assignable.
class Compartment
{
public:
	Compartment(float posX, float posY);
	~Compartment();
	void draw();
	void addElement(IEntity *);
	void delElement();


	sf::RectangleShape _rect;
	std::list<IEntity *> _elements;

private:
	void applyPicture(Type);
};