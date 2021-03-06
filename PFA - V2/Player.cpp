#include "Chunk.h"
#include "Player.h"
#include "Water.h"
#include "Wood.h"
#include "Singleton.h"
#include "ImageManager.h"
#include <iostream>
#include <math.h>  
#include "Map.h"
#include "FontManager.h"
#include "ShadersManager.h"
#include "MapEnvironment.h"
#include "Meat.h"
#include "Bush.h"
#include "InventoryWindow.h"
#include "SoundManager.h"

std::string &Player::serialize() const
{
	std::string toto;
	return (toto);
}

void Player::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Player::Player(sf::Vector2f &pos, Camera *cam) 
: _camera(cam), AEntity(0.f, true, sf::Vector2f(pos), 10, sf::FloatRect(0, 0, 0, 0), 100)
{
	_isActionning = false;
	_isAttacking = false;
	this->_isHittingRock = true;
	this->_isWalking = false;
	this->_stepsBuffer.loadFromFile("./Media/sounds/sfx/steps.ogg");
	this->_stepts.setBuffer(this->_stepsBuffer);
	this->_eatBuffer.loadFromFile("./Media/sounds/sfx/manger.ogg");
	this->_eat.setBuffer(this->_eatBuffer);
	this->_drinkBuffer.loadFromFile("./Media/sounds/sfx/boire.ogg");
	this->_drink.setBuffer(this->_drinkBuffer);
	this->_swordBuffer.loadFromFile("./Media/sounds/sfx/sword2.ogg");
	this->_sword.setBuffer(this->_swordBuffer);
	this->_dieBuffer.loadFromFile("./Media/sounds/sfx/mort.ogg");
	this->_die.setBuffer(this->_dieBuffer);
	this->_cutThreeBuffer.loadFromFile("./Media/sounds/sfx/bois.ogg");
	this->_cutThree.setBuffer(this->_cutThreeBuffer);
	this->_hitRockBuffer.loadFromFile("./Media/sounds/sfx/pierre.ogg");
	this->_hitRock.setBuffer(this->_hitRockBuffer);
	_target = BADTYPE;
	this->_name = "Player";
	this->_inventoryWindow = NULL;
	this->_sizeInventory = 0;
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Red);
	_hasAPath = false;
	/*
	** Gestion de la vie / soif / etc...
	*/
	_speed = 5;
	_life = 100;
	_water = 100;
	_food = 100;
	_isSick = false;
	_hungerClock = 0;
	_thirstClock = 0;
	_lifeClock = 0;
	_path.clear();
	_cursorTime = 0;
	_objective = NULL;
	_timeAttack = 0;

}

sf::FloatRect Player::getBoxCollider() const
{
	return _animatedSprite->getGlobalBounds();
}

