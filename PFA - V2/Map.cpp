#include "Map.h"

Map::Map()
{
	_size = sf::Vector2i(16, 16);
	_seed = 0xcafe; // OLOL
	_groundRatio = 33;
	_temperature = NULL;
	_humidity = NULL;

	_typeToColor[Cell::GRASS] = sf::Color::Green;
	_typeToColor[Cell::OCEAN] = sf::Color::Blue;
	_typeToColor[Cell::SAND] = sf::Color::Yellow;
	_typeToColor[Cell::FOREST] = sf::Color(3, 53, 3);
	_typeToColor[Cell::SNOW] = sf::Color::White;
	_typeToColor[Cell::SAVANNA] = sf::Color(253, 178, 1);

	_typeToTexture[Cell::GRASS] = ImageSingleton::getInstance().get(Type::GRASS);
	_typeToTexture[Cell::OCEAN] = ImageSingleton::getInstance().get(Type::LAC);
	_typeToTexture[Cell::SAND] = ImageSingleton::getInstance().get(Type::SABLE);
	_typeToTexture[Cell::FOREST] = ImageSingleton::getInstance().get(Type::FOREST);
	_typeToTexture[Cell::SNOW] = ImageSingleton::getInstance().get(Type::SNOW);
	_typeToTexture[Cell::SAVANNA] = ImageSingleton::getInstance().get(Type::SAVANNA);

	int i;
	for (i = 0 ; i < 22 ; ++i)
		_corTab[i]._cellType = Cell::SAND;
	for ( ; i < 44 ; ++i)
		_corTab[i]._cellType = Cell::FOREST;
	for ( ; i < 55 ; ++i)
		_corTab[i]._cellType = Cell::GRASS;

	for ( ; i < 66 ; ++i)
		_corTab[i]._cellType = Cell::SAVANNA;
	for ( ; i < 100 ; ++i)
		_corTab[i]._cellType = Cell::SNOW;

	hori = 0;
	vert = 0;
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
	_temperature = new PerlinNoise(_seed);
	_humidity = new PerlinNoise(_seed);
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

void						Map::transformChunkToMap()
{
	_cellMap = new Cell*[_size.y * Chunk::NB_CELLS];
	for (int i = 0 ; i < _size.y * Chunk::NB_CELLS ; ++i)
		_cellMap[i] = new Cell[_size.x * Chunk::NB_CELLS];
	for (int i = 0 ; i < _size.y ; ++i)
		for (int j = 0 ; j < _size.x ; ++j)
		{
			Cell **tmp = _map[i][j].getCells();
			for (int x = 0 ; x < Chunk::NB_CELLS ; ++x)
			{
				for (int y = 0 ; y < Chunk::NB_CELLS ; ++y)
				{
					_cellMap[(j * Chunk::NB_CELLS) + y][(i * Chunk::NB_CELLS) + x]._cellType =
						tmp[y][x]._cellType;
				}
			}
		}
}

bool					Map::isCellTypeAround(int x, int y, Cell::Type type)
{
	if (y - 1 >= 0 && _cellMap[y - 1][x]._cellType == type)
		return true;
	else if (y + 1 < Chunk::NB_CELLS * _size.y && _cellMap[y + 1][x]._cellType == type)
		return true;
	else if (x - 1 >= 0 && _cellMap[y][x - 1]._cellType == type)
		return true;
	else if (x + 1 < Chunk::NB_CELLS *_size.x && _cellMap[y][x + 1]._cellType == type)
		return true;
	return (false);
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

	// Transforming the chunk to a map.
	transformChunkToMap();
	generateBiomes();
	generateSand();
	createMiniMap();
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

void						Map::generateBiomes()
{
	for (int i = 0 ; i < _size.y * Chunk::NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < _size.x * Chunk::NB_CELLS ; ++j)
		{
			//std::cout << (int)(_temperature->getElevation(i, j, 75)* 0.5 * 100) << std::endl;
			if (_cellMap[i][j]._cellType != Cell::OCEAN)
				_cellMap[i][j]._cellType = (_corTab[(int)((_temperature->getElevation(i, j, 10)+1)* 0.5 * 100)])._cellType;
		}
	}
}

void						Map::generateSand()
{
	for (int i = 0 ; i < _size.y * Chunk::NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < _size.x * Chunk::NB_CELLS ; ++j)
		{
			if (_cellMap[i][j]._cellType != Cell::OCEAN && isCellTypeAround(j, i, Cell::OCEAN))
				_cellMap[i][j]._cellType = Cell::SAND;
		}
	}

	int nbLands = 400;
	int stop = 0;
	while (nbLands > 0)
	{
		if (stop > Chunk::NB_CELLS * Chunk::NB_CELLS)
			return ;
		int x = rand() % (Chunk::NB_CELLS * _size.y);
		int y = rand() % (Chunk::NB_CELLS * _size.x);
		if (_cellMap[x][y]._cellType != Cell::OCEAN &&
			isCellTypeAround(y, x, Cell::SAND))
		{
			_cellMap[x][y]._cellType = Cell::SAND;
			--nbLands;
		}
		//++stop;
	}
}

