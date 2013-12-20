#include <sstream>
#include "InventaryWindow.h"
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
	createOnglets();
	
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
		os << i;
		p->setName("Player " + os.str());
		this->_onglets.push_back(new Onglet(p, p->getName(), sizeXOnglet, sizeYOnglet, this->_window.getPosition().x + (i * sizeXOnglet), this->_window.getPosition().y));
		++i;
		os.str("");
	}
	this->_onglets.front()->setisSelected(true);
}


 s_action Stuff::clickInCompartment()
{
	 s_action action;
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	for (Compartment *c : this->_compartments)
	{
		float leftCompartment = c->_rect.getGlobalBounds().left;
		float rightCompartment = c->_rect.getGlobalBounds().width + leftCompartment;
		float topCompartment = c->_rect.getGlobalBounds().top;
		float bottomCompartment = topCompartment + c->_rect.getGlobalBounds().height;
		if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
		{
			std::cout << "On est dans un compartiment" << std::endl;
			action._compartment = c;
			action._screen = INVENTORY;
			return action;
		}
	}
	return action;
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
	clickInWindow();
	AWindow::checkClose();
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
		std::cout << "pos : " << posRelatX << std::endl;
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

void InventaryWindow::draw()
{
	AWindow::draw();
	for (Onglet *o : this->_onglets)
	{
		o->draw();
	}	
}

InventaryWindow::~InventaryWindow(void)
{
}
