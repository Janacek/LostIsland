#include "Chunk.h"
#include "Player.h"
#include "Water.h"
#include "Singleton.h"
#include <iostream>
#include <math.h>  

Player::Player(sf::Vector2f &pos, Camera *cam) : _pos(pos), _camera(cam)
{
	this->_name = "Georgette";
	this->_sizeInventory = 0;
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Red);
}

void Player::setCamPos(sf::Vector2f &pos)
{

	//std::cout << "x " << _cam.x << " y " << _cam.y << std::endl;
	
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

void Player::moveToNextWP()
{
	if (!_path.empty())
	{
		
		if (_path.front().first == floor(_pos.x) && _path.front().second == floor(_pos.y))
		{
			std::cout << "coucou" << std::endl;
			_path.pop_front();
		}

		if (_pos.x > _path.front().first)
			_pos.x -= 0.1;
		if (_pos.x < _path.front().first)
			_pos.x += 0.1;
		if (_pos.y > _path.front().second)
			_pos.y -= 0.1;
		if (_pos.y < _path.front().second)
			_pos.y += 0.1;
		
		
	}
}

void Player::draw()
{
	moveToNextWP();
	_posDisp.x = (_pos.x - _camera->_position.x) * Chunk::SIZE_OF_CELL;
	_posDisp.y = (_pos.y - _camera->_position.y) * Chunk::SIZE_OF_CELL;
	
	_rect.setPosition(_posDisp);
	Singleton::getInstance()._window->draw(_rect);
}

void Player::move(sf::Vector2f &pos)
{
	_pos.x += pos.x;
	_pos.y += pos.y;

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

void Player::setPath(std::list<std::pair<float, float> > &path)
{
	_path = path;
}

void Player::setPosition(sf::Vector2f &pos)
{
	_pos.x = (pos.x - _camera->_position.x) * Chunk::SIZE_OF_CELL;
	_pos.y = (pos.y - _camera->_position.y) * Chunk::SIZE_OF_CELL;
	_rect.setPosition(_pos);
}

sf::Vector2f  Player::getPosition() const
{
	return _pos;
}


/*sf::Rect & Player::getCollisionBox(void)
{
}
*/