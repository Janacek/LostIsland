#include "Chunk.h"
#include "Player.h"
#include "Water.h"
#include "Wood.h"
#include "Singleton.h"
#include <iostream>
#include <math.h>  
#include "Map.h"

Player::Player(sf::Vector2f &pos, Camera *cam) : _pos(pos), _camera(cam)
{
	this->_name = "Player";
	this->_sizeInventory = 0;
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Red);
	this->addEntityInInventory(new Water);
	this->addEntityInInventory(new Water);
	this->addEntityInInventory(new Wood);
	_isMoving = false;
	_hasAPath = false;
	_isPathFound = false;
	/*
	** Gestion de la vie / soif / etc...
	*/
	_speed = 7;
	_pathToGo = 0.f;
	_damages = 10;
	_life = 100;
	_water = 100;
	_food = 100;
	_isSick = false;
	_hungerClock = 0;
	_thirstClock = 0;
	_lifeClock = 0;
	_isSelected = false;
	_path.clear();
	_cursorTime = 0;
}

Compartment	*Player::getCompartment(int index)
{
	if (static_cast<unsigned int>(index) >= this->_inventoryPlayer.size())
		return NULL;
	return this->_inventoryPlayer[index];
}

sfg::Box::Ptr Player::getBox()
{
	return this->_inventory;
}

//ON NE S'EN sert pas pour le moment
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

int		Player::posInventory(IEntity *entity)
{
	int a = 0;
	for (Compartment *u : this->_inventoryPlayer)
	{
		if (u->getType() == entity->getType())
			return a;
		++a;
	}
	return a;
}

void Player::drink(Water *water)
{
	//Ici, nous buvons.
}

