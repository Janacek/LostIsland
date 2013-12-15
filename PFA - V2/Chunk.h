#pragma once

#include						<deque>
#include						<SFML/Graphics.hpp>
#include						"Polygon.h"

class Chunk
{
public:
	Chunk();
	~Chunk();
	std::deque<Polygon_ *>		_polygons;
	static const int			_width = 512;
	static const int			_height = 512;
	std::pair<int, int>			_pos;

private:
	sf::RenderTexture			*_texture;
	std::deque<sf::ConvexShape>	_convexShapes;

public:
	sf::RenderTexture			*getTexture();
	void						addPolygon(Polygon_ *);
	void						unload();
};