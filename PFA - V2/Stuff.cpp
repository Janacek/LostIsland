#include "Stuff.h"


Stuff::Stuff(std::string const &title) : AWindow(title, 
							 Singleton::getInstance()._window->getSize().x * 40 / 100, 
							 Singleton::getInstance()._window->getSize().y * 35 / 100, 
							 Singleton::getInstance()._window->getSize().x * 55 / 100, 
							 Singleton::getInstance()._window->getSize().y * 55 / 100)
{
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 42 / 100, this->_window.getPosition().y + this->_window.getSize().y * 10 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 14 / 100, this->_window.getPosition().y + this->_window.getSize().y * 60 / 100));
	this->_compartments.push_back(new Compartment(this->_window.getSize(), this->_window.getPosition().x + this->_window.getSize().x * 70 / 100, this->_window.getPosition().y + this->_window.getSize().y * 60 / 100));

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
	AWindow::checkClose();
	AWindow::clickInWindow();
}

Stuff::~Stuff(void)
{
}