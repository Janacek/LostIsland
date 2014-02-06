#include "Bunny.h"

Bunny::Bunny()
{
}

Bunny::Bunny(sf::Vector2f &position, int life, Camera *cam)
: _position(position), _life(life), _camera(cam)
{
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(_position);
	loadAnimation("bunny", 0.1f);
}

Bunny::~Bunny()
{

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

void Bunny::update()
{

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