#include <iostream>
#include "Food.h"
#include "Wood.h"
#include "Water.h"
#include "Inventory.h"

Inventory::Inventory(std::vector<Player *> &players) : _players(players)
{
// 	this->_enumStrings[WOOD] = "WOOD";
// 	this->_enumStrings[FOOD] = "FOOD";
// 	this->_enumStrings[WATER] = "WATER";
// 	this->_enumStrings[PLAYER] = "PLAYER";
	//this->_mainInventory = new InventaryWindow(players);
 	//for (int i = 0; i < 9; i++)
 		//this->_mainInventory->addCompartment();


// 	players[0]->addEntityInInventory(new Food);
// 	players[0]->addEntityInInventory(new Food);
// 	players[1]->addEntityInInventory(new Water);
// 	players[1]->addEntityInInventory(new Water);
// 	players[1]->addEntityInInventory(new Food);
// 	players[1]->addEntityInInventory(new Food);
// 	players[2]->addEntityInInventory(new Wood);
// 	players[2]->addEntityInInventory(new Wood);
// 	players[2]->addEntityInInventory(new Wood);
// 	players[3]->addEntityInInventory(new Water);
// 	players[3]->addEntityInInventory(new Water);
// 	players[3]->addEntityInInventory(new Water);
// 	players[3]->addEntityInInventory(new Food);
// 	players[3]->addEntityInInventory(new Water);
	this->_selectOnglet = this->_mainInventory->_onglets.front();
}

bool Inventory::close() const
{
	return this->_mainInventory->close();
}

void Inventory::update()
{

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
			return ;
		}
	}

}

void Inventory::selectOnglet(Onglet *onglet)
{
	//couleur de l'onglet
	this->_selectOnglet->setisSelected(false);

	//selection de l'inventaire du perso a afficher
	this->_selectOnglet = onglet;
	this->_selectOnglet->setisSelected(true);
}

void Inventory::draw()
{
	//this->update();
	this->_mainInventory->draw();
	for (Compartment *u : this->_selectOnglet->_player->_compartments)
		u->draw();
}

/// <summary>
/// Adds the entity information inventory. Ajoute seulement pour l'affichage mais pas dans l'inventaire du player
/// </summary>
/// <param name="entity">The entity.</param>
void Inventory::addEntityInInventory(IEntity *entity)
{
// 	int i = 0;
// 
// 	Type tmpType = entity->getType();
// 	//std::cout << "SIZE : " << this->_mainInventory._compartments.size() << std::endl;
// 	for (Compartment *u : this->_mainInventory->_compartments)
// 	{
// 		if (u->_elements.size() != 0 && u->_elements.front()->getType() == tmpType)
// 		{
// 			u->addElement(entity);
// 			return ;
// 		}
// 	}
// 	if (this->_sizeInventory < 6)
// 	{
// 		this->_mainInventory->_compartments[this->_sizeInventory]->addElement(entity);
// 		++this->_sizeInventory;
// 	}
// 	else
// 	{
// 		std::cout << "Inventaire plein !!!" << std::endl;
// 	}
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

Inventory::~Inventory(void)
{
}

