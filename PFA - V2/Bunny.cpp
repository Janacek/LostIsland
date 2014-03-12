#include "Bunny.h"
#include "ImageManager.h"
#include "Map.h"
#include "Chunk.h"
#include "MapEnvironment.h"
#include "Player.h"
#include "Meat.h"
#include "ShadersManager.h"

std::string &Bunny::serialize() const
{
	std::string toto;
	return (toto);
}

void Bunny::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

Bunny::Bunny(sf::Vector2f &position, int life, Camera *cam)
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

Bunny::~Bunny()
{

}

void Bunny::loadAnimation(std::string const &string_anim, float)
{


}

Type Bunny::getType() const
{
	return BUNNY;
}