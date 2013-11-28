#pragma once
#include				<iostream>
#include				<deque>

#include				"Area.h"
#include				"Object.h"
#include				"Coordinates.hpp"
#include				"VoronoiDiagramGenerator.h"
#include				"Polygon.h"
#include				"Chunk.h"

class										Map : public IDisplay
{
public:
	Map(std::pair<unsigned int, unsigned int>, int);
	~Map();
	void									draw(sf::RenderWindow *);
	void									update(sf::Event *);
	void									setSize(std::pair<unsigned int, unsigned int>);
	std::pair<unsigned int, unsigned int>	getSize();
	void									generateVoronoiPolygons();
private:
	std::pair<unsigned int, unsigned int>	_size;
	int										_seed;
	std::pair<int, int>						_sizeOfChunks;
	std::deque<Coordinates>					_points;
	std::deque<Polygon *>					_polygons;
	sf::RenderTexture						_img;
	Chunk									**_chunks;
};