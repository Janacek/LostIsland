#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "HarmfullAnimal.h"

class Dinosaur : public HarmfullAnimal
{
public:
	Dinosaur(sf::Vector2f &, int, Camera *);
	virtual ~Dinosaur();

	virtual void						loadAnimation(std::string const &, float);
	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	virtual Type getType() const;
};