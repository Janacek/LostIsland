#include "Map.h"

Map::Map(std::pair<unsigned int, unsigned int> size, int seed)
	: _size(size), _seed(seed)
{
	this->_drawableChunks.clear();
	this->_sizeOfChunks.first = 512;
	this->_sizeOfChunks.second = 512;
	this->_perlinNoise = new PerlinNoise(seed);
	generateVoronoiPolygons();

}

std::pair<unsigned int, unsigned int> Map::getSize()
{
	return (this->_size);
}

void	Map::setSize(std::pair<unsigned int, unsigned int> size)
{
	this->_size = size;
}

Chunk	**Map::getChunks()
{
	return (this->_chunks);
}

void	Map::generateVoronoiPolygons()
{
	int i = 0;


	srand(_seed);
	int number = 1000;
	float *nx = new float[number];
	float *ny = new float[number];
	for (; i < number ; ++i)
	{
		nx[i] = rand() % (_size.first);
		ny[i] = rand() % (_size.second);
		_points.push_back(Coordinates(nx[i], ny[i]));
		this->_polygons.push_back(new Polygon_(std::pair<float, float>(nx[i], ny[i])));
	}
	VoronoiDiagramGenerator vdg;
	vdg.generateVoronoi(nx, ny, number, 0, _size.first, 0, _size.second, 3);
	vdg.resetIterator();
	float x1, y1, x2, y2;
	while(vdg.getNext(x1,y1,x2,y2))
	{
		float mX, mY = 0;

		mX = (x1 + x2) / 2;
		mY = (y1 + y2) / 2;

		Polygon_			*nearest1 = NULL;
		Polygon_			*nearest2 = NULL;
		float n1 = _size.second, n2 = _size.second;
		std::deque<Polygon_ *>::iterator it = this->_polygons.begin();
		for (; it != this->_polygons.end() ; ++it)
		{
			float norme = sqrt(((mX - (*it)->getCenter().first) * (mX - (*it)->getCenter().first)) +
				((mY - (*it)->getCenter().second) * (mY - (*it)->getCenter().second)));
			if (norme < n1)
			{
				n2 = n1;
				nearest2 = nearest1;
				n1 = norme;
				nearest1 = (*it);
			}
			else if (norme < n2)
			{
				n2 = norme;
				nearest2 = (*it);
			}
		}
		Edge_ *edge = new Edge_(std::pair<float, float>(x1, y1), std::pair<float, float>(x2, y2));

		nearest1->addEdge(edge);
		nearest2->addEdge(edge);
		edge->_polygonsOwn.first = nearest1;
		edge->_polygonsOwn.second = nearest2;
	}


	std::deque<Polygon_ *>::iterator it = this->_polygons.begin();
	std::deque<Edge_ *>::iterator edges;
	for (; it != this->_polygons.end() ; ++it)
	{
		float b = _size.second;
		float t = 0;
		float r = _size.second;
		float l = 0;
		for (edges = (*it)->getEdges().begin() ; edges != (*it)->getEdges().end() ; ++edges)
		{
			if (t < (*edges)->_pos1.second)
				t = (*edges)->_pos1.second;
			if (t < (*edges)->_pos2.second)
				t = (*edges)->_pos2.second;
			if (b > (*edges)->_pos1.second)
				b = (*edges)->_pos1.second;
			if (b > (*edges)->_pos2.second)
				b = (*edges)->_pos2.second;

			if (l < (*edges)->_pos1.first)
				l = (*edges)->_pos1.first;
			if (l < (*edges)->_pos2.first)
				l = (*edges)->_pos2.first;
			if (r > (*edges)->_pos1.first)
				r = (*edges)->_pos1.first;
			if (r > (*edges)->_pos2.first)
				r = (*edges)->_pos2.first;
		}

		(*it)->_pos.left = r;
		(*it)->_pos.top = b;
		(*it)->_pos.width = (l - r);
		(*it)->_pos.height = (t - b);

		if (b <= 0)
		{
			Edge_ *tmp = new Edge_(std::pair<int, int>(r, b), std::pair<int, int>(r + (l - r), b));
			(*it)->addEdge(tmp);
		}
		if (b + (t - b) == this->_size.second)
		{
			Edge_ *tmp = new Edge_(std::pair<int, int>(r, (b + (t - b))), std::pair<int, int>(r + (l - r), b + (t - b)));
			(*it)->addEdge(tmp);
		}

		if (r == 0)
		{
			Edge_ *tmp = new Edge_(std::pair<int, int>(r, b), std::pair<int, int>(r, b + (t - b)));
			(*it)->addEdge(tmp);
		}
		if (r + (l - r) == this->_size.first)
		{
			Edge_ *tmp = new Edge_(std::pair<int, int>(r + (l - r), b), std::pair<int, int>(r + (l - r), b + (t - b)));
			(*it)->addEdge(tmp);
		}

		if (this->_perlinNoise->getElevation((*it)->getCenter().first, (*it)->getCenter().second, 350) > -50 &&
			this->_perlinNoise->getElevation((*it)->getCenter().first, (*it)->getCenter().second, 350) < 30)
			(*it)->setPolygonType(Polygon_::GROUND);
		else
			(*it)->setPolygonType(Polygon_::WATER);
	}	

	int nb_chunksX = ceil((float)this->_size.first / (float)Chunk::_width);
	int nb_chunksY = ceil((float)this->_size.second / (float)Chunk::_height);
	this->_chunks = new Chunk*[nb_chunksY];
	for (int c = 0 ; c < nb_chunksY ; ++c)
		this->_chunks[c] = new Chunk[nb_chunksX];
	it = this->_polygons.begin();

	for (; it != this->_polygons.end() ; ++it)
	{
		int posX = (float)(*it)->_pos.top / (float)Chunk::_width;
		int posY = (float)(*it)->_pos.left / (float)Chunk::_height;

		/*	this->_chunks[posX][posY]._polygons.push_back((*it));
		this->_chunks[posX][posY]._pos = std::pair<int, int>(posX, posY);*/

		for (int i = 0 ; i < 10 ; ++i)
		{
			for (int j = 0 ; j < 10 ; ++j)
			{
				if (posX + i < nb_chunksY && posY + j < nb_chunksX)
				{
					this->_chunks[posX + i][posY + j].addPolygon(*it);
					this->_chunks[posX + i][posY + j]._pos = std::pair<int, int>(posX + i, posY + j);
				}
			}
		}
	}

	//PUTTING THE MAP EDGES OCEAN TYPE
	for (int i = 0 ; i < nb_chunksY ; ++i)
	{
		it = this->_chunks[i][0]._polygons.begin();
		for (; it != this->_chunks[i][0]._polygons.end() ; ++it)
			if ((*it)->_pos.left < 50)
			{
				(*it)->setPolygonType(Polygon_::WATER);
				(*it)->setPolygonPrecisionType(Polygon_::OCEAN);
			}
	}

	for (int i = 0 ; i < nb_chunksY ; ++i)
	{
		it = this->_chunks[i][nb_chunksX - 1]._polygons.begin();
		for (; it != this->_chunks[i][nb_chunksX - 1]._polygons.end() ; ++it)
			if ((*it)->_pos.left + (*it)->_pos.width > this->_size.first - 50)
			{
				(*it)->setPolygonType(Polygon_::WATER);
				(*it)->setPolygonPrecisionType(Polygon_::OCEAN);
			}
	}

	for (int i = 0 ; i < nb_chunksX ; ++i)
	{
		it = this->_chunks[0][i]._polygons.begin();
		for (; it != this->_chunks[0][i]._polygons.end() ; ++it)
			if ((*it)->_pos.top < 50)
			{
				(*it)->setPolygonType(Polygon_::WATER);
				(*it)->setPolygonPrecisionType(Polygon_::OCEAN);
			}
	}

	for (int i = 0 ; i < nb_chunksX ; ++i)
	{
		it = this->_chunks[nb_chunksY - 1][i]._polygons.begin();
		for (; it != this->_chunks[nb_chunksY - 1][i]._polygons.end() ; ++it)
			if ((*it)->_pos.top + (*it)->_pos.height > this->_size.second - 50)
			{
				(*it)->setPolygonType(Polygon_::WATER);
				(*it)->setPolygonPrecisionType(Polygon_::OCEAN);
			}
	}

	int looooooop = 0;
	while (looooooop < 6)
	{
		it = this->_polygons.begin();
		for (; it != this->_polygons.end() ; ++it)
		{
			if ((*it)->getPolygonType() == Polygon_::WATER && (*it)->getPolygonPrecisionType() == Polygon_::NONE)
			{
				edges = (*it)->getEdges().begin();
				for (; edges != (*it)->getEdges().end() ; ++edges)
				{
					if ((*edges)->_polygonsOwn.first && (*edges)->_polygonsOwn.second)
						if ((*edges)->_polygonsOwn.first->getPolygonPrecisionType() == Polygon_::OCEAN ||
							(*edges)->_polygonsOwn.second->getPolygonPrecisionType() == Polygon_::OCEAN)
						{
							(*it)->setPolygonPrecisionType(Polygon_::OCEAN);
						}
				}
			}
		}
		++looooooop;
	}

	it = this->_polygons.begin();
	for (; it != this->_polygons.end() ; ++it)
	{
		if ((*it)->getPolygonType() == Polygon_::WATER && (*it)->getPolygonPrecisionType() == Polygon_::NONE)
			(*it)->setPolygonPrecisionType(Polygon_::LAKE);
	}

	it = this->_polygons.begin();
	for (; it != this->_polygons.end() ; ++it)
	{
		if ((*it)->getPolygonType() == Polygon_::GROUND && (*it)->getPolygonPrecisionType() == Polygon_::NONE)
		{
			edges = (*it)->getEdges().begin();
			for (; edges != (*it)->getEdges().end() ; ++edges)
			{
				if ((*edges)->_polygonsOwn.first && (*edges)->_polygonsOwn.second)
					if ((*edges)->_polygonsOwn.first->getPolygonPrecisionType() == Polygon_::OCEAN ||
						(*edges)->_polygonsOwn.second->getPolygonPrecisionType() == Polygon_::OCEAN)
						(*it)->setPolygonPrecisionType(Polygon_::BEACH);
			}
		}
	}
}

