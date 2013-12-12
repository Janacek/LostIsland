#include "InventaryWindow.h"


/// <summary>
/// Initializes a new instance of the <see cref="InventaryWindow"/> class. Set the position and Color of the sf::RectangleShape
/// </summary>
InventaryWindow::InventaryWindow(void)
{
	float sizeX = Singleton::getInstance()._window->getSize().x / 2;
	float sizeY = Singleton::getInstance()._window->getSize().y / 2;
	this->_inventaryWindow = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
	this->_inventaryWindow.setPosition(Singleton::getInstance()._window->getSize().x / 4, Singleton::getInstance()._window->getSize().y / 4);
	this->_inventaryWindow.setFillColor(sf::Color::Blue);
}

void InventaryWindow::update()
{

}

void InventaryWindow::addCompartment()
{

}

void InventaryWindow::draw()
{
	Singleton::getInstance()._window->draw(this->_inventaryWindow);
}

InventaryWindow::~InventaryWindow(void)
{
}
