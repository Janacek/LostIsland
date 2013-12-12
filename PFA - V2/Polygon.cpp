#include				"Polygon.h"

Polygon::Polygon(std::pair<float, float> pos)
{
	this->_center = pos;
	this->_polygonPrecisionType = Polygon::NONE;
	this->_polygonType = Polygon::UNKNOWN;
}

Polygon::~Polygon()
{
	std::deque<Edge_ *>::iterator it = this->_edges.begin();
	for (; it != this->_edges.end() ; ++it)
		if (*it)
			delete *it;
}

void					Polygon::addEdge(Edge_ *edge)
{
	this->_edges.push_back(edge);
}

void					Polygon::addEdge(std::pair<float, float> p1,
										 std::pair<float, float> p2)
{
	this->_edges.push_back(new Edge_(p1, p2));
}

std::deque<Edge_ *>		&Polygon::getEdges()
{
	return (this->_edges);
}

std::pair<float, float>	const &Polygon::getCenter()
{
	return (this->_center);
}

void Polygon::setPolygonType(Polygon::PType type)
{
	this->_polygonType = type;
}

Polygon::PType Polygon::getPolygonType() const
{
	return (this->_polygonType);
}

void Polygon::setPolygonPrecisionType(Polygon::PPrecisionType type)
{
	this->_polygonPrecisionType = type;
}

Polygon::PPrecisionType Polygon::getPolygonPrecisionType() const
{
	return (this->_polygonPrecisionType);
}