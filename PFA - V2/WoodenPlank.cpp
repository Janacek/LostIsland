#include "WoodenPlank.h"

std::string &WoodenPlank::serialize() const
{
	std::string toto;
	return (toto);
}

void WoodenPlank::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

WoodenPlank::WoodenPlank()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void WoodenPlank::doAction(AEntity *other)
{
	// nothing
}

void WoodenPlank::getAction(AEntity *other)
{
	// ??
}

void WoodenPlank::loadAnimation(std::string const &, float)
{

}

void WoodenPlank::update(Map &)
{

}

void WoodenPlank::draw(sf::RenderTexture *, sf::Shader &)
{

}

void WoodenPlank::draw(sf::RenderTexture *)
{

}

Type WoodenPlank::getType() const
{
	return WOODEN_PLANK;
}

WoodenPlank::~WoodenPlank()
{

}