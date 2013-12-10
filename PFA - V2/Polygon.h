#pragma once

#include					<deque>
#include					<SFML/Graphics.hpp>
#include					"Coordinates.hpp"
#include					"Edge.h"

class						Polygon
{
public:
	enum					PType
	{
		GROUND = 0,
		WATER,
		UNKNOWN
	};

	enum					PPrecisionType
	{
		OCEAN = 0,
		LAKE,
		GRASS,
		BEACH,
		NONE
	};

public:
	Polygon(std::pair<float, float>);
	~Polygon();
	void					addEdge(Edge_ *);
	void					addEdge(std::pair<float, float>, std::pair<float, float>);
	std::deque<Edge_ *>		&getEdges();
	std::pair<float, float>	const &getCenter();
	void					setPolygonType(PType);
	PType					getPolygonType() const;

	void					setPolygonPrecisionType(PPrecisionType);
	PPrecisionType			getPolygonPrecisionType() const;

private:
	std::deque<Edge_ *>		_edges;
	std::pair<float, float>	_center;

public:
	std::pair<float, float>	_topLeft;
	std::pair<float, float>	_bottomRight;
	sf::Rect<float>			_pos;

	//Polygon type
private:
	PType					_polygonType;
	PPrecisionType			_polygonPrecisionType;
	int						_temperature;
	int						_humidity;
};