bool Player::addEntityInInventory(IEntity *entity)
{
	std::cout << "je passe dans inventaire" << std::endl;
	for (Compartment *u : this->_inventoryPlayer)
	{
		//on a déja un element de ce type
		if (u == entity->getType())
		{
			u->addElement(entity);
			return true;
		}
	}
	std::cout << "ajout d'un element " << std::endl;
	//nouveau Type d'element
	this->_inventoryPlayer.push_back(new Compartment(entity));
	return true;
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

float Player::getPathToGo() const
{
	return _pathToGo;
}

void Player::setPathToGo(float f)
{
	_pathToGo = f;
}

void Player::addToPathToGo(float f)
{
	_pathToGo += f;
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
void Player::changeAnimation(sf::Vector2f&pos, std::pair<float, float>front)
{
	if (front.first > floor(pos.x))
	{
		_anim->setAnimation(1);
	}
	if (front.first < floor(pos.x))
	{
		_anim->setAnimation(3);
	}
	if (front.second < floor(pos.y))
	{
		_anim->setAnimation(2);
	}
	if (front.second > floor(pos.y))
	{
		_anim->setAnimation(0);
	}
}

void Player::moveToNextWP()
{
	double dt = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;

	_oldDtMvt = static_cast<float>(time);
	
	if (!_path.empty())
	{
		_anim->play();
		_isMoving = true;
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;
		//std::cout << "COIN HAUT GAUCHE : x " << floor(_pos.x) << " y " << floor(_pos.y) <<" pos reel droite  x " << floor(tmp.x) << " y "<< floor(tmp.y)  << std::endl;

		if (_path.front().first == floor(_pos.x) && _path.front().second == floor(_pos.y) &&
			_path.front().first == floor(tmp.x) && _path.front().second == floor(tmp.y)) // && que chaque coté est dans la case

		{
			_path.pop_front();
			changeAnimation(_pos, _path.front());
			return;
		}

		if (_pos.x > _path.front().first)
			_pos.x -= static_cast<float>(dt * _speed);
		if (_pos.x < _path.front().first)
			_pos.x += static_cast<float>(dt * _speed);
		if (_pos.y > _path.front().second)
			_pos.y -= static_cast<float>(dt *_speed);
		if (_pos.y < _path.front().second)
			_pos.y += static_cast<float>(dt * _speed);

	}
	else {
		_anim->pause();
		_isMoving = false;
		_hasAPath = false;
	}
}

void Player::setSelected(bool const s)
{
	_isSelected = s;
}

bool Player::getIsMoving() const
{
	return _isMoving;
}

bool const Player::getSelected() const
{
	return _isSelected;
}

void Player::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Player::draw(sf::RenderTexture *)
{

	_posDisp.x = ((_pos.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_pos.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);
	
	sf::Vector2f v(0, -10);
	this->_anim->show(_posDisp + v);

	sf::Text name;
	name.setFont(*FontManager::getInstance().getFont(SANSATION));
	name.setString(_name);
	name.setCharacterSize(12);
	name.setColor(sf::Color::Black);
	name.setPosition(_posDisp.x - (name.getGlobalBounds().width / 8), _posDisp.y - 24);
	Singleton::getInstance()._window->draw(name);

	if (_isSelected)
	{
		sf::Vector2f posIcon = _posDisp;
		sf::RectangleShape icon(sf::Vector2f(32, 32)); 
		icon.setTexture(ImageSingleton::getInstance().get(SELECTED_ICON));
		posIcon.y -= 52;
		icon.setPosition(posIcon);

		Singleton::getInstance()._selectedShader.setParameter("texture", sf::Shader::CurrentTexture);
		Singleton::getInstance()._selectedShader.setParameter("wave_phase", _cursorTime);
		Singleton::getInstance()._selectedShader.setParameter("wave_amplitude", 2, 2);
		_cursorTime += 0.05f;
		Singleton::getInstance()._window->draw(icon, &Singleton::getInstance()._selectedShader);
	}
}

void Player::changeMapEntity(Map & map)
{
	if (!_path.empty() && _hasAPath == false)
	{
		_hasAPath = true;
		//if (map.getEntitiesMap()[static_cast<int>(floor(_path.back().second))][static_cast<int>(floor(_path.back().first))]._component &&
		//map.getEntitiesMap()[static_cast<int>(floor(_path.back().second))][static_cast<int>(floor(_path.back().first))]._component->getType() == PLAYER)
		{
			map.setEntityMap(NULL, static_cast<int>(floor(_pos.y)), static_cast<int>(floor(_pos.x)));
		}

		if (map.getEntitiesMap()[static_cast<int>(floor(_path.back().second))][static_cast<int>(floor(_path.back().first))]._component == NULL)
		{
			map.setEntityMap(this, static_cast<int>(floor(_path.back().second)), static_cast<int>(floor(_path.back().first)));
		}
		
	}
}

void Player::update(Map & map)
{
	double dt = 0;
	double time;

	time = _referenceClock.getElapsedTime().asSeconds();
	dt = time - _oldDt;

	_oldDt = time;

	/*
	Si on est en mvt on delete la case ou on était a la base, on set la case d'arrivée

	*/
	/*if (_isMoving == false && map.getEntitiesMap()[static_cast<int>(floor(_pos.x))][static_cast<int>(floor(_pos.y))]._component == NULL)
	{
		std::cout << "Point add : x " << static_cast<int>(floor(_pos.x)) << " y " << static_cast<int>(floor(_pos.y)) << std::endl;
		map.setEntityMap(this, static_cast<int>(floor(_pos.x)), static_cast<int>(floor(_pos.y)));
	}*/
	
	changeMapEntity(map);
	
	_hungerClock += dt;
	_thirstClock += dt;
	if (_hungerClock > 6)
	{
		_hungerClock = 0.f;
		_food -= 1;
	}
	if (_thirstClock > 3)
	{
		_thirstClock = 0.f;
		_water -= 1;
	}
	if (_water <= 0)
		_water = 0;
	if (_food <= 0)
		_food = 0;

	if (_water <= 0 || _food <= 0)
		_lifeClock += dt;
	if (_lifeClock > 5)
	{
		_lifeClock = 0;
		_life -= 1;
	}
	if (_life <= 0)
	{
		// You're supposedly dead here.
	}
	moveToNextWP();

}

void Player::loadAnimation(std::string const & string_anim, float speed)
{
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