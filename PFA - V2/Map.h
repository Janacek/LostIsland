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

#include					"Camera.h"

#include					<list>
#include					"Tree.h"

#include					"MapEnvironment.h"
#include					"ForestTree.h"
#include					"Bush.h"
#include					"PalmTree.h"

#include <algorithm>

/*
** This class is used to procedurally generates Islands with different biomes.
** The map is made fully configurable thanks to the init function.
*/

class						Map
{
public:
	Map(Camera *);
	~Map();

	sf::Vector2f			&getCamPos();
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

	void					generateTrees();

	// Draw the map.
	void					draw(sf::RenderWindow *);
	// Updates the map.
	void					update();
	Chunk					**getMap() const;
	Cell					**getCellMap() const;
	sf::Vector2i			getSize() const;


private:

	// DO NOT MAKE GETTERS FOR THESES
	sf::Vector2i			_size;		  // Size of the map.
	int						_seed;		  // Seed for the random.
	int						_groundRatio; // Ratio of ground cells on the map.

private:
	// THIS CAN HAS A GETTER
	Chunk					**_map;		  // Map container.
	Cell					**_cellMap;	  // Cell Map container.
	MapEnvironment			**_entitiesMap; // Enitites container.

	// LATER BE TEXTURE INSTEAD OF COLOR
	std::map<Cell::Type, sf::Color>				_typeToColor;
	std::map<Cell::Type, sf::Texture *>			_typeToTexture;

	PerlinNoise				*_temperature;
	PerlinNoise				*_humidity;

	Cell					_corTab[100];

	Camera					*_camera;

	float hori;
	float vert;
	sf::Vector2f			_camPos;
	/*
	** Methodes and Attributes for the minimap.
	*/
private:
	sf::RenderTexture		*_miniMapT;

	// A SUPPRIMER LE PLUS VITE POSSIBLE.
	std::list<Tree *>		_trees;
	std::list<Tree *>		_bushes;
	std::list<Tree *>		_palmtrees;

public:
	void					createMiniMap();
	void					drawMiniMap(sf::RenderWindow *);
};