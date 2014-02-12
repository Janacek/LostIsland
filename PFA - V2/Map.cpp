
#include "Map.h"

Map::Map(Camera *cam, std::string &loading)
: _loading(loading)
{
	_camera = cam;
	_size = sf::Vector2i(16, 16);
	_seed = 0xcafe; // Outdated
	
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
	_typeToTexture[Cell::WALKABLE_WATER] = ImageSingleton::getInstance().get(Type::WATER_WALKABLE);

	int i;
	for (i = 0; i < 27; ++i)
		_corTab[i]._cellType = Cell::SNOW;
	for (; i < 44; ++i)
		_corTab[i]._cellType = Cell::SAVANNA;
	for (; i < 55; ++i)
		_corTab[i]._cellType = Cell::GRASS;

	for (; i < 66; ++i)
		_corTab[i]._cellType = Cell::FOREST;
	for (; i < 100; ++i)
		_corTab[i]._cellType = Cell::SAND;

	// SNOW SAVANNA GRASS FOREST SAND

	_mapTexture = NULL;

	_spawnPoints.clear();
}

Map::~Map()
{
	if (_map)
	{
		for (int i = 0; i < _size.x; ++i)
			delete[] _map[i];
		delete _map;
		_map = NULL;
	}

	if (_cellMap)
	{
		for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
			delete[] _cellMap[i];
		delete _cellMap;
		_cellMap = NULL;
	}

	if (_entitiesMap)
	{
		for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
			delete[] _entitiesMap[i];
		delete _entitiesMap;
		_entitiesMap = NULL;
	}

	if (_temperature)
	{
		delete _temperature;
		_temperature = NULL;
	}

	if (_humidity)
	{
		delete _humidity;
		_humidity = NULL;
	}

	if (_miniMapT)
	{
		delete _miniMapT;
		_miniMapT = NULL;
	}

	if (_mapText)
	{
		delete _mapText;
		_mapText = NULL;
	}

}

static unsigned int generateHash(std::string const & string)
{
	unsigned int hash = 0;
	for (size_t i = 0; i < string.length(); ++i)
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

	if (_mapTexture)
		delete _mapTexture;
	_mapTexture = new sf::RenderTexture;
	_mapTexture->create(1920, 1080);
}

void						Map::generateCenterIsland(int ratio)
{
	int startX = (int)(ceil(((float)_size.x * (float)ratio) / (float)100));
	int startY = (int)(ceil(((float)_size.y * (float)ratio) / (float)100));

	int stopX = (int)(startX + (((float)_size.x * (float)_groundRatio) / (float)100));
	int stopY = (int)(startY + (((float)_size.x * (float)_groundRatio) / (float)100));

	for (int i = startY; i <= stopY; ++i)
	for (int j = startX; j <= stopX; ++j)
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
	for (int i = startX; i <= stopX; ++i)
		probabilities(startY, i);
	else if (stopX < startX)
	for (int i = stopX; i <= startX; ++i)
		probabilities(startY, i);
}

void						Map::generateVerticalGrass(int startX,
	int startY,
	int stopX,
	int stopY)
{
	if (startY < stopY)
	for (int i = startY; i <= stopY; ++i)
		probabilities(i, startX);
	else if (stopY < startY)
	for (int i = stopY; i <= startY; ++i)
		probabilities(i, startX);
}

