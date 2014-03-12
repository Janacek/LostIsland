#pragma once

#include "Dinosaur.h"

class Velociraptor : public Dinosaur
{
public:
	Velociraptor(sf::Vector2f &, int, Camera *);
	~Velociraptor();
	virtual void loadAnimation(std::string const &, float);
};