void						Map::createMiniMap()
{
	_miniMapT = new sf::RenderTexture();
	_miniMapT->create((_size.x * Chunk::NB_CELLS) * 2,
		(_size.y * Chunk::NB_CELLS) * 2);

	for (int i = 0 ; i < _size.y * Chunk::NB_CELLS ; ++i)
	{
		for (int j = 0 ; j < _size.x * Chunk::NB_CELLS ; ++j)
		{
			sf::RectangleShape tmp(sf::Vector2f(2, 2));
			tmp.setFillColor(_typeToColor[_cellMap[i][j]._cellType]);
			tmp.setPosition(j * 2, i * 2);
			_miniMapT->draw(tmp);
		}
	}
	_miniMapT->display();
}

void						Map::drawMiniMap(sf::RenderWindow *win)
{
	sf::Sprite sprite(_miniMapT->getTexture());
	win->draw(sprite);

	{
		sf::RectangleShape tmp(sf::Vector2f(
			(Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL) * 2,
			(Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) * 2));
		tmp.setFillColor(sf::Color::Transparent);
		tmp.setOutlineThickness(2);
		tmp.setOutlineColor(sf::Color::Black);
		tmp.setPosition(hori * 2, vert * 2);
		win->draw(tmp);
	}

	sf::RectangleShape tmp(sf::Vector2f(
		(_size.x * Chunk::NB_CELLS) * 2,
		(_size.y * Chunk::NB_CELLS) * 2));
	tmp.setFillColor(sf::Color::Transparent);
	tmp.setOutlineThickness(2);
	tmp.setOutlineColor(sf::Color::Black);
	tmp.setPosition(0, 0);
	win->draw(tmp);
}

void						Map::draw(sf::RenderWindow *win)
{
	if (Singleton::getInstance().isMovingRight)
		if (hori + Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL 
			< _size.x * Chunk::NB_CELLS)
			++hori;
	if (Singleton::getInstance().isMovingLeft)
		if (hori - 1 >= 0)
			--hori;

	if (Singleton::getInstance().isMovingUp)
		if (vert - 1 >= 0)
			--vert;
	if (Singleton::getInstance().isMovingDown)
		if (vert + Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL 
			< _size.y * Chunk::NB_CELLS)
			++vert;

	for (int i = vert ; i < Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL + vert ; ++i)
	{
		for (int j = hori ; j < Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + hori ; ++j)
		{
			sf::RectangleShape tmp(sf::Vector2f(Chunk::SIZE_OF_CELL,
				Chunk::SIZE_OF_CELL));
			//if (_cellMap[i][j]._cellType == Cell::OCEAN)
			//	tmp.setTexture(ImageSingleton::getInstance().get(Type::LAC));
			//else if (_cellMap[i][j]._cellType == Cell::GRASS)
			//	tmp.setFillColor(sf::Color(19, 209, 111));
			//else
			//{
			////	tmp.setFillColor(sf::Color::Yellow);
			//	tmp.setTexture(ImageSingleton::getInstance().get(Type::SABLE));
			//}
			//tmp.setFillColor(_typeToColor[_cellMap[i][j]._cellType]);
			tmp.setTexture(_typeToTexture[_cellMap[i][j]._cellType]);
			tmp.setPosition((j -hori) * Chunk::SIZE_OF_CELL,
				(i -vert) * Chunk::SIZE_OF_CELL);
			win->draw(tmp);
		}
	}
}

void						Map::update()
{
}