void						Map::generateExtendedIsland(int ratio)
{
	int startX = (int)(ceil(((float)_size.x * (float)ratio) / (float)100));
	int startY = (int)(ceil(((float)_size.y * (float)ratio) / (float)100));

	int stopX = (int)(startX + (((float)_size.x * (float)_groundRatio) / (float)100));
	int stopY = (int)(startY + (((float)_size.x * (float)_groundRatio) / (float)100));

	for (int i = 1; i <= 3; ++i)
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
	for (int i = y - 1; i <= y + 1; ++i)
	{
		for (int j = x - 1; j <= x + 1; ++j)
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
	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
		_cellMap[i] = new Cell[_size.x * Chunk::NB_CELLS];
	for (int i = 0; i < _size.y; ++i)
	for (int j = 0; j < _size.x; ++j)
	{
		Cell **tmp = _map[i][j].getCells();
		for (int x = 0; x < Chunk::NB_CELLS; ++x)
		{
			for (int y = 0; y < Chunk::NB_CELLS; ++y)
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
	for (int i = 0; i < _size.x; ++i)
		_map[i] = new Chunk[_size.y];

	int ratio;
	ratio = (100 - _groundRatio) / 2;

	_loading = "Generating the main island";
	generateCenterIsland(ratio);
	_loading = "Adding some more lands";
	generateExtendedIsland(ratio);
	_loading = "Adding some magic";
	divideLands();
	mergeLands();
	_loading = "Too much water, should dry some";
	dryUselessWater();
	_loading = "Adding some details";
	addDetails();

	// Transforming the chunk to a map.
	transformChunkToMap();
	_loading = "Generating cool biomes";
	generateBiomes();
	_loading = "Adding beaches, bitches love beaches";
	generateSand();

	_loading = "Art thou Jesus Christ ?!";
	generateWalkableWater();

	_loading = "Growing trees";
	generateTrees();

	_loading = "Adding a mini map";
	createMiniMap();
}

void						Map::divideLands()
{
	for (int i = 0; i < _size.y; ++i)
	{
		for (int j = 0; j < _size.x; ++j)
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
	for (int i = 0; i < _size.y; ++i)
	{
		for (int j = 0; j < _size.x; ++j)
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
	for (int i = 0; i < _size.y; ++i)
	{
		for (int j = 0; j < _size.x; ++j)
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
	for (int i = 0; i < _size.y; ++i)
	{
		for (int j = 0; j < _size.x; ++j)
		{
			_map[i][j].addDetails();
		}
	}
}

void						Map::generateBiomes()
{
	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
	{
		for (int j = 0; j < _size.x * Chunk::NB_CELLS; ++j)
		{
			//std::cout << (int)(_temperature->getElevation(i, j, 75)* 0.5 * 100) << std::endl;
			if (_cellMap[i][j]._cellType != Cell::OCEAN)
				_cellMap[i][j]._cellType = (_corTab[(int)((_temperature->getElevation(static_cast<float>(i), static_cast<float>(j), static_cast<float>(10)) + 1)* 0.5 * 100)])._cellType;
		}
	}
}

void						Map::changeWaterToWalkableWater(int x, int y)
{
	sf::Vector2f			start(x - NBR_WALKABLE_WATER, y - NBR_WALKABLE_WATER);

	for (int i = start.x; i < x + NBR_WALKABLE_WATER; ++i)
	{
		for (int j = start.y; j < y + NBR_WALKABLE_WATER; ++j)
		{
			if (_cellMap[i][j]._cellType == Cell::OCEAN)
			{
				_cellMap[i][j]._cellType = Cell::WALKABLE_WATER;
			}
		}
	}
}

void						Map::generateWalkableWater()
{
	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
	{
		for (int j = 0; j < _size.x * Chunk::NB_CELLS; ++j)
		{
			if (_cellMap[i][j]._cellType == Cell::SAND &&
				isCellTypeAround(j, i, Cell::OCEAN))
			{
				changeWaterToWalkableWater(i, j);
			}
		}
	}
}

void						Map::generateSand()
{
	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
	{
		for (int j = 0; j < _size.x * Chunk::NB_CELLS; ++j)
		{
			if (_cellMap[i][j]._cellType != Cell::OCEAN && isCellTypeAround(j, i, Cell::OCEAN))
			{
				_spawnPoints.push_back(sf::Vector2f(j, i));
				_cellMap[i][j]._cellType = Cell::SAND;
			}
		}
	}

	int nbLands = 400;
	int stop = 0;
	while (nbLands > 0)
	{
		if (stop > Chunk::NB_CELLS * Chunk::NB_CELLS)
			return;
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
	sf::Vector2f			rapport((_size.x * Chunk::NB_CELLS) / _sizeOfMiniMap,
									(_size.y * Chunk::NB_CELLS) / _sizeOfMiniMap);

	_miniMapT = new sf::RenderTexture();
	_miniMapT->create((_size.x * Chunk::NB_CELLS) * rapport.x,
		(_size.y * Chunk::NB_CELLS) * rapport.y);

	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
	{
		for (int j = 0; j < _size.x * Chunk::NB_CELLS; ++j)
		{
			sf::RectangleShape tmp(sf::Vector2f(rapport.x, rapport.y));
			tmp.setTexture(_typeToTexture[_cellMap[i][j]._cellType]);
			tmp.setPosition(static_cast<float>(j * rapport.y), static_cast<float>(i * rapport.x));
			_miniMapT->draw(tmp);
		}
	}
	_miniMapT->display();
}

void						Map::drawMiniMap(sf::RenderWindow *win)
{
	sf::Vector2f			rapport((_size.x * Chunk::NB_CELLS) / _sizeOfMiniMap,
		(_size.y * Chunk::NB_CELLS) / _sizeOfMiniMap);

	if (_miniMapT)
	{
		sf::Sprite sprite(_miniMapT->getTexture());
		win->draw(sprite);
	}

	{
		sf::RectangleShape tmp(sf::Vector2f(
			static_cast<float>(Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL) * rapport.x,
			static_cast<float>(Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL) * rapport.y));
		tmp.setFillColor(sf::Color::Transparent);
		tmp.setOutlineThickness(2);
		tmp.setOutlineColor(sf::Color::Black);
		tmp.setPosition(_camera->_position.x * rapport.x, _camera->_position.y * rapport.y);
		win->draw(tmp);
	}

	sf::RectangleShape tmp(sf::Vector2f(
		static_cast<float>(_size.x * Chunk::NB_CELLS) * rapport.x,
		static_cast<float>(_size.y * Chunk::NB_CELLS) * rapport.y));
	tmp.setFillColor(sf::Color::Transparent);
	tmp.setOutlineThickness(2);
	tmp.setOutlineColor(sf::Color::Black);
	tmp.setPosition(0, 0);
	win->draw(tmp);
}

sf::Vector2f				&Map::getCamPos()
{
	_camPos.x = _camera->_position.x;
	_camPos.y = _camera->_position.y;
	return _camPos;
}

void						Map::draw(sf::RenderWindow *win)
{
	if (!_cellMap || !_entitiesMap)
		return;
	for (int i = static_cast<int>(_camera->_position.y); i < static_cast<int>((Singleton::getInstance()._window->getSize().y / Chunk::SIZE_OF_CELL + 2 + _camera->_position.y)); ++i)
	{
		for (int j = static_cast<int>(_camera->_position.x); j < Singleton::getInstance()._window->getSize().x / Chunk::SIZE_OF_CELL + 1 + _camera->_position.x; ++j)
		{
			sf::RectangleShape tmp(sf::Vector2f(static_cast<float>(Chunk::SIZE_OF_CELL),
				static_cast<float>(Chunk::SIZE_OF_CELL)));
			tmp.setTexture(_typeToTexture[_cellMap[i][j]._cellType]);
			tmp.setPosition((j - _camera->_position.x) * Chunk::SIZE_OF_CELL,
				(i - _camera->_position.y) * Chunk::SIZE_OF_CELL);
			_mapTexture->draw(tmp);
			//Singleton::getInstance()._window->draw(tmp);

			sf::Vector2f savePos;
			if (_entitiesMap[i][j]._component != NULL && _entitiesMap[i][j]._component->getType() != PLAYER)
			{
				savePos = _entitiesMap[i][j]._component->getPosition();
				_entitiesMap[i][j]._component->setPosition(sf::Vector2f((j - _camera->_position.x) * Chunk::SIZE_OF_CELL
					, (i - _camera->_position.y) * Chunk::SIZE_OF_CELL - 20));
				_entitiesMap[i][j]._component->draw(_mapTexture);
				_entitiesMap[i][j]._component->setPosition(savePos);
			}
		}
	}
	_mapTexture->display();
	Singleton::getInstance()._window->draw(sf::Sprite(_mapTexture->getTexture()));
}

void						Map::generateTrees()
{

	_entitiesMap = new MapEnvironment*[_size.y * Chunk::NB_CELLS];
	for (int i = 0; i < _size.y * Chunk::NB_CELLS; ++i)
		_entitiesMap[i] = new MapEnvironment[_size.x * Chunk::NB_CELLS]();

	for (int i = 0; i < 500;)
	{
		int x = rand() % (_size.x * Chunk::NB_CELLS);
		int y = rand() % (_size.y  * Chunk::NB_CELLS);
		if (_cellMap[x][y]._cellType == Cell::FOREST &&
			_entitiesMap[x][y]._component == NULL)
		{
			/*	Tree *tmp;
				tmp = new Tree();
				tmp->setPosition(sf::Vector2f(x, y));*/

			_entitiesMap[x][y]._component = new ForestTree();
			_entitiesMap[x][y]._component->setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

			++i;
		}
	}


	for (int i = 0; i < 50;)
	{
		int x = rand() % (_size.x * Chunk::NB_CELLS);
		int y = rand() % (_size.y  * Chunk::NB_CELLS);
		if (_cellMap[x][y]._cellType == Cell::GRASS &&
			_entitiesMap[x][y]._component == NULL)
		{
			Bush *tmp;
			tmp = new Bush();
			tmp->setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

			_entitiesMap[x][y]._component = tmp;


			++i;
		}
	}


	for (int i = 0; i < 50;)
	{
		int x = rand() % (_size.x * Chunk::NB_CELLS);
		int y = rand() % (_size.y  * Chunk::NB_CELLS);
		if (_cellMap[x][y]._cellType == Cell::SAND &&
			_entitiesMap[x][y]._component == NULL)
		{
			PalmTree *tmp;
			tmp = new PalmTree();
			tmp->setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

			_entitiesMap[x][y]._component = tmp;

			++i;
		}
	}
}

Chunk						**Map::getMap() const
{
	return _map;
}

Cell						**Map::getCellMap() const
{
	return _cellMap;
}

MapEnvironment			**Map::getEntitiesMap() const
{
	return _entitiesMap;
}

void					Map::setEntityMap(IEntity *ent, int x, int y)
{
	_entitiesMap[x][y]._component = ent;
}
sf::Vector2i				Map::getSize() const
{
	return this->_size;
}

void						Map::update()
{
	_camera->moveCamera(_size);
}