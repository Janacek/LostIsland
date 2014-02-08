#include "Bunny.h"

Bunny::Bunny()
{
	_isMoving = false;
}

Bunny::Bunny(sf::Vector2f &position, int life, Camera *cam)
: _position(position), _life(life), _camera(cam)
{
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(_position);
	loadAnimation("bunny", 0.1f);
	_isMoving = false;
	_pathToGo = 1.f;
	_speed = 8;
	_oldTime = 0;
	_isPathFound = false;
	_iterPath = 0;
}

Bunny::~Bunny()
{

}

void Bunny::moveToNextWP()
{
	double dt = 0;
	double dt2 = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;
	_oldDtMvt = time;
	
	if (_iterPath > IT_BEF_STOP)
	{
		
		_path.clear();
		if (_oldTime == 0)
			_oldTime = time;
		dt2 = time - _oldTime;
	}
	if (dt2 > TIMESTOP)
	{
		_iterPath = 0;
		_oldTime = 0;
	}
	if (!_path.empty())
	{

		_isMoving = true;
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;
		//std::cout << "COIN HAUT GAUCHE : x " << floor(_pos.x) << " y " << floor(_pos.y) <<" pos reel droite  x " << floor(tmp.x) << " y "<< floor(tmp.y)  << std::endl;

		if (_path.front().first == floor(_position.x) && _path.front().second == floor(_position.y) &&
			_path.front().first == floor(tmp.x) && _path.front().second == floor(tmp.y)) // && que chaque coté est dans la case

		{
			++_iterPath;
			_path.pop_front();
			return;
		}

		if (_position.x > _path.front().first)
			_position.x -= dt * _speed;
		if (_position.x < _path.front().first)
			_position.x += dt * _speed;
		if (_position.y > _path.front().second)
			_position.y -= dt *_speed;
		if (_position.y < _path.front().second)
			_position.y += dt * _speed;

	}
	else
		_isMoving = false;
}


void Bunny::setIsPathFound(bool p )
{
	_isPathFound = p;
}

bool const Bunny::getIsPathFound() const
{
	return _isPathFound;
}

float Bunny::getPathToGo() const
{
	return _pathToGo;
}

void Bunny::setPathToGo(float p) 
{
	_pathToGo = p;
}

void Bunny::addToPathToGo(float p)
{
	_pathToGo += p;
}

bool Bunny::getIsMoving() const
{
	return _isMoving;
}
void Bunny::doAction(IEntity *o)
{
	o->getAction(this);
}

void Bunny::getAction(IEntity *o)
{
	_life -= o->getDamage();
}

void Bunny::loadAnimation(std::string const &, float)
{
	this->_anim = new Animation(ImageSingleton::getInstance().get(BUNNY), 2, 3, 0.1f);
	this->_anim->setAnimation(0);
}

void Bunny::draw()
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	/*sf::Vector2f v(0, -10);
	_rect.setPosition(_posDisp);
	Singleton::getInstance()._window->draw(_rect);*/
	this->_anim->show(_posDisp);
}

void Bunny::update(Map &map)
{
	moveToNextWP();
}

void Bunny::setPath(std::list<std::pair<float, float>> &list)
{
	_path = list;
}

void Bunny::setPosition(sf::Vector2f &vec)
{
	_position = vec;
}

sf::Vector2f Bunny::getPosition() const
{
	return _position;
}

int Bunny::getDamage(void) const
{
	return 0;
}

Type Bunny::getType() const
{
	return BUNNY;
}