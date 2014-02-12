#include "Singleton.h"

Singleton Singleton::m_instance = Singleton();

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
	this->isEscapePressed = false;

	this->posLeftClickPressed = sf::Vector2i(0, 0);
	this->posLeftClickReleased = sf::Vector2i(0, 0);
	this->posRightClickPressed = sf::Vector2i(0, 0);
	this->posRightClickReleased = sf::Vector2i(0, 0);

	_clock = new sf::Clock();
	_animClock = new sf::Clock();

	//_selectedShader.loadFromFile("./shaders/selectedShader.vert", "./shaders/selectedShader.frag");
	_selectedShader.loadFromFile("./shaders/selectedShader.vert", "./shaders/selectedShader.frag");

	_glowShader.loadFromFile("./shaders/glowShader.vert", "./shaders/glowShader.frag");

	//_selectedShader.loadFromFile("./shaders/selectedShader.frag", sf::Shader::Fragment);
}

Singleton& Singleton::getInstance()
{
	return m_instance;
}

Singleton::~Singleton()
{
}