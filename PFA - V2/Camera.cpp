#include "Camera.h"
#include "Singleton.h"
#include "Chunk.h"

std::string &Camera::serialize() const
{
	std::string toto;
	return (toto);
}

void Camera::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Camera::Camera()
: _position(sf::Vector2f(0, 0))
{
	_camClock = new sf::Clock;
	_camClock->restart();

	_speed = 25;
}

Camera::~Camera()
{
}

void Camera::update()
{
}


bool Camera::moveCameraMouse(sf::Vector2i const &size)
{
	double dt = 0;
	double time;

	time = _camClock->getElapsedTime().asSeconds();
	dt = time - _oldTimeMouse;

	_oldTimeMouse = static_cast<float>(time);

	float calc = dt * _speed;
	bool isChangePosition = false;

	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x <= 3.0f)
	{
		if (this->_position.x - calc >= 0)
		{
			this->_position.x -= calc;
			Singleton::getInstance().updatePosLeftClickPressed.x -= calc;
		}
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x >= Singleton::getInstance()._window->getSize().x - 3.0f)
	{
		if (this->_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc + 1
			< size.x * Chunk::NB_CELLS)
		{
			this->_position.x += calc;
			Singleton::getInstance().updatePosLeftClickPressed.x += calc;
		}
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y <= 3.0f)
	{
		if (this->_position.y - calc >= 0)
		{
			this->_position.y -= calc;
			Singleton::getInstance().updatePosLeftClickPressed.y -= calc;
		}
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y >= Singleton::getInstance()._window->getSize().y - 3.0f)
	{
		if ((_position.y + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) + 1 + calc
			< size.y * Chunk::NB_CELLS)
		{
			this->_position.y += calc;
			Singleton::getInstance().updatePosLeftClickPressed.y += calc;
		}
	}
	if (!Singleton::getInstance().isLeftClicking)
	{
		Singleton::getInstance().updatePosLeftClickPressed.x = 0;
		Singleton::getInstance().updatePosLeftClickPressed.y = 0;
	}
	return (isChangePosition);
}

void Camera::moveCamera(sf::Vector2i const &size)
{
	double dt = 0;
	double time;

	time = _camClock->getElapsedTime().asSeconds();
	dt = time - _oldTime;

	_oldTime = static_cast<float>(time);

	float calc = dt * _speed;

	if (this->moveCameraMouse(size) == false)
	{
		if (Singleton::getInstance().isMovingRight)
		{
			if (_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc + 1
				< size.x * Chunk::NB_CELLS)
			{
				_position.x += calc;
				Singleton::getInstance().updatePosLeftClickPressed.x += calc;
			}
		}
		if (Singleton::getInstance().isMovingLeft)
		{
			if (_position.x - calc >= 0)
			{
				Singleton::getInstance().updatePosLeftClickPressed.x -= calc;
				_position.x -= calc;
			}
		}

		if (Singleton::getInstance().isMovingUp)
		{
			if (_position.y - calc >= 0)
			{
				_position.y -= calc;
				Singleton::getInstance().updatePosLeftClickPressed.y -= calc;
			}
		}
		if (Singleton::getInstance().isMovingDown)
		{
			if ((_position.y + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) + 1 + calc
				< size.y * Chunk::NB_CELLS)
			{
				_position.y += calc;
				Singleton::getInstance().updatePosLeftClickPressed.y += calc;
			}
		}
	}
	if (!Singleton::getInstance().isLeftClicking)
	{
		Singleton::getInstance().updatePosLeftClickPressed.x = 0;
		Singleton::getInstance().updatePosLeftClickPressed.y = 0;
	}
}