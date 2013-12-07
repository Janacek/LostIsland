#include <iostream>
#include "Inventory.h"

Inventory::Inventory(void)
{
	this->_mainInventory = sf::RectangleShape(sf::Vector2f(Singleton::getInstance()._window->getSize().x / 2, Singleton::getInstance()._window->getSize().y / 2));
	this->_mainInventory.setFillColor(sf::Color::Blue);
	for (int i = 0; i < 6; i++)
	{
		this->_compartment.push_back(Compartment(Singleton::getInstance()._window->getSize().x / 10, Singleton::getInstance()._window->getSize().y / 10));
	}
	this->_compartment[0]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10, 50);
	this->_compartment[0]._rect.setFillColor(sf::Color::Red);
	this->_compartment[1]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10 * 2, 50);
	this->_compartment[1]._rect.setFillColor(sf::Color::Red);
	this->_compartment[2]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10 * 3, 50);
	this->_compartment[2]._rect.setFillColor(sf::Color::Red);
	this->_compartment[3]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10, 200);
	this->_compartment[3]._rect.setFillColor(sf::Color::Red);
	this->_compartment[4]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10 * 2, 200);
	this->_compartment[4]._rect.setFillColor(sf::Color::Red);
	this->_compartment[5]._rect.setPosition(Singleton::getInstance()._window->getSize().x / 10 * 3, 200);
	this->_compartment[5]._rect.setFillColor(sf::Color::Red);
}

void Inventory::update()
{

}

void Inventory::draw()
{
	Singleton::getInstance()._window->draw(this->_mainInventory);
	for (Compartment u : _compartment)
	{
		Singleton::getInstance()._window->draw(u._rect);
	}
}

void Inventory::addEntityInInventory(IEntity *entity)
{
	//TODO : tester si elle existe deja dans l'inventaire et l'ajouter dans la premiere case libre
}

void Inventory::deleteEntityInInventory(IEntity *entity)
{
	
}

Inventory::~Inventory(void)
{
}
