#include "Compartment.h"
#include <sstream>
#include <iostream>

Compartment::Compartment(const sf::Vector2f &sizeParent, float x, float y)
{
	this->_numberElements = 0;
	this->_isSelected = false;
	this->_rect = sf::RectangleShape(sf::Vector2f(sizeParent.x * 16 / 100, sizeParent.x * 16 / 100));
	this->_rect.setFillColor(sf::Color::Magenta);
	this->_rect.setPosition(x, y);
	this->_rect.setOutlineColor(sf::Color::Red);
	this->_font.loadFromFile("./Media/Sansation.ttf");
	this->_textNumber.setFont(this->_font);
	this->_textNumber.setPosition(x, y);
	this->_textNumber.setCharacterSize(30);
	this->_textNumber.setColor(sf::Color::Green);
}

void Compartment::emptyCompartment()
{
	this->_elements.clear();
	this->_textNumber.setString("");
	this->_numberElements = 0;
}

void Compartment::setIsSelected(bool b)
{
	this->_isSelected = b;
	if (b)
	{
		std::cout << "JE SUIS SELEC" << std::endl;
		this->_rect.setOutlineThickness(10);
	}
	else
	{
		std::cout << "JE SUIS PAS SELECT" << std::endl;
		this->_rect.setOutlineThickness(0);
	}
}

bool Compartment::isSelected() const
{
	return this->_isSelected;
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
	else //Si c'est z�ro
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