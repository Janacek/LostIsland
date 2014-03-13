#include "Dinosaur.h"
#include "ImageManager.h"
#include "Map.h"
#include "Chunk.h"
#include "MapEnvironment.h"
#include "Player.h"
#include "Meat.h"
#include "ShadersManager.h"
#include "Fur.h"

std::string &Dinosaur::serialize() const
{
	std::string toto;
	return (toto);
}

void Dinosaur::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

Dinosaur::Dinosaur(sf::Vector2f &position, int life, Camera *cam)
: HarmfullAnimal(position, life, cam)
{
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(_position);
	_speed = 2;
	_oldTime = 0;
	_iterPath = 0;
	_hasAPath = false;
	_firstPath = true;
	_isSelected = true;
}

Dinosaur::~Dinosaur()
{

}

void Dinosaur::loadAnimation(std::string const &string_anim, float)
{


}

Type Dinosaur::getType() const
{
	return BUNNY;
}