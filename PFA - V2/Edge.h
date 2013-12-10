#ifndef								EDGE
#define								EDGE

#include							<queue>

class								Polygon;

class								Edge_
{
public:
	Edge_(std::pair<float, float>, std::pair<float, float>);
	Edge_ operator=(Edge_ const &);
	~Edge_();
	std::pair<float, float>			_pos1;
	std::pair<float, float>			_pos2;
	std::pair<Polygon *, Polygon *>	_polygonsOwn;
};

#endif								