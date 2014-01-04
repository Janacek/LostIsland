#include <sstream>
#include "InventaryWindow.h"
#include "Food.h"
#include "Wood.h"
#include "Water.h"
#include <iostream>


/// <summary>
/// Initializes a new instance of the <see cref="InventaryWindow"/> class. Set the position and Color of the sf::RectangleShape
/// </summary>
InventaryWindow::InventaryWindow(std::vector<Player *> &players, std::string  const &title) : _players(players), AWindow(title, 
																														 Singleton::getInstance()._window->getSize().x * 40 / 100, 
																														 Singleton::getInstance()._window->getSize().y * 80 / 100, 
																														 Singleton::getInstance()._window->getSize().x * 5 / 100, 
																														 Singleton::getInstance()._window->getSize().y / 10)
{
	this->_enumStrings[FOOD] = "FOOD";
	this->_enumStrings[WATER] = "WATER";
	this->_enumStrings[PLAYER] = "PLAYER";	

	createOnglets();
	players[0]->addEntityInInventory(new Food);
	players[0]->addEntityInInventory(new Food);
	players[1]->addEntityInInventory(new Water);
	players[1]->addEntityInInventory(new Water);
	players[1]->addEntityInInventory(new Food);
	players[1]->addEntityInInventory(new Food);
	players[2]->addEntityInInventory(new Wood);
	players[2]->addEntityInInventory(new Wood);
	players[2]->addEntityInInventory(new Wood);
	players[3]->addEntityInInventory(new Water);
	players[3]->addEntityInInventory(new Water);
	players[3]->addEntityInInventory(new Water);
	players[3]->addEntityInInventory(new Food);
	players[3]->addEntityInInventory(new Water);
	this->_selectOnglet = this->_onglets.front();
}

void InventaryWindow::createOnglets()
{
	std::ostringstream os;

	int nbPlayers = this->_players.size();
	float sizeXOnglet = this->_window.getSize().x / 4;
	float sizeYOnglet = this->_window.getSize().y * 5 / 100;
	int i = 0;
	for (Player *p : this->_players)
	{
		for (int i = 0; i < 9; i++)
			p->addCompartment(this->_window);
		os << i;
		p->setName("Player " + os.str());
		this->_onglets.push_back(new Onglet(p, p->getName(), sizeXOnglet, sizeYOnglet, this->_window.getPosition().x + (i * sizeXOnglet), this->_window.getPosition().y));
		++i;
		os.str("");
	}
	this->_onglets.front()->setisSelected(true);
}

void InventaryWindow::checkInputOnglet()
{
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	for (Onglet *o : this->_onglets)
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

void InventaryWindow::selectOnglet(Onglet *onglet)
{
	//couleur de l'onglet
	this->_selectOnglet->setisSelected(false);

	//selection de l'inventaire du perso a afficher
	this->_selectOnglet = onglet;
	this->_selectOnglet->setisSelected(true);
}

s_action InventaryWindow::clickInCompartment(sf::Vector2i &coordClick)
{
	s_action action(true);
	sf::Vector2i posLeftClickPressed = coordClick;
	for (Compartment *c : this->_selectOnglet->_player->_compartments)
	{
		float leftCompartment = c->_rect.getGlobalBounds().left;
		float rightCompartment = c->_rect.getGlobalBounds().width + leftCompartment;
		float topCompartment = c->_rect.getGlobalBounds().top;
		float bottomCompartment = topCompartment + c->_rect.getGlobalBounds().height;
		if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
		{
			//std::cout << "On est dans un compartiment" << std::endl;
			action._compartment = c;
			action._screen = INVENTORY;
			return action;
		}
	}
	return action;
}

//plus appelé 
bool InventaryWindow::isInCompartment(Compartment &c) const
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


void InventaryWindow::swapCompartment(s_action &pressed, s_action &released)
{

}
void InventaryWindow::addCompartment(s_action &, s_action &)
{

}

bool InventaryWindow::close()
{
	if (this->_close == true)
	{
		this->_close = false;
		return true;
	}
	return this->_close;
}

void InventaryWindow::update()
{
	checkInputOnglet();
	/*	clickInWindow();
	AWindow::checkClose();*/
}


/// <summary>
/// Adds the compartment. Calcul savant pour caller les cases en fonction de la size de la fenetre
/// </summary>
void InventaryWindow::addCompartment()
{
	float posIniX = this->_window.getPosition().x + this->_window.getSize().x / 10; //10% de marge
	if (this->_compartments.size() < 3)
	{
		float posRelatX = this->_compartments.size() * (this->_window.getSize().x * 5 / 100) + this->_compartments.size() * (this->_window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		//std::cout << "pos : " << posRelatX << std::endl;
		this->_compartments.push_back(new Compartment(this->_window.getSize(), posIniX + posRelatX, this->_window.getPosition().y + this->_window.getSize().y / 10)); //10% de marge);
	}
	else if (this->_compartments.size() < 6)
	{
		float posRelatX = (this->_compartments.size() - 3) * (this->_window.getSize().x * 5 / 100) + (this->_compartments.size() - 3) * (this->_window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		this->_compartments.push_back(new Compartment(this->_window.getSize(), posIniX + posRelatX, this->_window.getPosition().y + this->_window.getSize().y * 2 / 10 + this->_window.getSize().x * 23 / 100)); //10% de marge);
	}
	else
	{
		float posRelatX = (this->_compartments.size() - 6) * (this->_window.getSize().x * 5 / 100) + (this->_compartments.size() - 6) * (this->_window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		this->_compartments.push_back(new Compartment(this->_window.getSize(), posIniX + posRelatX, this->_window.getPosition().y + this->_window.getSize().y * 3 / 10 + this->_window.getSize().x * 23 / 100 * 2)); //10% de marge);
	}
}

void InventaryWindow::printInventory() const
{
	int i = 0;
	for (Compartment *u : this->_selectOnglet->_player->_compartments)
	{
		std::cout << "---------- CASE " << i << " ---------" << std::endl;
		for (IEntity *i : u->_elements)
		{
			std::cout << "- " <<  this->_enumStrings.at(i->getType()) << std::endl;
		}
		++i;
	}
}

void InventaryWindow::printInventory(Onglet *o) const
{
	int i = 0;
	for (Compartment *u : o->_player->_compartments)
	{
		std::cout << "---------- CASE " << i << " ---------" << std::endl;
		for (IEntity *i : u->_elements)
		{
			std::cout << "- " <<  this->_enumStrings.at(i->getType()) << std::endl;
		}
		++i;
	}
}

void InventaryWindow::draw()
{
	AWindow::draw();
	for (Onglet *o : this->_onglets)
	{
		o->draw();
	}
	for (Compartment *u : this->_selectOnglet->_player->_compartments)
		u->draw();
}

InventaryWindow::~InventaryWindow(void)
{
}
