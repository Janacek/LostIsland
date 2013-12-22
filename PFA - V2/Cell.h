#pragma once
#include					<iostream>

#include					<SFML/Graphics.hpp>
#include					<SFML/System.hpp>
#include					<SFML/Window.hpp>

/*
** Cell class, contains the type of terrain the cell is.
*/

class						Cell
{
public:
	enum					Type
	{
		OCEAN = 0,
		GRASS,
		SAND,
		ROCK,
	};

public:
	Cell();
	~Cell();
	
	// Cell type.
	Type					_cellType;
};