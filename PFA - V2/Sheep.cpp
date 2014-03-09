#include "Sheep.h"
#include "ImageManager.h"
#include "Map.h"
#include "Chunk.h"
#include "MapEnvironment.h"
#include "Player.h"
#include "Meat.h"
#include "ShadersManager.h"
#include "Fur.h"

std::string &Sheep::serialize() const
{
	std::string toto;
	return (toto);
}

void Sheep::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

Sheep::Sheep(sf::Vector2f &position, int life, Camera *cam)
: HarmlessAnimal(position, life, cam)
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

Sheep::~Sheep()
{

}

void Sheep::loadAnimation(std::string const &string_anim, float)
{


}

Type Sheep::getType() const
{
	return SHEEP;
}