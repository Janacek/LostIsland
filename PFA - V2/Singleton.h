#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>
#include						<SFGUI/SFGUI.hpp>


class Singleton
{
public:
	static Singleton& getInstance();
	sf::RenderWindow *_window;
	sf::Clock *_clock;
	
	sfg::SFGUI		_sfgui;

	int deltaMouseWeel;
	bool isKeyPressed;
	bool isEscapePressed;
	bool isLeftClicking;
	bool isRightClicking;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
	bool isKeyIPressed;
	bool isKey1Pressed;
	bool isKey2Pressed;
	bool isKey3Pressed;
	bool isKey4Pressed;
	bool isShiftPressed;
	
	sf::Vector2i posLeftClickPressed;
	sf::Vector2i posLeftClickReleased;
	sf::Vector2i posRightClickPressed;
	sf::Vector2i posRightClickReleased;

	sf::Vector2f updatePosLeftClickPressed;

	bool isValidating;
	bool isRunning;
	sf::Mutex mutex;
	sf::Clock *_animClock;
	sfg::Desktop _desktop;

	bool gameOver;

	
private:
	Singleton(const Singleton&) {};
	static Singleton m_instance;
	Singleton();
	~Singleton();
};