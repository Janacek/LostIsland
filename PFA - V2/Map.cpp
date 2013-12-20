#include "Map.h"

Map::Map()
{
	_size = sf::Vector2i(16, 16);
	_seed = 0xcafe; // OLOL
	_groundRatio = 33;
}

Map::~Map()
{
}

static unsigned int generateHash(std::string const & string)
{
    unsigned int hash = 0;
	for(size_t i = 0; i < string.length(); ++i) 
		hash = 65599 * hash + string.at(i);
    return hash ^ (hash >> 16);
}

void						Map::init(std::string const & seed, sf::Vector2i size, int groundRatio)
{
	_size = size;
	_seed = generateHash(seed);
	if (_seed == 0)
		_seed = rand() % INT_MAX;
	groundRatio = groundRatio > 100 ? 100 : groundRatio;
	groundRatio = groundRatio < 0 ? 0 : groundRatio;
	_groundRatio = groundRatio;
}

void						Map::generateCenterIsland(int ratio)
{
	int startX = (int)(ceil(((float)_size.x * (float)ratio) / (float)100));
	int startY = (int)(ceil(((float)_size.y * (float)ratio) / (float)100));

	int stopX = (int)(startX + (((float)_size.x * (float)_groundRatio) / (float)100));
	int stopY = (int)(startY + (((float)_size.x * (float)_groundRatio) / (float)100));

	for (int i = startY ; i <= stopY ; ++i)
		for (int j = startX ; j <= stopX ; ++j)
			_map[i][j].setCell(Cell::GRASS);
}

void						Map::probabilities(int x, int y)
{
	int mod;
	int nbr = countAdjacentChunkType(x, y, Cell::GRASS);
	mod = nbr;
	if (nbr == 2)
		mod = 7;
	else if (nbr == 3)
		mod = 10;
	else if (nbr == 4)
		mod = 8;
	if (rand() % 10 < mod)
		_map[x][y].setCell(Cell::GRASS);
}

void						Map::generateHorizontalGrass(int startX,
														 int startY,
														 int stopX,
														 int stopY)
{
	if (startX < stopX)
		for (int i = startX ; i <= stopX ; ++i)
			probabilities(startY, i);
	else if (stopX < startX)
		for (int i = stopX ; i <= startX ; ++i)
			probabilities(startY, i);
}

void						Map::generateVerticalGrass(int startX,
													   int startY,
													   int stopX,
													   int stopY)
{
	if (startY < stopY)
		for (int i = startY ; i <= stopY ; ++i)
			probabilities(i, startX);
	else if (stopY < startY)
		for (int i = stopY ; i <= startY ; ++i)
			probabilities(i, startX);
}

void						Map::generateExtendedIsland(int ratio)
{
	int startX = (int)(ceil(((float)_size.x * (float)ratio) / (float)100));
	int startY = (int)(ceil(((float)_size.y * (float)ratio) / (float)100));

	int stopX = (int)(startX + (((float)_size.x * (float)_groundRatio) / (float)100));
	int stopY = (int)(startY + (((float)_size.x * (float)_groundRatio) / (float)100));

	for (int i = 1 ; i <= 3 ; ++i)
	{
		generateHorizontalGrass(startX, startY - i, stopX + 1, startY - i);

		generateVerticalGrass(stopX + i, startY - i, stopX + i, stopY + i);

		generateHorizontalGrass(stopX + i, stopY + i, startX - i, stopY + i);

		generateVerticalGrass(startX - i, stopY + i, startX - i, startY - i - 1);
	}
}

int							Map::countAdjacentChunkType(int x, int y, Cell::Type type)
{
	int nbr = 0;
	for (int i = y - 1 ; i <= y + 1 ; ++i)
	{
		for (int j = x - 1 ; j <= x + 1 ; ++j)
		{
			if (i >= 0 && i < _size.y && j >= 0 && j < _size.x)
			{
				if (_map[i][j].getCell(0, 0)._cellType == type)
					++nbr;
			}
		}
	}
	return nbr;
}

void						Map::generate()
{
	srand(_seed);

	_map = new Chunk*[_size.x];
	for (int i = 0 ; i < _size.x ; ++i)
		_map[i] = new Chunk[_size.y];

	int ratio;
	ratio = (100 - _groundRatio) / 2;
	generateCenterIsland(ratio);
	generateExtendedIsland(ratio);
	divideLands();
	mergeLands();
	dryUselessWater();
	addDetails();
	generateSand();
}

void						Map::divideLands()
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			if (_map[i][j].getCell(0, 0)._cellType == Cell::GRASS)
			{
				_map[i][j].divideLandIntoWater();
			}
		}
	}
}

void						Map::mergeLands()
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			if (_map[i][j].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS &&
				_map[i][j + 1].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS)
			{
				_map[i][j].mergeLandsDown();
				_map[i][j + 1].mergeLandsUp();
			}
			if (_map[i][j].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS &&
				_map[i - 1][j].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS)
			{
				_map[i][j].mergeLandsRight();
				_map[i - 1][j].mergeLandsLeft();
			}
		}
	}
}

void						Map::dryUselessWater()
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			if (_map[i][j].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS &&
				_map[i][j + 1].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS &&
				_map[i + 1][j].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS &&
				_map[i + 1][j + 1].getCell(Chunk::SIZE_OF_CELL / Chunk::NB_CELLS,
				Chunk::SIZE_OF_CELL / Chunk::NB_CELLS)._cellType == Cell::GRASS)
			{
				_map[i + 1][j + 1].dryUselessWaterUpLeft();
				_map[i][j + 1].dryUselessWaterUpRight();
				_map[i][j].dryUselessWaterDownRight();
				_map[i + 1][j].dryUselessWaterDownLeft();
			}
		}
	}
}

void						Map::addDetails()
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			_map[i][j].addDetails();
		}
	}
}

void						Map::generateSand()
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			_map[i][j].generateSand();
		}
	}}

void						Map::draw(sf::RenderWindow *win)
{
	for (int i = 0 ; i < _size.y ; ++i)
	{
		for (int j = 0 ; j < _size.x ; ++j)
		{
			_map[i][j].draw(win, i, j);
			/*sf::RectangleShape tmp(sf::Vector2f(32, 32));
			tmp.setFillColor(sf::Color::Transparent);
			tmp.setOutlineColor(sf::Color::Black);
			tmp.setOutlineThickness(1);
			tmp.setPosition(i * 32, j * 32);
			win->draw(tmp);*/
		}
	}
}

void						Map::update()
{
}