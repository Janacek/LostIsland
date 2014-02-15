#include					"Cell.h"

Cell::Cell()
: _shape(sf::RectangleShape(sf::Vector2f(32, 32)))
{
	_cellType = Cell::OCEAN;
}

Cell::~Cell()
{
}