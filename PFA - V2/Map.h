#pragma once
#include				<iostream>
#include				<deque>
#include				<algorithm>

#include				"Area.h"
#include				"Object.h"
#include				"Coordinates.hpp"
#include				"VoronoiDiagramGenerator.h"
#include				"Polygon.h"
#include				"Chunk.h"
#include				"PerlinNoise.h"

class										Map
{
public:
	Map(std::pair<unsigned int, unsigned int>, int);
	~Map();
	void									draw(sf::RenderWindow *);
	void									update(sf::Event *);
	void									setSize(std::pair<unsigned int, unsigned int>);
	std::pair<unsigned int, unsigned int>	getSize();
	void									generateVoronoiPolygons();
	Chunk									**getChunks();
//private:
	PerlinNoise								*_perlinNoise;
	std::pair<unsigned int, unsigned int>	_size;
	int										_seed;
	std::pair<int, int>						_sizeOfChunks;
	std::deque<Coordinates>					_points;
	std::deque<Polygon *>					_polygons;
	Chunk									**_chunks;
};