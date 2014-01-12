#include "Camera.h"
#include "Singleton.h"
#include "Chunk.h"

Camera::Camera()
	: _position(sf::Vector2f(0, 0))
{
}

Camera::~Camera()
{
}

void Camera::update()
{
}


bool Camera::moveCameraMouse(sf::Vector2i const &size)
{
	float dt = Singleton::getInstance()._clock->getElapsedTime().asMilliseconds();
	float speed = 0.0001;
	float calc = dt * speed;
	bool isChangePosition = false;
	
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x < 5.0f)
	{
		if (this->_position.x - calc >= 0)
			this->_position.x -= calc;
		isChangePosition = true;
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x > Singleton::getInstance()._window->getSize().x - 5.0f)
	{
		if (this->_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc
			< size.x * Chunk::NB_CELLS)
			this->_position.x += calc;
		isChangePosition = true;
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y < 5.0f)
	{
		if (this->_position.y - calc >= 0)
			this->_position.y -= calc;
		isChangePosition = true;
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y > Singleton::getInstance()._window->getSize().y - 5.0f)
	{
		if ((_position.y + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) + 1 + calc
			< size.y * Chunk::NB_CELLS)
			this->_position.y += calc;
		isChangePosition = true;
	}
	return (isChangePosition);
}

void Camera::moveCamera(sf::Vector2i const &size)
{
	float dt = Singleton::getInstance()._clock->getElapsedTime().asMilliseconds();
	float speed = 0.0001;
	float calc = dt * speed;

	if (this->moveCameraMouse(size) == false)
	{
		if (Singleton::getInstance().isMovingRight)
			if (_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc
				< size.x * Chunk::NB_CELLS)
				_position.x += calc;
		if (Singleton::getInstance().isMovingLeft)
			if (_position.x - calc >= 0)
				_position.x -= calc;

		if (Singleton::getInstance().isMovingUp)
			if (_position.y - calc >= 0)
				_position.y -= calc;
		if (Singleton::getInstance().isMovingDown)
			if ((_position.y + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) + 1 + calc
				< size.y * Chunk::NB_CELLS)
				_position.y += calc;
	}
}