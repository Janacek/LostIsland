#include "Singleton.h"

Singleton Singleton::m_instance=Singleton();

Singleton::Singleton()
{
	this->isLeftClicking = false;
	this->isRightClicking = false;
	this->isValidating = false;
	this->isMovingUp = false;
	this->isMovingDown = false;
	this->isMovingRight = false;
	this->isMovingLeft = false;
	this->isKeyIPressed = false;

	this->posLeftClick = sf::Vector2f(0, 0);
	this->posRightClick = sf::Vector2f(0, 0);

	_clock = new sf::Clock();
	_animClock = new sf::Clock();

}

Singleton& Singleton::getInstance()
{
	return m_instance;
}

Singleton::~Singleton()
{
}