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
	AWindow::clickInWindow();
}

Crafting::~Crafting(void)
{
}

