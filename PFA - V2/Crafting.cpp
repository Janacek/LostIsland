#include "Crafting.h"


Crafting::Crafting(std::string const &title) : AWindow(title, 
								   Singleton::getInstance()._window->getSize().x * 40 / 100, 
								   Singleton::getInstance()._window->getSize().y * 35 / 100, 
								   Singleton::getInstance()._window->getSize().x * 55 / 100, 
								   Singleton::getInstance()._window->getSize().y / 10)
{
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 20 / 100, this->_window.getPosition().y + this->_window.getSize().y * 10 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 60 / 100, this->_window.getPosition().y + this->_window.getSize().y * 10 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 20 / 100, this->_window.getPosition().y + this->_window.getSize().y * 50 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 60 / 100, this->_window.getPosition().y + this->_window.getSize().y * 50 / 100));
}

 s_action Crafting::clickInCompartment(sf::Vector2i &coordClick)
{
	s_action action(true);
	sf::Vector2i posLeftClickPressed = coordClick;
	for (Compartment *c : this->_compartments)
	{
		float leftCompartment = c->_rect.getGlobalBounds().left;
		float rightCompartment = c->_rect.getGlobalBounds().width + leftCompartment;
		float topCompartment = c->_rect.getGlobalBounds().top;
		float bottomCompartment = topCompartment + c->_rect.getGlobalBounds().height;
		if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
		{
			//std::cout << "On est dans un compartiment" << std::endl;
			action._compartment = c;
			//Singleton::getInstance().posLeftClickPressed.x = -1;
			action._screen = CRAFTING;
			return action;
		}
	}
	return action;
}


 void Crafting::swapCompartment(s_action &, s_action &)
 {

 }
 void Crafting::addCompartment(s_action &, s_action &)
 {

 }

bool Crafting::close()
{
	if (this->_close == true)
	{
		this->_close = false;
		return true;
	}
	return this->_close;
}

void Crafting::update()
{
	AWindow::checkClose();
}

Crafting::~Crafting(void)
{
}

