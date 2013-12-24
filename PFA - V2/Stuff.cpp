#include "Stuff.h"
#include "Water.h"


Stuff::Stuff(std::string const &title) : AWindow(title, 
							 Singleton::getInstance()._window->getSize().x * 40 / 100, 
							 Singleton::getInstance()._window->getSize().y * 35 / 100, 
							 Singleton::getInstance()._window->getSize().x * 55 / 100, 
							 Singleton::getInstance()._window->getSize().y * 55 / 100)
{
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 42 / 100, this->_window.getPosition().y + this->_window.getSize().y * 10 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 14 / 100, this->_window.getPosition().y + this->_window.getSize().y * 60 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 70 / 100, this->_window.getPosition().y + this->_window.getSize().y * 60 / 100));
	this->_compartments[0]->_elements.push_back(new Water);
}

s_action Stuff::clickInCompartment(sf::Vector2i &coordClick)
{
	 s_action action;
	sf::Vector2i posLeftClickPressed = coordClick;
	for (Compartment *c : this->_compartments)
	{
		float leftCompartment = c->_rect.getGlobalBounds().left;
		float rightCompartment = c->_rect.getGlobalBounds().width + leftCompartment;
		float topCompartment = c->_rect.getGlobalBounds().top;
		float bottomCompartment = topCompartment + c->_rect.getGlobalBounds().height;
		if (leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
		{
			std::cout << "On est dans un compartiment" << std::endl;
			action._compartment = c;
			action._screen = STUFF;
			return action;
		}
	}
	return action;
}


void Stuff::swapCompartment(s_action &, s_action &)
{

}
void Stuff::addCompartment(s_action &, s_action &)
{

}

bool Stuff::close()
{
	if (this->_close == true)
	{
		this->_close = false;
		return true;
	}
	return this->_close;
}

void Stuff::update()
{
	/*AWindow::checkClose();
	AWindow::clickInWindow();*/
}

Stuff::~Stuff(void)
{
}