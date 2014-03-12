#pragma once

#include "Sheep.h"

class SheepWhite : public Sheep
{
public:
	SheepWhite(sf::Vector2f &, int, Camera *);
	~SheepWhite();
	virtual void loadAnimation(std::string const &, float);
};