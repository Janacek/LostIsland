#include "Pants.h"

std::string &Pants::serialize() const
{
	std::string toto;
	return (toto);
}

void Pants::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Pants::Pants()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Pants::doAction(AEntity *other)
{
	// do action
}

void Pants::getAction(AEntity *other)
{

}

void Pants::loadAnimation(std::string const &, float)
{

}

void Pants::update(Map &)
{

}

void Pants::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Pants::draw(sf::RenderTexture *)
{

}

Type Pants::getType() const
{
	return PANTS;
}

Pants::~Pants(void)
{
}
