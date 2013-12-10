#pragma once

#include					<SFML/Graphics.hpp>
#include					<SFML/Window.hpp>
#include					<SFML/System.hpp>

class Coordinates
{
public:
	Coordinates(int x, int y)
		: _x(x), _y(y) {};
	Coordinates(Coordinates &pos)
		: _x(pos._x), _y(pos._y) {};
	~Coordinates() {};

public:
	unsigned int				_x;
	unsigned int				_y;
};