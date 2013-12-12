#include "Compartment.h"
#include <sstream>
#include <iostream>

Compartment::Compartment()
{
	this->_numberElements = 0;
	this->_rect = sf::RectangleShape(sf::Vector2f(50, 50));
	this->_font.loadFromFile("./Media/Sansation.ttf");
	this->_textNumber.setFont(this->_font);
	this->_textNumber.setCharacterSize(30);
	this->_textNumber.setColor(sf::Color::Green);
}

void Compartment::setCompartmentPosition(float x, float y)
{
	this->_rect.setPosition(x, y);
	this->_textNumber.setPosition(x, y);
}

void Compartment::draw()
{
	Singleton::getInstance()._window->draw(this->_rect);
	Singleton::getInstance()._window->draw(this->_textNumber);

}

void Compartment::delElement()
{
	if (this->_elements.size() != 0)
	{
		this->_numberElements--;
		decreaseNumber();
	}
}

void Compartment::addElement(IEntity *entity)
{
	++this->_numberElements;
	if (this->_elements.size() == 0)
		applyPicture(entity->getType());
	increaseNumber();
	this->_elements.push_back(entity);
}

void Compartment::increaseNumber()
{
	if (this->_numberElements > 1)
	{
		std::ostringstream tmp;

		tmp << this->_numberElements;

		this->_textNumber.setString(tmp.str());
	}
}

void Compartment::decreaseNumber()
{
	if (this->_numberElements > 1)
	{
		std::ostringstream tmp;

		tmp << this->_numberElements;
		this->_textNumber.setString(tmp.str());
	}
	else if (this->_numberElements == 1)
	{
		this->_textNumber.setString("");
	}
	else //Si c'est zéro
	{
		//TODO supprimer la photo
	}
}

void Compartment::applyPicture(Type type)
{
	//TODO mettre le sprite qui correspond au type
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
