#pragma once

#include "Bunny.h"

class BunnyWhite : public Bunny
{
public:
	BunnyWhite(sf::Vector2f &, int, Camera *);
	~BunnyWhite();
	virtual void loadAnimation(std::string const &, float);
};