Map::~Map()
{
	std::deque<Polygon_ *>::iterator it = this->_polygons.begin();
	for (; it != this->_polygons.end() ; ++it)
		delete *it;
}

void	Map::draw(sf::RenderWindow *win)
{
	int nb_chunksX = ceil((float)this->_size.first / (float)Chunk::_width);
	int nb_chunksY = ceil((float)this->_size.second / (float)Chunk::_height);

	static int x = 0;
	static int y = 0;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		x += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		x -= 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		y -= 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		y += 10;
	}

	int posX = x / Chunk::_width;
	int posY = y / Chunk::_height;

	int posXX = x - posX * 512;
	int posYY = y - posY * 512;


	int nbChunksToDrawX = ceil((float)win->getSize().x / (float)Chunk::_width) + 1;
	int nbChunksToDrawY = ceil((float)win->getSize().y / (float)Chunk::_height) + 1;

	std::list<std::pair<Chunk *, std::pair<sf::Vector2f, bool>>>::iterator it = _drawableChunks.begin();
	for ( ; it != _drawableChunks.end() ; ++it)
		(*it).second.second = false;

	for (int i = posY ; i < nbChunksToDrawY + posY; ++i)
	{
		for (int j = posX ; j < nbChunksToDrawX + posX; ++j)
		{
			if (j < nb_chunksX && i < nb_chunksY)
			{
				sf::RenderTexture *tmp = this->_chunks[i][j].getGeneratedTexture();
				if (true)
				//if (tmp && this->_chunks[i][j]._generated && !this->_chunks[i][j]._generating)
				{
					sf::Sprite sprite(this->_chunks[i][j].getTexture()->getTexture(), sf::Rect<int>(0, 0, 512, 512));
					sprite.setPosition((j * 512) - x, (i * 512) - y);


					bool push = true;
					it = _drawableChunks.begin();
					for ( ; it != _drawableChunks.end() ; ++it)
						if ((*it).first == &(this->_chunks[i][j]))
						{
							push = false;
							(*it).second.second = true;
						}

						if (push)
							_drawableChunks.push_back(std::pair<Chunk *, std::pair<sf::Vector2f, bool>>(&(this->_chunks[i][j]),
							std::pair<sf::Vector2f, bool>(sf::Vector2f((j * 512) - x, (i * 512) - y), true)));

						win->draw(sprite);

						//sf::RectangleShape tmp(sf::Vector2f(512, 512));
						//tmp.setFillColor(sf::Color::Transparent);
						//tmp.setOutlineColor(sf::Color::Red);
						//tmp.setPosition((j * 512) - x, (i * 512) - y);
						//win->draw(sprite);
				}
			}
		}
	}

	it = _drawableChunks.begin();
	for ( ; it != _drawableChunks.end() ; ++it)
		if ((*it).second.second == false)
		{
			(*it).first->unload();
			_drawableChunks.erase(it);
			it = _drawableChunks.begin();
		}
}

void	Map::update()
{
	int nb_chunksX = ceil((float)this->_size.first / (float)Chunk::_width);
	int nb_chunksY = ceil((float)this->_size.second / (float)Chunk::_height);

	static int x = 0;
	static int y = 0;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		x += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		x -= 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		y -= 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		y += 10;
	}

	int posX = x / Chunk::_width;
	int posY = y / Chunk::_height;

	int posXX = x - posX * 512;
	int posYY = y - posY * 512;


	int nbChunksToDrawX = ceil((float)Singleton::getInstance()._window->getSize().x / (float)Chunk::_width) + 1;
	int nbChunksToDrawY = ceil((float)Singleton::getInstance()._window->getSize().y / (float)Chunk::_height) + 1;

	for (int i = posY ; i < nbChunksToDrawY + posY; ++i)
	{
		for (int j = posX ; j < nbChunksToDrawX + posX; ++j)
		{
			if (j < nb_chunksX && i < nb_chunksY)
			{
				this->_chunks[i][j].getTexture();
			}
		}
	}
}