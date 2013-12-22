#pragma once

#include "Singleton.h"
#include "ImageSingleton.h"
#include "IEntity.h"
#include "Player.h"
#include <list>

//Attention : Type T shall be copy-constructible and assignable.
class Compartment
{
public:
	Compartment(const sf::Vector2f &sizeParent, float x, float y);
	~Compartment();
	void draw();
	void addElement(IEntity *);
	void delElement();
	void setCompartmentPosition(float x, float y);
	void setIsSelected(bool);
	bool isSelected() const;
	void emptyCompartment();

	sf::RectangleShape _rect;
	std::list<IEntity *> _elements;
	sf::Text			_textNumber;
	sf::Font			_font;
	

private:
	bool				_isSelected;
	unsigned int _numberElements;
	void applyPicture(Type);
	void increaseNumber();
	void decreaseNumber();
};