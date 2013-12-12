#include "GameEngine.h"
#include "KeyboardControler.h"
#include "Singleton.h"

KeyboardControler::KeyboardControler()
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
	else if (k == sf::Keyboard::I)
		Singleton::getInstance().isKeyIPressed = isPressed;
}