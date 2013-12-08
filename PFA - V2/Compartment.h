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
	void setCompartmentPosition(float x, float y);

	sf::RectangleShape _rect;
	std::list<IEntity *> _elements;
	sf::Text			_textNumber;
	sf::Font			_font;

private:
	unsigned int _numberElements;
	void applyPicture(Type);
	void increaseNumber();
	void decreaseNumber();
};