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

	bool isEscapePressed;
	bool isLeftClicking;
	bool isRightClicking;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
	bool isKeyIPressed;
	
	sf::Vector2i posLeftClickPressed;
	sf::Vector2i posLeftClickReleased;
	sf::Vector2i posRightClickPressed;
	sf::Vector2i posRightClickReleased;
	bool isValidating;
	sf::Clock *_animClock;

	
private:
	Singleton(const Singleton&) {};
	static Singleton m_instance;
	Singleton();
	~Singleton();
};