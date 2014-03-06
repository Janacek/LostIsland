#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "HarmlessAnimal.h"

class Sheep : public HarmlessAnimal
{
public:
	Sheep(sf::Vector2f &, int, Camera *);
	virtual ~Sheep();

	virtual void						loadAnimation(std::string const &, float);
	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	virtual Type getType() const;
};