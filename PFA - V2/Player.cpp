#include "Player.h"
#include "Water.h"
#include <iostream>

Player::Player()
{
	this->_name = "Georgette";
	this->_sizeInventory = 0;
}

void Player::drink(Water *water)
{
	//Ici, nous buvons.
}

void Player::addEntityInInventory(IEntity *entity)
{
	int i = 0;

	Type tmpType = entity->getType();
	//std::cout << "SIZE : " << this->_mainInventory._compartments.size() << std::endl;
	for (Compartment *u : this->_compartments)
	{
		if (u->_elements.size() != 0 && u->_elements.front()->getType() == tmpType)
		{
			u->addElement(entity);
			return ;
		}
	}
	if (this->_sizeInventory < 6)
	{
		this->_compartments[this->_sizeInventory]->addElement(entity);
		++this->_sizeInventory;
	}
	else
	{
		std::cout << "Inventaire plein !!!" << std::endl;
	}
}

void Player::addCompartment(sf::RectangleShape &window)
{
	float posIniX = window.getPosition().x + window.getSize().x / 10; //10% de marge
	if (this->_compartments.size() < 3)
	{
		float posRelatX = this->_compartments.size() * (window.getSize().x * 5 / 100) + this->_compartments.size() * (window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		//std::cout << "pos : " << posRelatX << std::endl;
		this->_compartments.push_back(new Compartment(window.getSize(), posIniX + posRelatX, window.getPosition().y + window.getSize().y / 10)); //10% de marge);
	}
	else if (this->_compartments.size() < 6)
	{
		float posRelatX = (this->_compartments.size() - 3) * (window.getSize().x * 5 / 100) + (this->_compartments.size() - 3) * (window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		this->_compartments.push_back(new Compartment(window.getSize(), posIniX + posRelatX, window.getPosition().y + window.getSize().y * 2 / 10 + window.getSize().x * 23 / 100)); //10% de marge);
	}
	else
	{
		float posRelatX = (this->_compartments.size() - 6) * (window.getSize().x * 5 / 100) + (this->_compartments.size() - 6) * (window.getSize().x * 23 / 100); //Calcul savant pour avoir des cases au bon endroit
		this->_compartments.push_back(new Compartment(window.getSize(), posIniX + posRelatX, window.getPosition().y + window.getSize().y * 3 / 10 + window.getSize().x * 23 / 100 * 2)); //10% de marge);
	}
}

void Player::doAction(IEntity* other)
{
	other->getAction(this);
}

void Player::getAction(IEntity* other)
{
	this->_damages -= other->getDamage();
}

void Player::Animate(std::string const & string_anim)
{
}

void Player::setName(std::string const &name)
{
	this->_name = name;
}

std::string const &Player::getName() const
{
	return this->_name;
}

int Player::getDamage(void) const
{
	return this->_damages;
}

Type Player::getType() const
{
	return PLAYER;
}

/*sf::Rect & Player::getCollisionBox(void)
{
}
*/