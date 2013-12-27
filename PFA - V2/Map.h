#pragma once
#include					<iostream>

#include					<map>

#include					<SFML/Graphics.hpp>
#include					<SFML/System.hpp>
#include					<SFML/Window.hpp>

#include					"Singleton.h"
#include					"ImageSingleton.h"
#include					"Chunk.h"

#include					"PerlinNoise.h"

/*
** This class is used to procedurally generates Islands with different biomes.
** The map is made fully configurable thanks to the init function.
*/

class						Map
{
public:
	Map();
	~Map();

	// Initializes the map.
	void					init(std::string const &, sf::Vector2i, int);
	// Generates the map.
	void					generate();
	void					generateCenterIsland(int);
	void					generateExtendedIsland(int);
	void					generateHorizontalGrass(int, int, int, int);
	void					generateVerticalGrass(int, int, int, int);
	void					probabilities(int, int);
	void					divideLands();
	void					mergeLands();
	void					dryUselessWater();
	void					addDetails();

	void					transformChunkToMap();
	bool					isCellTypeAround(int, int, Cell::Type);

	void					generateBiomes();
	void					generateSand();


	int						countAdjacentChunkType(int, int, Cell::Type);

	// Draw the map.
	void					draw(sf::RenderWindow *);
	// Updates the map.
	void					update();

private:

	// DO NOT MAKE GETTERS FOR THESES
	sf::Vector2i			_size;		  // Size of the map.
	int						_seed;		  // Seed for the random.
	int						_groundRatio; // Ratio of ground cells on the map.

private:
	// THIS CAN HAS A GETTER
	Chunk					**_map;		  // Map container.
	Cell					**_cellMap;

	// LATER BE TEXTURE INSTEAD OF COLOR
	std::map<Cell::Type, sf::Color>				_typeToColor;
	PerlinNoise				*_temperature;
	PerlinNoise				*_humidity;

	Cell					_corTab[100];
};