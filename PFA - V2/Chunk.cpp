#include "Chunk.h"

Chunk::Chunk()
{
	_cells = new Cell*[NB_CELLS];
	for (int i = 0 ; i < NB_CELLS ; ++i)
		_cells[i] = new Cell[NB_CELLS];
}

Chunk::~Chunk()
{
}

Cell					**Chunk::getCells() const
{
	return _cells;
}

Cell					**Chunk::getCells()
{
	return _cells;
}

Cell					Chunk::getCell(int x, int y) const
{
	return _cells[x][y];
}

Cell					Chunk::getCell(int x, int y)
{
	return _cells[x][y];
}

Cell					Chunk::getCell(sf::Vector2i const &pos) const
{
	return _cells[pos.x][pos.y];
}

Cell					Chunk::getCell(sf::Vector2i const &pos)
{
	return _cells[pos.x][pos.y];
}

void					Chunk::setCell(Cell::Type type)
{
	for (int i = 0 ; i < NB_CELLS ; ++i)
		for (int j = 0 ; j < NB_CELLS ; ++j)
			_cells[i][j]._cellType = type;
}

void					Chunk::divideLandIntoWater()
{
	int middle = NB_CELLS / 2;
	int start = middle / 2;
	setCell(Cell::OCEAN);
	for (int i = start ; i < start + middle ; ++i)
	{
		for (int j = start ; j < start + middle ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::mergeLandsUp()
{
	int startX = (SIZE_OF_CELL / NB_CELLS) / 2;
	int startY = 0;

	for (int i = startY ; i < ((SIZE_OF_CELL / NB_CELLS) / 2) ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::mergeLandsDown()
{
	int startX = (SIZE_OF_CELL / NB_CELLS) / 2;
	int startY = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);

	for (int i = startY ; i < startY + ((SIZE_OF_CELL / NB_CELLS) / 2) ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::mergeLandsLeft()
{
	int startX = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);
	int startY = 0 + (SIZE_OF_CELL / NB_CELLS) / 2;

	for (int i = startY ; i < startY + SIZE_OF_CELL / NB_CELLS; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::mergeLandsRight()
{
	int startX = 0;
	int startY = 0 + (SIZE_OF_CELL / NB_CELLS) / 2;

	for (int i = startY ; i < startY + SIZE_OF_CELL / NB_CELLS; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::dryUselessWaterUpLeft()
{
	int startX = 0;
	int startY = 0;

	for (int i = startY ; i < startY + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::dryUselessWaterUpRight()
{
	int startX = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);
	int startY = 0;

	for (int i = startY ; i < startY + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::dryUselessWaterDownLeft()
{
	int startX = 0;
	int startY = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);

	for (int i = startY ; i < startY + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}

void					Chunk::dryUselessWaterDownRight()
{
	int startX = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);
	int startY = (SIZE_OF_CELL / NB_CELLS) / 2 + (SIZE_OF_CELL / NB_CELLS);

	for (int i = startY ; i < startY + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++i)
	{
		for (int j = startX ; j < startX + (SIZE_OF_CELL / NB_CELLS) / 2 ; ++j)
		{
			_cells[i][j]._cellType = Cell::GRASS;
		}
	}
}



void					Chunk::probabilities(int x, int y)
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
		_cells[x][y]._cellType = Cell::GRASS;
}

void					Chunk::generateHorizontalGrass(int startX,
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

void					Chunk::generateVerticalGrass(int startX,
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

void					Chunk::generateExtendedIsland(int ratio)
{
	int startX = (int)(ceil(((float)NB_CELLS * (float)ratio) / (float)100));
	int startY = (int)(ceil(((float)NB_CELLS * (float)ratio) / (float)100));

	int stopX = (int)(startX + (((float)NB_CELLS * (float)0) / (float)100));
	int stopY = (int)(startY + (((float)NB_CELLS * (float)0) / (float)100));

	for (int i = 1 ; i <= 3 ; ++i)
	{
		generateHorizontalGrass(startX, startY - i, stopX + 1, startY - i);

		generateVerticalGrass(stopX + i, startY - i, stopX + i, stopY + i);

		generateHorizontalGrass(stopX + i, stopY + i, startX - i, stopY + i);

		generateVerticalGrass(startX - i, stopY + i, startX - i, startY - i - 1);
	}
}

int						Chunk::countAdjacentChunkType(int x, int y, Cell::Type type)
{
	int nbr = 0;
	for (int i = y - 1 ; i <= y + 1 ; ++i)
	{
		for (int j = x - 1 ; j <= x + 1 ; ++j)
		{
			if (i >= 0 && i < NB_CELLS && j >= 0 && j < NB_CELLS)
			{
				if (_cells[i][j]._cellType == type)
					++nbr;
			}
		}
	}
	return nbr;
}

bool					Chunk::isCellTypeAround(int x, int y, Cell::Type type)
{
	if (y - 1 >= 0 && _cells[y - 1][x]._cellType == type)
		return true;
	else if (y + 1 < NB_CELLS && _cells[y + 1][x]._cellType == type)
		return true;
	else if (x - 1 >= 0 && _cells[y][x - 1]._cellType == type)
		return true;
	else if (x + 1 < NB_CELLS && _cells[y][x + 1]._cellType == type)
		return true;
	return (false);
}

bool					Chunk::isLandOnCell(int x, int y)
{
	for (int i = 0 ; i < NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < NB_CELLS ; ++j)
		{
			if (_cells[x][y]._cellType == Cell::GRASS)
				return true;
		}
	}
	return false;
}

void					Chunk::addDetails()
{
	if (_cells[SIZE_OF_CELL / NB_CELLS][SIZE_OF_CELL / NB_CELLS]._cellType ==
		Cell::GRASS)
	{
		int nbLands = rand() % 40;
		int stop = 0;
		while (nbLands > 0)
		{
			if (stop > NB_CELLS * NB_CELLS)
				return ;
			int x = rand() % NB_CELLS;
			int y = rand() % NB_CELLS;
			if (_cells[x][y]._cellType != Cell::GRASS &&
				isCellTypeAround(y, x, Cell::GRASS))
			{
				_cells[x][y]._cellType = Cell::GRASS;
				--nbLands;
			}
			++stop;
		}
	}
}

void					Chunk::generateMoreSand()
{
	if (_cells[SIZE_OF_CELL / NB_CELLS][SIZE_OF_CELL / NB_CELLS]._cellType ==
		Cell::GRASS ||
		_cells[SIZE_OF_CELL / NB_CELLS][SIZE_OF_CELL / NB_CELLS]._cellType ==
		Cell::SAND)
	{
		int nbLands = 1;
		int stop = 0;
		while (nbLands > 0)
		{
			if (stop > NB_CELLS * NB_CELLS)
				return ;
			int x = rand() % NB_CELLS;
			int y = rand() % NB_CELLS;
			if (_cells[x][y]._cellType != Cell::SAND &&
				isCellTypeAround(y, x, Cell::SAND))
			{
				_cells[x][y]._cellType = Cell::SAND;
				--nbLands;
			}
			++stop;
		}
	}
}

void					Chunk::generateSand()
{
	for (int i = 0 ; i < NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < NB_CELLS ; ++j)
		{
			if (_cells[i][j]._cellType == Cell::GRASS && isCellTypeAround(j, i, Cell::OCEAN))
			{
				_cells[i][j]._cellType = Cell::SAND;
				generateMoreSand();
			}
		}
	}
}

void					Chunk::draw(sf::RenderWindow *win, int y, int x)
{
	for (int i = 0 ; i < NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < NB_CELLS ; ++j)
		{
			sf::RectangleShape tmp(sf::Vector2f(SIZE_OF_CELL / NB_CELLS,
				SIZE_OF_CELL / NB_CELLS));
			if (_cells[i][j]._cellType == Cell::OCEAN)
				tmp.setFillColor(sf::Color(12, 173, 193));
			else if (_cells[i][j]._cellType == Cell::GRASS)
				tmp.setFillColor(sf::Color(19, 209, 111));
			else
				tmp.setFillColor(sf::Color::Yellow);
			tmp.setPosition((j * (SIZE_OF_CELL / NB_CELLS) + y * Chunk::SIZE_OF_CELL),
				(i * (SIZE_OF_CELL / NB_CELLS)) + x * Chunk::SIZE_OF_CELL);
			win->draw(tmp);
		}
	}
}