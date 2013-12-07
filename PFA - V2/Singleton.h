#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

class Singleton
{
public:
	static Singleton& getInstance();
	sf::RenderWindow *_window;
	sf::Clock *_clock;
	bool isLeftClicking;
	bool isRightClicking;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
	

	sf::Vector2f posLeftClick;
	sf::Vector2f posRightClick;
	bool isValidating;
	sf::Clock *_animClock;

private:
	Singleton(const Singleton&) {};
	static Singleton m_instance;
	Singleton();
	~Singleton();
};