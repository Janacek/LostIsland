#include "Grass.h"
#include "Player.h"

std::string &Grass::serialize() const
{
	std::string toto;
	return (toto);
}

void Grass::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Grass::Grass(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Grass::doAction(AEntity* other)
{
}

void Grass::getAction(AEntity* other)
{

}

void Grass::loadAnimation(std::string const & string_anim, float speed)
{

}
void Grass::update(Map &map)
{

}

void Grass::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Grass::draw(sf::RenderTexture *)
{

}

Type Grass::getType() const
{
	return GRASS;
}

Grass::~Grass(void)
{
}
