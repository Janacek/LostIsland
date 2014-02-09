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
	float dt = (float)Singleton::getInstance()._clock->getElapsedTime().asMilliseconds();
	float speed = 0.0001f;
	float calc = dt * speed;
	bool isChangePosition = false;

	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x <= 3.0f)
	{
		if (this->_position.x - calc >= 0)
		{
			this->_position.x -= calc;
			Singleton::getInstance().updatePosLeftClickPressed.x -= calc;
		}
		//isChangePosition = true;
		//if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x <= 3.0f)
		//	sf::Mouse::setPosition(sf::Vector2i(3, (Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y), *(Singleton::getInstance()._window));
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x >= Singleton::getInstance()._window->getSize().x - 3.0f)
	{
		if (this->_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc
			< size.x * Chunk::NB_CELLS)
		{
			this->_position.x += calc;
			Singleton::getInstance().updatePosLeftClickPressed.x += calc;
		}
		//isChangePosition = true;
		//if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x >= Singleton::getInstance()._window->getSize().x - 3.0f)
		//	sf::Mouse::setPosition(sf::Vector2i(Singleton::getInstance()._window->getSize().x - 3.0f, (Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y), *(Singleton::getInstance()._window));
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y <= 3.0f)
	{
		if (this->_position.y - calc >= 0)
		{
			this->_position.y -= calc;
			Singleton::getInstance().updatePosLeftClickPressed.y -= calc;
		}
		//isChangePosition = true;
		//if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y <= 3.0f)
		//	sf::Mouse::setPosition(sf::Vector2i((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x, 3), *(Singleton::getInstance()._window));
	}
	if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y >= Singleton::getInstance()._window->getSize().y - 3.0f)
	{
		if ((_position.y + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) + 1 + calc
			< size.y * Chunk::NB_CELLS)
		{
			this->_position.y += calc;
			Singleton::getInstance().updatePosLeftClickPressed.y += calc;
		}
		/*isChangePosition = true;
		if ((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).y >= Singleton::getInstance()._window->getSize().y - 3.0f)
			sf::Mouse::setPosition(sf::Vector2i((Singleton::getInstance()._window)->mapPixelToCoords(sf::Mouse::getPosition(*(Singleton::getInstance()._window))).x, Singleton::getInstance()._window->getSize().y - 3.0f), *(Singleton::getInstance()._window));*/
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
	float dt = (float)Singleton::getInstance()._clock->getElapsedTime().asMilliseconds();
	float speed = 0.0001f;
	float calc = dt * speed;

	if (this->moveCameraMouse(size) == false)
	{
		if (Singleton::getInstance().isMovingRight)
		{
			if (_position.x + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + calc
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