sf::Sound		Player::getDie() const
{
	return (this->_die);
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

void Player::setCamPos(sf::Vector2f &pos)
{

	//std::cout << "x " << _cam.x << " y " << _cam.y << std::endl;

}

void Player::drink(int amount)
{
	this->_water + amount > 100 ? this->_water = 100 : this->_water += amount;
}

int		Player::posInventory(AEntity *entity)
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

void Player::eat(int amount)
{
	this->_eat.play();
	this->_food + amount > 100 ? this->_food = 100 : this->_food += amount;
}

void Player::drink(Water *water)
{
	this->_drink.play();
	this->_water + 20 > 100 ? this->_water = 100 : this->_water += 20;
}

bool Player::addEntityInInventory(AEntity *entity)
{
	int compt = 0;
	for (Compartment *u : this->_inventoryPlayer)
	{
		//on a d�ja un element de ce type
		if (u == entity->getType())
		{
			u->addElement(entity);
			this->_inventoryWindow->updateLabel(this, compt);
			return true;
		}
		++compt;
	}
	compt = 0;
	for (Compartment *u : this->_inventoryPlayer)
	{
		if (u->getSize() == 0)
		{
			u->addElement(entity);
			this->_inventoryWindow->addToInventory(this, u, compt);
			return true;
		}
		++compt;
	}
	Compartment *u = new Compartment(entity);
	this->_inventoryPlayer.push_back(u);
	this->_inventoryWindow->close();
	if (this->_inventoryWindow != NULL)
	{
		this->_inventoryWindow->addToInventory(this, u, compt);
	}
	else
		std::cout << "Inventaire dans le joueur NULL" << std::endl;
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

bool Player::delEntityInInventory(AEntity *entity)
{
	for (Compartment *u : this->_inventoryPlayer)
	{
		if (u->delElement(entity) == true) //la ressource est dans le player et dans ce compartiement
		{
			return true;
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
	else if (front.first < floor(pos.x))
	{
		_curAnim = _walkLeftAnim;
	}
	else if (front.second < floor(pos.y))
	{
		_curAnim = _walkUpAnim;
	}
	else
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
			

			_isActionning = true;
			if (_actionClock >= 0.5)
			{
				_isActionning = false;
				
				doAction(_objective);
				_actionClock = 0;
			}
			if (_objective->getIsActionOver() == true)
			{
				changeToIdleAnim();
			}
			else
			{
				if (this->_objective->getType() == ROCK && this->_rockClock.getElapsedTime().asSeconds() > 0.5f)
				{
						this->_hitRock.play();
						this->_rockClock.restart();
				}

				if ((this->_objective->getType() == TREE || this->_objective->getType() == PALMTREE) && this->_rockClock.getElapsedTime().asSeconds() > 0.5f)
				{
					this->_cutThree.play();
					this->_rockClock.restart();
				}
				changeToActionAnim();
			}
		}
	}
}

void Player::changeToActionAnim()
{
	sf::Vector2f objPos2;
	objPos2.x = _objective->getPosition().y;
	objPos2.y = _objective->getPosition().x;

	sf::Vector2i tmp = diffDist(objPos2, _position);
	if (tmp.x >= 0 && tmp.y == -1) // moi non plus je comprend pas mais une phase de test � arbres binaire compos� de baies m'a dit que c'�tait la bonne solution
		_curAnim = _hitRightAnim;
	else if (tmp.x <= -1 && tmp.y == -1)
		_curAnim = _hitLeftAnim;
	else if (tmp.x <= 0 && tmp.y == 0)
		_curAnim = _hitDownAnim;
	else
		_curAnim = _hitUpAnim;
}

void Player::changeToIdleAnim()
{
	/*if (_curAnim == _walkRightAnim)
		_curAnim = _idleRightAnim;
	if (_curAnim == _walkLeftAnim)
		_curAnim = _idleLeftAnim;
	if (_curAnim == _walkUpAnim)
		_curAnim = _idleUpAnim;
	if (_curAnim == _walkDownAnim)*/
		_curAnim = _idleDownAnim;
}

void Player::moveToNextWP()
{
	double dt = 0;
	double time;
	_isActionning = false;
	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;

	_oldDtMvt = static_cast<float>(time);
	_animatedSprite->play(*_curAnim);
	if (_isAttacking == true)
	{
		if (_objective &&  !_objective->getPath().empty() && _path.back() != _objective->getPath().front())
		{

			_path.push_back(_objective->getPath().front());
			}
		_timeAttack += dt;

		
	}
	if (_timeAttack > 0.7 && _isAttacking == true)
	{
			this->_sword.play();
		_isAttacking = false;
		_timeAttack = 0;
		
	}
	if (_isAttacking == false)
	{
		
		if (!_path.empty())
		{
			_animatedSprite->setLooped(true);

			//_animatedSprite->play(*_curAnim);
			_isMoving = true;
			sf::Vector2f tmp(0, 0);
			tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
			tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;

			if (_position.x > _path.front().first)
				_position.x -= static_cast<float>(dt * _speed);
			if (_position.x < _path.front().first)
				_position.x += static_cast<float>(dt * _speed);
			if (_position.y > _path.front().second)
				_position.y -= static_cast<float>(dt *_speed);
			if (_position.y < _path.front().second)
				_position.y += static_cast<float>(dt * _speed);
			if (_path.front().first == floor(_position.x) && _path.front().second == floor(_position.y) &&
				_path.front().first == floor(tmp.x) && _path.front().second == floor(tmp.y)) // && que chaque cot� est dans la case

			{
				if (!_path.empty())
					_path.pop_front();
				changeAnimation(_position, _path.front());
				return;
			}
		}
		else  {
			doActionOnEntity();
 			if (_isActionning == false)
				changeToIdleAnim();
			//_animatedSprite->stop();
			_isMoving = false;
			_hasAPath = false;
		}
	}
	if (_isAttacking == false && _objective && _objective->getIsAMovingEntity() && _objective->getType() != PLAYER && _objective->getBoxCollider().intersects(_animatedSprite->getGlobalBounds()))
	{
		_isAttacking = true;
		std::cout << "A LATTAQUE  !" << std::endl;
		std::pair<float, float> save;
		save.first = _path.front().first;
		save.second = _path.front().second;

		_path.clear();
		_path.push_back(save);
		_animatedSprite->setLooped(false);
		_timeAttack += dt;
		sf::Vector2i tmp = diffDist(_objective->getPosition(), _position);
		if (tmp.x >= 0 && tmp.y == -1) // moi non plus je comprend pas mais une phase de test � arbres binaire compos� de baies m'a dit que c'�tait la bonne solution
			_curAnim = _attackRightAnim;
		else if (tmp.x <= -1 && tmp.y == -1)
			_curAnim = _attackLeftAnim;
		else if (tmp.x <= 0 && tmp.y == 0)
			_curAnim = _attackDownAnim;
		else
			_curAnim = _attackUpAnim;
		
		_objective->getAction(this);
		//On need un new chemin ici 
	}

	sf::Time t = sf::seconds(dt);;
	_animatedSprite->update(t);
}

sf::Vector2i const Player::diffDist(sf::Vector2f&first, sf::Vector2f&second)
{
	sf::Vector2i sum;
	sum.x = floor(((first.x) - (second.x)));
	sum.y = floor(((first.y) - (second.y)));
	
	return sum;
}

void Player::draw(sf::RenderTexture *tex, sf::Shader &)
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	sf::Vector2f v(0, -10);
	_animatedSprite->setPosition(_posDisp + v);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(*_animatedSprite, ShadersManager::getInstance().get(BLOOM));

	sf::Text name;
	name.setFont(*FontManager::getInstance().getFont(SANSATION));
	name.setString(_name);
	name.setCharacterSize(12);
	name.setColor(sf::Color::Black);
	name.setPosition(_posDisp.x - (name.getGlobalBounds().width / 8), _posDisp.y - 24);
	tex->draw(name);

	if (_isSelected)
	{
		sf::Vector2f posIcon = _posDisp;
		sf::RectangleShape icon(sf::Vector2f(32, 32));
		icon.setTexture(ImageManager::getInstance().get(SELECTED_ICON));
		posIcon.y -= 52;
		icon.setPosition(posIcon);

		ShadersManager::getInstance().get(FLAG)->setParameter("texture", sf::Shader::CurrentTexture);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_phase", _cursorTime);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_amplitude", 2, 2);

		_cursorTime += 0.025f;
		tex->draw(icon, ShadersManager::getInstance().get(FLAG));
	}
}

