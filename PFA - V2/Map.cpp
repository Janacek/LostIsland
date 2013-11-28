#include "Map.h"

Map::Map(std::pair<unsigned int, unsigned int> size, int seed)
	: _size(size), _seed(seed)
{
	this->_sizeOfChunks.first = 512;
	this->_sizeOfChunks.second = 512;
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

void	Map::generateVoronoiPolygons()
{
	int i = 0;


	srand(_seed);
	int number = 50;
	float *nx = new float[number];
	float *ny = new float[number];
	for (; i < number ; ++i)
	{
		nx[i] = rand() % (_size.first);
		ny[i] = rand() % (_size.second);
		_points.push_back(Coordinates(nx[i], ny[i]));
		this->_polygons.push_back(new Polygon(std::pair<float, float>(nx[i], ny[i])));
	}
		

	VoronoiDiagramGenerator vdg;
	vdg.generateVoronoi(nx, ny, number, 0, _size.first, 0, _size.second, 3);

	vdg.resetIterator();
	this->_img.create(this->_size.first, this->_size.second);

	float x1, y1, x2, y2;
	while(vdg.getNext(x1,y1,x2,y2))
	{
		float mX, mY = 0;

		mX = (x1 + x2) / 2;
		mY = (y1 + y2) / 2;

		Polygon			*nearest1 = NULL;
		Polygon			*nearest2 = NULL;
		float n1 = _size.second, n2 = _size.second;
		std::deque<Polygon *>::iterator it = this->_polygons.begin();
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
		nearest1->addEdge(std::pair<float, float>(x1, y1), std::pair<float, float>(x2, y2));
		nearest2->addEdge(std::pair<float, float>(x1, y1), std::pair<float, float>(x2, y2));
	}

	std::deque<Polygon *>::iterator it = this->_polygons.begin();
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
		(*it)->_topLeft = std::pair<float, float>(t, l);
		(*it)->_bottomRight = std::pair<float, float>(b, r);
	}
	std::cout << this->_polygons.size() << std::endl;
}

Map::~Map()
{
	std::deque<Polygon *>::iterator it = this->_polygons.begin();
	for (; it != this->_polygons.end() ; ++it)
		delete *it;
}

void	Map::draw(sf::RenderWindow *win)
{	
	std::deque<Polygon *>::iterator it = this->_polygons.begin();
	for (; it != this->_polygons.end() ; ++it)
	{
		std::deque<Edge_ *> edges = (*it)->getEdges();
		if (edges.size() > 2)
		{
			sf::ConvexShape convex;
			convex.setPointCount(3);
			convex.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));

			int bord = 0;

			while (bord < edges.size())
			{
				std::deque<Edge_ *>::iterator ite = edges.begin();
				for (; ite != edges.end() ; ++ite)
				{
					sf::VertexArray lines(sf::Lines, 2);
					lines[0].position = sf::Vector2f((*ite)->_pos1.first, (*ite)->_pos1.second);
					lines[1].position = sf::Vector2f((*ite)->_pos2.first, (*ite)->_pos2.second);
					this->_img.draw(lines);
					convex.setPoint(0, sf::Vector2f((*it)->getCenter().first, (*it)->getCenter().second));
					convex.setPoint(1, sf::Vector2f((*ite)->_pos1.first, (*ite)->_pos1.second));
					convex.setPoint(2, sf::Vector2f((*ite)->_pos2.first, (*ite)->_pos2.second));
					this->_img.draw(convex);
				}
				++bord;
			}
		}
	}
	this->_img.display();


	sf::Sprite sprite(this->_img.getTexture(), sf::Rect<int>(0, 0, 1200, 800));
	win->draw(sprite);
}

void	Map::update(sf::Event *)
{
}