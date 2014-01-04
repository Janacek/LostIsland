#include <iostream>
#include "Food.h"
#include "Wood.h"
#include "Water.h"
#include "Inventory.h"

Inventory::Inventory(std::vector<Player *> &players) : _players(players)
{
	this->_enumStrings[WOOD] = "WOOD";
	this->_enumStrings[FOOD] = "FOOD";
	this->_enumStrings[WATER] = "WATER";
	this->_enumStrings[PLAYER] = "PLAYER";
	this->_mainInventory = new InventaryWindow(players);
	for (int i = 0; i < 9; i++)
		this->_mainInventory->addCompartment();
	this->_sizeInventory = 0;
	players[0]->_inventary.push_back(new Food);
	players[0]->_inventary.push_back(new Food);
	players[1]->_inventary.push_back(new Water);
	players[1]->_inventary.push_back(new Water);
	players[1]->_inventary.push_back(new Food);
	players[1]->_inventary.push_back(new Food);
	players[2]->_inventary.push_back(new Wood);
	players[2]->_inventary.push_back(new Wood);
	players[2]->_inventary.push_back(new Wood);
	players[3]->_inventary.push_back(new Water);
	players[3]->_inventary.push_back(new Water);
	players[3]->_inventary.push_back(new Water);
	players[3]->_inventary.push_back(new Food);
	players[3]->_inventary.push_back(new Water);
	this->_selectOnglet = this->_mainInventory->_onglets.front();
	updateViewCompartments();
}

bool Inventory::close() const
{
	return this->_mainInventory->close();
}

void Inventory::update()
{
	checkInputOnglet();
	this->_mainInventory->update();
}

void Inventory::checkInputOnglet()
{
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	for (Onglet *o : this->_mainInventory->_onglets)
	{
		float leftCompartment = o->getGlobalBounds().left;
		float rightCompartment = o->getGlobalBounds().width + leftCompartment;
		float topCompartment = o->getGlobalBounds().top;
		float bottomCompartment = topCompartment + o->getGlobalBounds().height;
		if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
		{
			Singleton::getInstance().posLeftClickPressed.x = -1;
			if (o != this->_selectOnglet)
				this->selectOnglet(o);
			//std::cout << "J'ai cliqué sur l'onglet : " << o->getName() << std::endl;
			return ;
		}
	}

}

void Inventory::updateViewCompartments()
{
	for (Compartment *c : this->_mainInventory->_compartments)
		c->emptyCompartment();
	this->_sizeInventory = 0;
	for (IEntity *u : this->_selectOnglet->_player->_inventary)
		this->addEntityInInventory(u);
	printInventory();
}

void Inventory::selectOnglet(Onglet *onglet)
{
	//couleur de l'onglet
	this->_selectOnglet->setisSelected(false);
	this->_selectOnglet = onglet;
	this->_selectOnglet->setisSelected(true);
	updateViewCompartments();
}

void Inventory::draw()
{
	//this->update();
	this->_mainInventory->draw();
}

bool Inventory::isInCompartment(Compartment &c) const
{
	float leftCompartment = c._rect.getGlobalBounds().left;
	float rightCompartment = c._rect.getGlobalBounds().width + leftCompartment;
	float topCompartment = c._rect.getGlobalBounds().top;
	float bottomCompartment = topCompartment + c._rect.getGlobalBounds().height;
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	sf::Vector2i posRightClickPressed = Singleton::getInstance().posRightClickPressed;

	if (posLeftClickPressed.x != -1 && !c.isSelected() && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
	{
		c.setIsSelected(true);
		Singleton::getInstance().posLeftClickPressed.x = -1;
		Singleton::getInstance().posRightClickPressed.x = -1;
		return true;
	}
	if (posRightClickPressed.x != -1 && c.isSelected() && leftCompartment <= posRightClickPressed.x && rightCompartment >= posRightClickPressed.x && topCompartment <= posRightClickPressed.y && bottomCompartment >= posRightClickPressed.y)
	{
		c.setIsSelected(false);
		Singleton::getInstance().posLeftClickPressed.x = -1;
		Singleton::getInstance().posRightClickPressed.x = -1;
		return true;
	}
	return false;
}

void Inventory::checkInputs()
{
	for (Compartment *u : this->_mainInventory->_compartments)
	{
		if (isInCompartment(*u))
		{

		}
	}
}

/// <summary>
/// Adds the entity information inventory. Ajoute seulement pour l'affichage mais pas dans l'inventaire du player
/// </summary>
/// <param name="entity">The entity.</param>
void Inventory::addEntityInInventory(IEntity *entity)
{
	int i = 0;

	Type tmpType = entity->getType();
	//std::cout << "SIZE : " << this->_mainInventory._compartments.size() << std::endl;
	for (Compartment *u : this->_mainInventory->_compartments)
	{
		if (u->_elements.size() != 0 && u->_elements.front()->getType() == tmpType)
		{
			u->addElement(entity);
			return ;
		}
	}
	if (this->_sizeInventory < 6)
	{
		this->_mainInventory->_compartments[this->_sizeInventory]->addElement(entity);
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
		--this->_sizeInventory;
	}
}

//n'est plus utilisée
void Inventory::organizeCompartment(Compartment *comp)
{
	int size = 0;
	if (this->_sizeInventory != 0)
		size = _sizeInventory - 1;
	comp->_elements = this->_mainInventory->_compartments[size]->_elements;
	comp->_rect = this->_mainInventory->_compartments[size]->_rect;
	this->_mainInventory->_compartments[size]->_elements.clear();
}

Inventory::~Inventory(void)
{
}

void Inventory::printInventory() const
{
	int i = 0;
	for (Compartment *u : this->_mainInventory->_compartments)
	{
		std::cout << "---------- CASE " << i << " ---------" << std::endl;
		for (IEntity *i : u->_elements)
		{
			std::cout << "- " <<  this->_enumStrings.at(i->getType()) << std::endl;
		}
		++i;
	}
}