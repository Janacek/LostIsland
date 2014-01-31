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
	this->_img.loadFromFile("carre.png");
	createBox();
}

sfg::Box::Ptr Player::getBox()
{
	return this->_inventory;
}

void Player::createBox()
{
	//on crée la structure
	this->_book = sfg::Notebook::Create();
	this->_inventory = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	auto table = sfg::Table::Create();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto  tmp = sfg::Image::Create();
			tmp->SetImage(this->_img);
			table->Attach(tmp, sf::Rect<sf::Uint32>(i, j, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
		}
	}
	this->_inventory->Pack(table, false);
	this->_book->AppendPage(this->_inventory, sfg::Label::Create(this->_name));
}

void Player::setCamPos(sf::Vector2f &pos)
{

	//std::cout << "x " << _cam.x << " y " << _cam.y << std::endl;
	
}

void Player::drink(Water *water)
{
	//Ici, nous buvons.
}

bool Player::addEntityInInventory(IEntity *entity)
{
	for (Compartment *u : this->_inventoryPlayer)
	{
		//on a déja un element de ce type
		if (u == entity->getType())
		{
			u->addElement(entity);
			return true;
		}
	}
	//nouveau Type d'element
	this->_inventoryPlayer.push_back(new Compartment(entity));
}

//peut peut etre servir
bool Player::delEntityInInventory(Type type)
{
	for (Compartment *u : this->_inventoryPlayer)
	{
		if (u == type)
		{
			return u->delElement();
		}
	}
	return false;
}

bool Player::delEntityInInventory(IEntity *entity)
{
	for (Compartment *u : this->_inventoryPlayer)
	{
		if (u == entity->getType())
		{
			return u->delElement(entity);
		}
	}
	return false;
}

void Player::moveToNextWP()
{
	if (!_path.empty())
	{
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;
		//std::cout << "COIN HAUT GAUCHE : x " << floor(_pos.x) << " y " << floor(_pos.y) <<" pos reel droite  x " << floor(tmp.x) << " y "<< floor(tmp.y)  << std::endl;

		if (_path.front().first == floor(_pos.x)  && _path.front().second == floor(_pos.y) &&
			_path.front().first == floor(tmp.x)  && _path.front().second == floor(tmp.y)) // && que chaque coté est dans la case
		
		{
			_path.pop_front();
			return;
		}

		if (_pos.x > _path.front().first)
			_pos.x -= 0.1f;
		if (_pos.x < _path.front().first)
			_pos.x += 0.1f;
		if (_pos.y > _path.front().second)
			_pos.y -= 0.1f;
		if (_pos.y < _path.front().second)
			_pos.y += 0.1f;
		
	}
}

void Player::draw()
{

	moveToNextWP();
	_posDisp.x = ((_pos.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_pos.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);
	
	sf::Vector2f v(0, -10);
	_rect.setPosition(_posDisp );
	//Singleton::getInstance()._window->draw(_rect);
	this->_anim->show(_posDisp + v);
}

void Player::update()
{
	

}

void Player::loadAnimation(std::string const & string_anim, float speed)
{
	std::cout << "SHO" << std::endl;
	sf::Texture *imgAnim = new sf::Texture;
	sf::Color color(255, 0, 255);
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	img_tmp.createMaskFromColor(color);
	imgAnim->loadFromImage(img_tmp);
	this->_anim = new Animation(imgAnim, 7, 3,speed);
	this->_anim->setAnimation(0);
}

void Player::move(sf::Vector2f &pos)
{
	_pos.x += pos.x;
	_pos.y += pos.y;

}

void Player::doAction(IEntity* other)
{
	other->getAction(this);
}

void Player::getAction(IEntity* other)
{
	this->_damages -= other->getDamage();
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