void Player::drawInfos(sf::RenderTexture *tex)
{
	sf::Text name;
	name.setFont(*FontManager::getInstance().getFont(SANSATION));
	name.setString(_name);
	name.setCharacterSize(12);
	name.setColor(sf::Color::Black);
	name.setPosition(_posDisp.x - (name.getGlobalBounds().width / 8), _posDisp.y - 24);
	tex->draw(name);

	if (_isSelected)
	{
		sf::Vector2f posIcon = _posDisp;
		sf::RectangleShape icon(sf::Vector2f(32, 32));
		icon.setTexture(ImageManager::getInstance().get(SELECTED_ICON));
		posIcon.y -= 52;
		icon.setPosition(posIcon);

		ShadersManager::getInstance().get(FLAG)->setParameter("texture", sf::Shader::CurrentTexture);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_phase", _cursorTime);
		ShadersManager::getInstance().get(FLAG)->setParameter("wave_amplitude", 2, 2);

		tex->draw(icon, ShadersManager::getInstance().get(FLAG));
	}
}

void Player::draw(sf::RenderTexture *tex)
{

	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	sf::Vector2f v(0, -10);
	//this->_anim->show(_posDisp + v);
	_animatedSprite->setPosition(_posDisp + v);
	tex->draw(*_animatedSprite);
}

