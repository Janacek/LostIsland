#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "SerializeTools.h"

class Camera
{
public:
	Camera();
	~Camera();
	
	void				moveCamera(sf::Vector2i const &);
	void				update();

public:
	bool				moveCameraMouse(sf::Vector2i const &size);
	sf::Vector2f		_position;

	sf::Clock			*_camClock;
	float				_oldTime;
	float				_oldTimeMouse;
	float				_speed;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
};