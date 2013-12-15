#include					"Chunk.h"

Chunk::Chunk()
{
	this->_texture = NULL;
}

Chunk::~Chunk()
{
}

#include <iostream>

void						Chunk::addPolygon(Polygon_ *polygon)
{
	this->_polygons.push_back(polygon);
}

sf::RenderTexture			*Chunk::getTexture()
{
	if (!this->_texture)
	{
		this->_texture = new sf::RenderTexture();
		this->_texture->create(this->_height, this->_width);

		std::deque<Polygon_ *>::iterator it = this->_polygons.begin();
		sf::ConvexShape convex;
		convex.setPointCount(3);
		for (; it != this->_polygons.end() ; ++it)
		{
			std::deque<Edge_ *> edges = (*it)->getEdges();
			if ((*it)->getPolygonType() == Polygon_::GROUND)
			{
				if ((*it)->getPolygonPrecisionType() == Polygon_::BEACH)
					convex.setFillColor(sf::Color::Yellow);
				else
					convex.setFillColor(sf::Color::Green);
			}
			else
			{
				if ((*it)->getPolygonPrecisionType() == Polygon_::OCEAN)
					convex.setFillColor(sf::Color::Blue);
				else
					convex.setFillColor(sf::Color::Cyan);
			}

			float boundsY = (this->_pos.first * this->_width);
			float boundsX = (this->_pos.second * this->_height);

			std::deque<Edge_ *>::iterator ite = edges.begin();
			for (; ite != edges.end() ; ++ite)
			{
				convex.setPoint(0, sf::Vector2f((*it)->getCenter().first - boundsX, (*it)->getCenter().second - boundsY));
				convex.setPoint(1, sf::Vector2f((*ite)->_pos1.first - boundsX, (*ite)->_pos1.second - boundsY));
				convex.setPoint(2, sf::Vector2f((*ite)->_pos2.first - boundsX, (*ite)->_pos2.second - boundsY));

				this->_texture->draw(convex);
			}
		}
	}


	this->_texture->display();
	return (this->_texture);
}

void						Chunk::unload()
{
	delete this->_texture;
	this->_texture = NULL;
}