void Player::stepsSound()
{
	if (!_path.empty() && this->_isWalking == false)
	{
		this->_stepts.play();
		this->_isWalking = true;
	}
	else if (_path.empty() && this->_isWalking == true)
	{
		this->_stepts.stop();
		this->_isWalking = false;
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
			map.setEntityMap(NULL, static_cast<int>(floor(_position.y)), static_cast<int>(floor(_position.x)));
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
	_cursorTime += dt;
	this->stepsSound();

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
		_water = 00;
	if (_food <= 0)
		_food = 0;

	if (_water <= 0 || _food <= 0)
		_lifeClock += dt;
	if (_lifeClock > HEALTH_CLOCK)
	{
		_lifeClock = 0;
		_life -= 100;
	}
	if (_life <= 0)
	{
	}

	moveToNextWP();
	if (_life <= 0)
	{
		if (this->_die.getStatus() != sf::Sound::Status::Playing)
			this->_die.play();
		_isDead = true;
		_isSelected = false;
	}
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

	
	_walkRightAnim = new Animation();
	_walkRightAnim->setSpriteSheet(*imgAnim);
	_walkRightAnim->addFrame(sf::IntRect(1, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(73, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(189, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(265, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(329, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(390, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(457, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(530, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(601, 428, 68, 88));
	_walkRightAnim->addFrame(sf::IntRect(664, 428, 68, 88));





	_walkLeftAnim = new Animation();
	_walkLeftAnim->setSpriteSheet(*imgAnim);
	_walkLeftAnim->addFrame(sf::IntRect(722, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(784, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(855, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(927, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(995, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(1058, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(1122, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(1196, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(1273, 428, 68, 88));
	_walkLeftAnim->addFrame(sf::IntRect(1340, 428, 68, 88));

	_deathAnim = new Animation();
	_deathAnim->setSpriteSheet(*imgAnim);
	_deathAnim->addFrame(sf::IntRect(7, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(93, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(175, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(260, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(342, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(436, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(534, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(633, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(736, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(839, 541, 92, 77));
	_deathAnim->addFrame(sf::IntRect(940, 541, 92, 77));

	_victoryAnim = new Animation();
	_victoryAnim->setSpriteSheet(*imgAnim);
	_victoryAnim->addFrame(sf::IntRect(14, 621, 83, 103));
	_victoryAnim->addFrame(sf::IntRect(112, 621, 83, 103));
	_victoryAnim->addFrame(sf::IntRect(232, 621, 83, 103));
	_victoryAnim->addFrame(sf::IntRect(318, 621, 83, 103));
	_victoryAnim->addFrame(sf::IntRect(397, 621, 83, 103));
	_victoryAnim->addFrame(sf::IntRect(475, 621, 83, 103));

	_hitUpAnim = new Animation();
	_hitUpAnim->setSpriteSheet(*imgAnim);
	_hitUpAnim->addFrame(sf::IntRect(3, 734, 100, 100));
	_hitUpAnim->addFrame(sf::IntRect(128, 734, 100, 100));
	_hitUpAnim->addFrame(sf::IntRect(226, 734, 100, 100));
	_hitUpAnim->addFrame(sf::IntRect(311, 734, 100, 100));
	_hitUpAnim->addFrame(sf::IntRect(396, 734, 100, 100));

	_hitRightAnim = new Animation();
	_hitRightAnim->setSpriteSheet(*imgAnim);
	_hitRightAnim->addFrame(sf::IntRect(3, 836, 86, 90));
	_hitRightAnim->addFrame(sf::IntRect(155, 836, 86, 90));
	_hitRightAnim->addFrame(sf::IntRect(293, 836, 86, 90));
	_hitRightAnim->addFrame(sf::IntRect(384, 836, 86, 90));
	_hitRightAnim->addFrame(sf::IntRect(465, 836, 86, 90));

	_hitLeftAnim = new Animation();
	_hitLeftAnim->setSpriteSheet(*imgAnim);
	_hitLeftAnim->addFrame(sf::IntRect(548, 836, 86, 90));
	_hitLeftAnim->addFrame(sf::IntRect(631, 836, 86, 90));
	_hitLeftAnim->addFrame(sf::IntRect(719, 836, 86, 90));
	_hitLeftAnim->addFrame(sf::IntRect(816, 836, 86, 90));
	_hitLeftAnim->addFrame(sf::IntRect(1029, 836, 86, 90));

	_hitDownAnim = new Animation();
	_hitDownAnim->setSpriteSheet(*imgAnim);
	_hitDownAnim->addFrame(sf::IntRect(3, 928, 98, 86));
	_hitDownAnim->addFrame(sf::IntRect(147, 928, 98, 86));
	_hitDownAnim->addFrame(sf::IntRect(263, 928, 98, 86));
	_hitDownAnim->addFrame(sf::IntRect(357, 928, 98, 86));
	_hitDownAnim->addFrame(sf::IntRect(459, 928, 98, 86));

	_attackUpAnim = new Animation();
	_attackUpAnim->setSpriteSheet(*imgAnim);
	_attackUpAnim->addFrame(sf::IntRect(15, 1410, 120, 114));
	_attackUpAnim->addFrame(sf::IntRect(162, 1410, 120, 114));
	_attackUpAnim->addFrame(sf::IntRect(352, 1410, 120, 114));
	_attackUpAnim->addFrame(sf::IntRect(501, 1410, 120, 114));
	_attackUpAnim->addFrame(sf::IntRect(635, 1410, 120, 114));

	_attackDownAnim = new Animation();
	_attackDownAnim->setSpriteSheet(*imgAnim);
	_attackDownAnim->addFrame(sf::IntRect(13, 1574, 124, 110));
	_attackDownAnim->addFrame(sf::IntRect(163, 1574, 124, 110));
	_attackDownAnim->addFrame(sf::IntRect(378, 1574, 124, 110));
	_attackDownAnim->addFrame(sf::IntRect(533, 1574, 124, 110));
	_attackDownAnim->addFrame(sf::IntRect(662, 1574, 124, 110));

	_attackRightAnim = new Animation();
	_attackRightAnim->setSpriteSheet(*imgAnim);
	_attackRightAnim->addFrame(sf::IntRect(78, 1720, 104, 114));
	_attackRightAnim->addFrame(sf::IntRect(231, 1720, 104, 114));
	_attackRightAnim->addFrame(sf::IntRect(351, 1720, 104, 114));
	_attackRightAnim->addFrame(sf::IntRect(457, 1720, 104, 114));
	_attackRightAnim->addFrame(sf::IntRect(555, 1720, 104, 114));

	_attackLeftAnim = new Animation();
	_attackLeftAnim->setSpriteSheet(*imgAnim);
	_attackLeftAnim->addFrame(sf::IntRect(663, 1720, 104, 114));
	_attackLeftAnim->addFrame(sf::IntRect(761, 1720, 104, 114));
	_attackLeftAnim->addFrame(sf::IntRect(868, 1720, 104, 114));
	_attackLeftAnim->addFrame(sf::IntRect(997, 1720, 104, 114));
	_attackLeftAnim->addFrame(sf::IntRect(1109, 1720, 104, 114));

	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_animatedSprite->setScale(0.5, 0.5);
	

	_curAnim = _idleDownAnim;


	_animatedSprite->play(*_curAnim);
	
	

	

}

void Player::move(sf::Vector2f &pos)
{
	_position.x += pos.x;
	_position.y += pos.y;

}

void Player::doAction(AEntity* other)
{
	if (other->getType() != PLAYER)
		other->getAction(this);
}

void Player::getAction(AEntity* other)
{
	this->_life -= other->getDamage();
	if (_life <= 0)
		_isDead = true;
}



void Player::setName(std::string const &name)
{
	this->_name = name;
}

std::string const &Player::getName() const
{
	return this->_name;
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
	_position.x = (pos.x - _camera->_position.x) * Chunk::SIZE_OF_CELL;
	_position.y = (pos.y - _camera->_position.y) * Chunk::SIZE_OF_CELL;
	_rect.setPosition(_position);
}

