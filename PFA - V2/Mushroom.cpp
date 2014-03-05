#include "Mushroom.h"

std::string &Mushroom::serialize() const
{
	std::string toto;
	return (toto);
}

void Mushroom::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Mushroom::Mushroom()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Mushroom::doAction(AEntity *other)
{
	// do action
}

void Mushroom::getAction(AEntity *other)
{

}

void Mushroom::loadAnimation(std::string const &, float)
{

}

void Mushroom::update(Map &)
{

}

void Mushroom::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Mushroom::draw(sf::RenderTexture *)
{

}

Type Mushroom::getType() const
{
	return MUSHROOM;
}

Mushroom::~Mushroom(void)
{
}
