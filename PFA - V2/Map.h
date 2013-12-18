#pragma once
#include				<iostream>
#include				<deque>
#include				<algorithm>
#include				<list>

#include				<SFML/System.hpp>
#include				<SFML/Graphics.hpp>
#include				<SFML/Window.hpp>


#include				"Area.h"
#include				"Object.h"
#include				"Coordinates.hpp"
#include				"VoronoiDiagramGenerator.h"
#include				"Polygon.h"
#include				"Chunk.h"
#include				"PerlinNoise.h"

#include				"Singleton.h"

class												Map
{
public:
	Map(std::pair<unsigned int, unsigned int>, int);
	~Map();
	void											draw(sf::RenderWindow *);
	void											update();
	void											setSize(std::pair<unsigned int, unsigned int>);
	std::pair<unsigned int, unsigned int>			getSize();
	void											generateVoronoiPolygons();
	Chunk											**getChunks();
//private:
	PerlinNoise										*_perlinNoise;
	std::pair<unsigned int, unsigned int>			_size;
	int												_seed;
	std::pair<int, int>								_sizeOfChunks;
	std::deque<Coordinates>							_points;
	std::deque<Polygon_ *>							_polygons;
	Chunk											**_chunks;

	/*
	** list of chunks to draw, useful to know which chunks to unload from memory.
	*/
	std::list<
			std::pair<Chunk *,
					std::pair<sf::Vector2f,
							bool>>>					_drawableChunks;
};