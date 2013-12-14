#include "Onglet.h"

Onglet::Onglet(Player *player, std::string const &title, float sizeX, float sizeY, float posX, float posY)
{
	//Onglet
	this->setSize(sf::Vector2f(sizeX, sizeY));
	this->setPosition(posX, posY);
	this->setFillColor(sf::Color(0, 0, 255, 100));
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color::Yellow);

	//Texte
	this->_font = new sf::Font;
	this->_font->loadFromFile("./Media/Sansation.ttf");
	this->_name.setFont(*this->_font);
	this->_name.setPosition(this->getPosition().x, this->getPosition().y);
	this->_name.setCharacterSize(15);
	this->_name.setColor(sf::Color::Black);
	std::cout << "NAME : " << title << std::endl;
	this->_name.setString(title);
	
	//Other
	this->_isSelected = false;
	this->_player = player;
}

std::string Onglet::getName() const
{
	return this->_name.getString();
}

bool Onglet::isSelected() const
{
	return this->_isSelected;
}

void Onglet::setisSelected(bool b)
{
	this->_isSelected = b;
	if (!b)
		this->setFillColor(sf::Color(0, 0, 255, 100));
	else
	{
		this->setFillColor(sf::Color(0, 0, 255, 255));
	}
}

void Onglet::draw()
{
	Singleton::getInstance()._window->draw(*this);
	Singleton::getInstance()._window->draw(this->_name);
}

void Onglet::update()
{

}

Onglet::~Onglet(void)
{
}
