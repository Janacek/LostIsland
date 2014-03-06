#pragma once

#include "Bunny.h"

class BunnyBlack : public Bunny
{
public:
	BunnyBlack(sf::Vector2f &, int, Camera *);
	~BunnyBlack();
	virtual void loadAnimation(std::string const &, float);
};