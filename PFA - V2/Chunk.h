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

public:
	sf::RenderTexture			*_texture;
	std::deque<sf::ConvexShape>	_convexShapes;

public:
	sf::RenderTexture			*getTexture();
	sf::RenderTexture			*getGeneratedTexture();
	void						addPolygon(Polygon_ *);
	void						unload();

	bool						_generated;
	bool						_generating;
};