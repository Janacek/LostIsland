#include "Chunk.h"
#include "Player.h"
#include "Water.h"
#include "Wood.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include <iostream>
#include <math.h>  
#include "Map.h"
#include "FontManager.h"
#include "ShadersManager.h"
#include "MapEnvironment.h"

Player::Player(sf::Vector2f &pos, Camera *cam) : _pos(pos), _camera(cam)
{
	_target = BADTYPE;
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
	_objective = NULL;
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
	this->_water + 20 > 100 ? this->_water = 100 : this->_water += 20;
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

void Player::setTarget(Type t)
{
	_target = t;
}

void Player::changeAnimation(sf::Vector2f&pos, std::pair<float, float>front)
{
	if (front.first > floor(pos.x))
	{
		_curAnim = _walkRightAnim;
	}
	if (front.first < floor(pos.x))
	{
		_curAnim = _walkLeftAnim;
	}
	if (front.second < floor(pos.y))
	{
		_curAnim = _walkUpAnim;
	}
	if (front.second > floor(pos.y))
	{
		_curAnim = _walkDownAnim;
	}
}

void Player::doActionOnEntity()
{
	if (_objective && _objective->getType() != PLAYER)
	{
		if (_objective->getIsAMovingEntity())
		{
			_path = _objective->getPath();
		}
		else
		{

			if (_actionClock >= 0.5)
			{
				doAction(_objective);
				_actionClock = 0;
			}
		}
	}
}

void Player::changeToIdleAnim()
{
	if (_curAnim == _walkRightAnim)
		_curAnim = _idleRightAnim;
	if (_curAnim == _walkLeftAnim)
		_curAnim = _idleLeftAnim;
	if (_curAnim == _walkUpAnim)
		_curAnim = _idleUpAnim;
	if (_curAnim == _walkDownAnim)
		_curAnim = _idleDownAnim;
}

void Player::moveToNextWP()
{
	double dt = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;

	_oldDtMvt = static_cast<float>(time);
	_animatedSprite->play(*_curAnim);

	if (!_path.empty())
	{
		
		_animatedSprite->play(*_curAnim);
		_isMoving = true;
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;

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
		doActionOnEntity();
		changeToIdleAnim();
		//_animatedSprite->stop();
		_isMoving = false;
		_hasAPath = false;
	}
	sf::Time t = sf::seconds(dt);;
	_animatedSprite->update(t);
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
	//this->_anim->show(_posDisp + v);
	_animatedSprite->setPosition(_posDisp + v);
	Singleton::getInstance()._window->draw(*_animatedSprite);

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

		ShadersManager::getInstance().get(FLAG)->setParameter("texture", sf::Shader::CurrentTexture);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_phase", _cursorTime);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_amplitude", 2, 2);

		_cursorTime += 0.025f;
		Singleton::getInstance()._window->draw(icon, ShadersManager::getInstance().get(FLAG));
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
	_actionClock += dt;
	if (_hungerClock > HUNGER_CLOCK)
	{
		_hungerClock = 0.f;
		_food -= 1;
	}
	if (_thirstClock > THIRST_CLOCK)
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
	if (_lifeClock > HEALTH_CLOCK)
	{
		_lifeClock = 0;
		_life -= 1;
	}
	if (_life <= 0)
	{
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
	//std::cout << string_anim << std::endl;
	_idleUpAnim = new Animation();
	_idleUpAnim->setSpriteSheet(*imgAnim);
	_idleUpAnim->addFrame(sf::IntRect(0, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(62, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(127, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(195, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(265, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(333, 0, 60, 84));
	_idleUpAnim->addFrame(sf::IntRect(396, 0, 60, 84));
	_idleDownAnim = new Animation();
	_idleDownAnim->setSpriteSheet(*imgAnim);
	_idleDownAnim->addFrame(sf::IntRect(0, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(62, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(127, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(195, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(265, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(333, 84, 60, 84));
	_idleDownAnim->addFrame(sf::IntRect(396, 84, 60, 84));

	_idleRightAnim = new Animation();
	_idleRightAnim->setSpriteSheet(*imgAnim);
	_idleRightAnim->addFrame(sf::IntRect(0, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(50, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(100, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(150, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(200, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(250, 170, 48, 88));
	_idleRightAnim->addFrame(sf::IntRect(300, 170, 48, 88));


	_idleLeftAnim = new Animation();
	_idleLeftAnim->setSpriteSheet(*imgAnim);
	_idleLeftAnim->addFrame(sf::IntRect(657, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(607, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(557, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(507, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(457, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(407, 170, 48, 88));
	_idleLeftAnim->addFrame(sf::IntRect(357, 170, 48, 88));
	
	_walkUpAnim = new Animation();
	_walkUpAnim->setSpriteSheet(*imgAnim);
	_walkUpAnim->addFrame(sf::IntRect(0, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(77, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(146, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(216, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(300, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(386, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(463, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(533, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(604, 260, 80, 84));
	_walkUpAnim->addFrame(sf::IntRect(688, 260, 80, 84));

	_walkDownAnim = new Animation();
	_walkDownAnim->setSpriteSheet(*imgAnim);
	_walkDownAnim->addFrame(sf::IntRect(1, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(78, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(148, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(222, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(299, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(387, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(464, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(534, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(609, 346, 78, 80));
	_walkDownAnim->addFrame(sf::IntRect(688, 346, 78, 80));
	/*_walkDownAnim->addFrame(sf::IntRect(7, 245, 18, 29));
	_walkDownAnim->addFrame(sf::IntRect(38, 243, 18, 28));
	_walkDownAnim->addFrame(sf::IntRect(68, 246, 18, 25));
	_walkDownAnim->addFrame(sf::IntRect(102, 246, 18, 29));
	_walkDownAnim->addFrame(sf::IntRect(134, 245, 18, 28));
	_walkDownAnim->addFrame(sf::IntRect(171, 248, 18, 25));
	*/
	_curAnim = _idleDownAnim;
	
	_walkLeftAnim = new Animation();
	_walkLeftAnim->setSpriteSheet(*imgAnim);
	/*A ENLEVER !!*/
	_walkLeftAnim->addFrame(sf::IntRect(464, 346, 78, 80));
	/*A ENLEVER !!*/
	_walkRightAnim = new Animation();
	_walkRightAnim->setSpriteSheet(*imgAnim);
	/*A ENLEVER !!*/
	_walkRightAnim->addFrame(sf::IntRect(464, 346, 78, 80));
	/*A ENLEVER !!*/

	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_animatedSprite->setScale(0.5, 0.5);
	//
	_animatedSprite->play(*_curAnim);
	
	

	

}

void Player::move(sf::Vector2f &pos)
{
	_pos.x += pos.x;
	_pos.y += pos.y;

}

void Player::doAction(IEntity* other)
{
	if (other->getType() != PLAYER)
		other->getAction(this);
}

void Player::getAction(IEntity* other)
{
	this->_life -= other->getDamage();
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
	_isMoving = false;
	_hasAPath = false;
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


sf::IntRect & Player::getCollisionBox(void)
{
	return _boxCollider;
}
