#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "HarmlessAnimal.h"

class Bunny : public HarmlessAnimal
{
public:
	Bunny(sf::Vector2f &, int, Camera *);
	virtual ~Bunny();

	virtual void						loadAnimation(std::string const &, float);
	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	virtual Type getType() const;
};