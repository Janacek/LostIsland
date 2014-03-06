#pragma once

#include "Sheep.h"

class SheepBlack : public Sheep
{
public:
	SheepBlack(sf::Vector2f &, int, Camera *);
	~SheepBlack();
	virtual void loadAnimation(std::string const &, float);
};