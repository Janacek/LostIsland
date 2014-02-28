#include "Bunny.h"
#include "ImageSingleton.h"
#include "Map.h"
#include "Chunk.h"
#include "MapEnvironment.h"
#include "Player.h"
#include "Food.h"

Bunny::Bunny(sf::Vector2f &position, int life, Camera *cam)
: _camera(cam), IEntity(1.f, true, sf::Vector2f(position), 0, sf::FloatRect(0, 0, 0, 0), life)
{
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(_position);
	loadAnimation("Media/images/bunny.png", 0.1f);
	_speed = 2;
	_oldTime = 0;
	_iterPath = 0;
	_hasAPath = false;
	_firstPath = true;
}

Bunny::~Bunny()
{

}
void Bunny::changeAnimation(sf::Vector2f&pos, std::pair<float, float>front)
{
	if (front.first > floor(pos.x))
	{
		//_anim->setAnimation(2);
		_curAnim = _walkRight;
	}
	if (front.first < floor(pos.x))
	{
		//_anim->setAnimation(1);
		_curAnim = _walkLeft;
	}
	if (front.second < floor(pos.y))
	{
		//_anim->setAnimation(3);
		_curAnim = _walkUp;
	}
	if (front.second > floor(pos.y))
	{
		//_anim->setAnimation(0);
		_curAnim = _walkDown;
	}
}
void Bunny::moveToNextWP()
{
	double dt = 0;
	double dt2 = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;
	_oldDtMvt = time;
	_animatedSprite->play(*_curAnim);

	/*if (_iterPath > IT_BEF_STOP)
	{
		_isStop = true;
		_path.clear();
		if (_oldTime == 0)
			_oldTime = time;
		dt2 = time - _oldTime;
	}
	if (dt2 > TIMESTOP)
	{
		_isStop = false;
		_iterPath = 0;
		_oldTime = 0;
	}*/
	if (!_path.empty())
	{
		//_anim->play();
		_animatedSprite->play(*_curAnim);
		_isMoving = true;
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;
		//std::cout << "COIN HAUT GAUCHE : x " << floor(_pos.x) << " y " << floor(_pos.y) <<" pos reel droite  x " << floor(tmp.x) << " y "<< floor(tmp.y)  << std::endl;

		if (_path.front().first == floor(_position.x) && _path.front().second == floor(_position.y) &&
			_path.front().first == floor(tmp.x) && _path.front().second == floor(tmp.y)) // && que chaque coté est dans la case

		{
			
			_path.pop_front();
			changeAnimation(_position, _path.front());
			return;
		}

		if (_position.x > _path.front().first)
			_position.x -= static_cast<float>(dt * _speed);
		if (_position.x < _path.front().first)
			_position.x += static_cast<float>(dt * _speed);
		if (_position.y > _path.front().second)
			_position.y -= static_cast<float>(dt *_speed);
		if (_position.y < _path.front().second)
			_position.y += static_cast<float>(dt * _speed);
		//std::cout << "getBoxCollider : x " << _animatedSprite->getGlobalBounds().left << "y " << _animatedSprite->getGlobalBounds().top << std::endl;


	}
	else{
		
		//_anim->pause();
		_animatedSprite->pause();
		_isMoving = false;
		_hasAPath = false;
	}
	sf::Time t = sf::seconds(dt);;
	_animatedSprite->update(t);
}


void Bunny::doAction(IEntity *o)
{
	o->getAction(this);
}

void Bunny::getAction(IEntity *o)
{
	_life -= o->getDamage();
	if (_life <= 0)
	{
		Player *player = dynamic_cast<Player *>(o);
		player->addEntityInInventory(new Food);
	}
}

void Bunny::loadAnimation(std::string const &string_anim, float)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);



	_walkDown = new Animation();
	_walkDown->setSpriteSheet(*imgAnim);
	_walkDown->addFrame(sf::IntRect(0, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(32, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(64, 0, 32, 32));

	_walkLeft = new Animation();
	_walkLeft->setSpriteSheet(*imgAnim);
	_walkLeft->addFrame(sf::IntRect(0, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(32, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(64, 32, 32, 32));

	_walkRight = new Animation();
	_walkRight->setSpriteSheet(*imgAnim);
	_walkRight->addFrame(sf::IntRect(0, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(32, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(64, 64, 32, 32));

	_walkUp = new Animation();
	_walkUp->setSpriteSheet(*imgAnim);
	_walkUp->addFrame(sf::IntRect(0, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(32, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(64, 96, 32, 32));
	

	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _walkDown;


	_animatedSprite->play(*_curAnim);

}

void Bunny::draw(sf::RenderTexture *, sf::Shader &shader) // To edit
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	//this->_anim->show(_posDisp);
	Singleton::getInstance()._window->draw(*_animatedSprite);
}

void Bunny::draw(sf::RenderTexture *)
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	_animatedSprite->setPosition(_posDisp);
	Singleton::getInstance()._window->draw(*_animatedSprite);

	//this->_anim->show(_posDisp);
}

void Bunny::update(Map &map)
{
	if (!_path.empty() && _hasAPath == false) // on va check tous les draw qui sont en rapport aux lapins
	{
		_hasAPath = true;
			map.setEntityMap(NULL, static_cast<int>(floor(_position.y)), static_cast<int>(floor(_position.x)));
		if (map.getEntitiesMap()[static_cast<int>(floor(_path.back().second))][static_cast<int>(floor(_path.back().first))]._component == NULL)
		{
			map.setEntityMap(this, static_cast<int>(floor(_path.back().second)), static_cast<int>(floor(_path.back().first)));
		}
	}
	moveToNextWP();
	//std::cout << " x " << _animatedSprite->getGlobalBounds().left << " y " <<  _animatedSprite->getGlobalBounds().top << std::en
}

Type Bunny::getType() const
{
	return BUNNY;
}