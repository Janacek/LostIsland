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
	else if (k == sf::Keyboard::Escape)
		Singleton::getInstance().isEscapePressed = isPressed;
	else if (k == sf::Keyboard::LShift || k == sf::Keyboard::RShift)
		Singleton::getInstance().isShiftPressed = isPressed;


	if (k == sf::Keyboard::I && isPressed)
		Singleton::getInstance().isKeyIPressed = !Singleton::getInstance().isKeyIPressed;
	else if (k == sf::Keyboard::Num1 && isPressed)
		Singleton::getInstance().isKey1Pressed = !Singleton::getInstance().isKey1Pressed;
	else if (k == sf::Keyboard::Num2 && isPressed)
		Singleton::getInstance().isKey2Pressed = !Singleton::getInstance().isKey2Pressed;
	else if (k == sf::Keyboard::Num3 && isPressed)
		Singleton::getInstance().isKey3Pressed = !Singleton::getInstance().isKey3Pressed;
	else if (k == sf::Keyboard::Num4 && isPressed)
		Singleton::getInstance().isKey4Pressed = !Singleton::getInstance().isKey4Pressed;

}

void KeyboardControler::handlePlayerInput(sf::Mouse::Button &k, bool isPressed)
{
	if (k == sf::Mouse::Left)
	{
		Singleton::getInstance().isLeftClicking = isPressed;
		if (isPressed)
		{
			Singleton::getInstance().posLeftClickPressed = sf::Mouse::getPosition(*Singleton::getInstance()._window);

		}
		else
		{
			Singleton::getInstance().posLeftClickReleased = sf::Mouse::getPosition(*Singleton::getInstance()._window);
			Singleton::getInstance().updatePosLeftClickPressed.x = 0;
			Singleton::getInstance().updatePosLeftClickPressed.y = 0;
		}
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