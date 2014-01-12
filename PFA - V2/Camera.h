#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void				moveCamera(sf::Vector2i const &);
	void				update();

public:
	sf::Vector2f		_position;
};