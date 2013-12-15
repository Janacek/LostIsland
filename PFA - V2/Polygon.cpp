#include				"Polygon.h"

Polygon_::Polygon_(std::pair<float, float> pos)
{
	this->_center = pos;
	this->_polygonPrecisionType = Polygon_::NONE;
	this->_polygonType = Polygon_::UNKNOWN;
}

Polygon_::~Polygon_()
{
	std::deque<Edge_ *>::iterator it = this->_edges.begin();
	for (; it != this->_edges.end() ; ++it)
		if (*it)
			delete *it;
}

void					Polygon_::addEdge(Edge_ *edge)
{
	this->_edges.push_back(edge);
}

void					Polygon_::addEdge(std::pair<float, float> p1,
										 std::pair<float, float> p2)
{
	this->_edges.push_back(new Edge_(p1, p2));
}

std::deque<Edge_ *>		&Polygon_::getEdges()
{
	return (this->_edges);
}

std::pair<float, float>	const &Polygon_::getCenter()
{
	return (this->_center);
}

void Polygon_::setPolygonType(Polygon_::PType type)
{
	this->_polygonType = type;
}

Polygon_::PType Polygon_::getPolygonType() const
{
	return (this->_polygonType);
}

void Polygon_::setPolygonPrecisionType(Polygon_::PPrecisionType type)
{
	this->_polygonPrecisionType = type;
}

Polygon_::PPrecisionType Polygon_::getPolygonPrecisionType() const
{
	return (this->_polygonPrecisionType);
}