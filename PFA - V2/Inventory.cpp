#include <iostream>
#include "Food.h"
#include "Wood.h"
#include "Water.h"
#include "Inventory.h"

Inventory::Inventory(void)
{
	this->_enumStrings[WOOD] = "WOOD";
	this->_enumStrings[FOOD] = "FOOD";
	this->_enumStrings[WATER] = "WATER";
	this->_enumStrings[PLAYER] = "PLAYER";
	this->_mainInventory = InventaryWindow();
	for (int i = 0; i < 6; i++)
	{
		this->_mainInventory.addCompartment();
		this->_compartment.push_back(new Compartment());
	}
	this->_compartment[0]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10, 50);
	this->_compartment[0]->_rect.setFillColor(sf::Color::Red);
	this->_compartment[1]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10 * 2, 50);
	this->_compartment[1]->_rect.setFillColor(sf::Color::Red);
	this->_compartment[2]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10 * 3, 50);
	this->_compartment[2]->_rect.setFillColor(sf::Color::Red);
	this->_compartment[3]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10, 200);
	this->_compartment[3]->_rect.setFillColor(sf::Color::Red);
	this->_compartment[4]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10 * 2, 200);
	this->_compartment[4]->_rect.setFillColor(sf::Color::Red);
	this->_compartment[5]->setCompartmentPosition((float)Singleton::getInstance()._window->getSize().x / 10 * 3, 200);
	this->_compartment[5]->_rect.setFillColor(sf::Color::Red);
	this->_sizeInventory = 0;
	addEntityInInventory(new Food);
	addEntityInInventory(new Food);
	addEntityInInventory(new Water);
	addEntityInInventory(new Water);
	addEntityInInventory(new Water);
	addEntityInInventory(new Water);
	addEntityInInventory(new Water);
	addEntityInInventory(new Wood);
	addEntityInInventory(new Wood);
	printInventory();
}

void Inventory::update()
{

}

void Inventory::draw()
{
	this->_mainInventory.draw();
// 	for (Compartment *u : _compartment)
// 	{
// 		u->draw();
// 	}
}

bool Inventory::isInCompartment(Compartment &c) const
{
	float leftCompartment = c._rect.getGlobalBounds().left;
	float rightCompartment = c._rect.getGlobalBounds().width + leftCompartment;
	float topCompartment = c._rect.getGlobalBounds().top;
	float bottomCompartment = topCompartment + c._rect.getGlobalBounds().height;
	sf::Vector2f posLeftClick = Singleton::getInstance().posLeftClick;

	if (leftCompartment <= posLeftClick.x && rightCompartment >= posLeftClick.x && topCompartment <= posLeftClick.y && bottomCompartment >= posLeftClick.y)
		return true;
	return false;
}

void Inventory::checkInputs()
{
	for (Compartment *u : this->_compartment)
	{
		if (isInCompartment(*u))
			std::cout << "Il est dans le compartiment !" << std::endl;
	}
}

void Inventory::addEntityInInventory(IEntity *entity)
{
	int i = 0;

	Type tmpType = entity->getType();
	for (Compartment *u : _compartment)
	{
		if (u->_elements.size() != 0 && u->_elements.front()->getType() == tmpType)
		{
			u->addElement(entity);
			return ;
		}
	}
	if (this->_sizeInventory < 6)
	{
		this->_compartment[this->_sizeInventory]->addElement(entity);
		++this->_sizeInventory;
	}
	else
	{
		std::cout << "Inventaire plein !!!" << std::endl;
	}
}

void Inventory::deleteEntityInInventory(Compartment *compartment)
{
	if (compartment->_elements.size() == 0)
	{
		std::cout << "Compartiment vide !" << std::endl;
		return ;
	}
	compartment->delElement();
	if (compartment->_elements.size() == 0)
	{
		organizeCompartment(compartment);
		--this->_sizeInventory;
	}
}

void Inventory::organizeCompartment(Compartment *comp)
{
	int size = 0;
	if (this->_sizeInventory != 0)
		size = _sizeInventory - 1;
	comp->_elements = this->_compartment[size]->_elements;
	comp->_rect = this->_compartment[size]->_rect;
	this->_compartment[size]->_elements.clear();
}

Inventory::~Inventory(void)
{
}

void Inventory::printInventory() const
{
	int i = 0;
	for (Compartment *u : this->_compartment)
	{
		std::cout << "---------- CASE " << i << " ---------" << std::endl;
		for (IEntity *i : u->_elements)
		{
			std::cout << "- " <<  this->_enumStrings.at(i->getType()) << std::endl;
		}
		++i;
	}
}