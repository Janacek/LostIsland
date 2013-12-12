#include			"Edge.h"

Edge_::Edge_(std::pair<float, float> p1, std::pair<float, float> p2)
{
	this->_pos1 = p1;
	this->_pos2 = p2;
}

Edge_::~Edge_()
{
}

Edge_			Edge_::operator=(Edge_ const &i)
{
	this->_pos1 = i._pos1;
	this->_pos2 = i._pos2;
	return (*this);
}