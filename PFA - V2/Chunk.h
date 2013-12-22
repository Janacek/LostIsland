#pragma once
#include					<iostream>

#include					<SFML/Graphics.hpp>
#include					<SFML/System.hpp>
#include					<SFML/Window.hpp>

#include					"Cell.h"

/*
** Chunk class, contains an 8 * 8 array of Cells.
** Do not edit this.
*/

class						Chunk
{
public:
	Chunk();
	~Chunk();

private:
	Cell					**_cells;

public:
	static const int		NB_CELLS = 8;
	static const int		SIZE_OF_CELL = 32;

public:
	// Get all the cells contained on the Chunk.
	Cell					**getCells() const;
	Cell					**getCells();

	// Get a cell contained on the Chunk using int coordinates.
	Cell					getCell(int, int) const;
	Cell					getCell(int, int);

	// Get a cell contained on the Chunk using sf::Vector2i coordinates.
	Cell					getCell(sf::Vector2i const &) const;
	Cell					getCell(sf::Vector2i const &);

	void					setCell(Cell::Type);
	void					divideLandIntoWater();

	void					mergeLandsUp();
	void					mergeLandsDown();
	void					mergeLandsLeft();
	void					mergeLandsRight();

	void					dryUselessWaterUpLeft();
	void					dryUselessWaterUpRight();
	void					dryUselessWaterDownLeft();
	void					dryUselessWaterDownRight();

	void					addDetails();
	void					probabilities(int, int);
	void					generateHorizontalGrass(int, int, int, int);
	void					generateVerticalGrass(int, int, int, int);
	void					generateExtendedIsland(int);
	int						countAdjacentChunkType(int, int, Cell::Type);

	bool					isCellTypeAround(int, int, Cell::Type);
	bool					isLandOnCell(int, int);

	void					generateSand();
	void					generateMoreSand();

	void					draw(sf::RenderWindow *win, int, int);
};