#include "GameEngine.h"
#include "KeyboardControler.h"
#include "Singleton.h"

KeyboardControler::KeyboardControler()
{

}
KeyboardControler::~KeyboardControler()
{
}

void KeyboardControler::handlePlayerInput(sf::Keyboard::Key& k, bool isPressed)
{
	if (k == sf::Keyboard::Up)
		Singleton::getInstance().isMovingUp = isPressed;
	else if (k == sf::Keyboard::Left )
		Singleton::getInstance().isMovingLeft = isPressed;
	else if (k == sf::Keyboard::Right)
		Singleton::getInstance().isMovingRight = isPressed;
	else if ( k == sf::Keyboard::Down)
		Singleton::getInstance().isMovingDown = isPressed;
	else if (k == sf::Keyboard::Return)
		Singleton::getInstance().isValidating = isPressed;
	if (k == sf::Keyboard::I && isPressed)
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
}

void KeyboardControler::handlePlayerInput(sf::Mouse::Button &k, bool isPressed)
{
	if (k == sf::Mouse::Left)
	{
		Singleton::getInstance().isLeftClicking = isPressed;
		if (isPressed)
			Singleton::getInstance().posLeftClickPressed = sf::Mouse::getPosition(*Singleton::getInstance()._window);
		else 
			Singleton::getInstance().posLeftClickReleased = sf::Mouse::getPosition(*Singleton::getInstance()._window);
	}
	else if (k == sf::Mouse::Right)
	{
		Singleton::getInstance().isRightClicking = isPressed;
		if (isPressed)
			Singleton::getInstance().posRightClickPressed = sf::Mouse::getPosition(*Singleton::getInstance()._window);
		else
			Singleton::getInstance().posRightClickReleased = sf::Mouse::getPosition(*Singleton::getInstance()._window);
	}
}