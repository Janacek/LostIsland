#include "Object.h"

Object::Object(Coordinates &pos) : Coordinates(pos)
{

}

Object::~Object()
{

}

void Object::print() const
{
	//std::cout << "Ici nous printons un object." << std::endl;
}

void		Object::draw(sf::RenderWindow *)
{

}

void		Object::update(sf::Event *)
{

}