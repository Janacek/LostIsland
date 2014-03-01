#include "Stew.h"

Stew::Stew()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Stew::doAction(AEntity *other)
{
	// do action
}

void Stew::getAction(AEntity *other)
{

}

void Stew::loadAnimation(std::string const &, float)
{

}

void Stew::update(Map &)
{

}

void Stew::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Stew::draw(sf::RenderTexture *)
{

}

Type Stew::getType() const
{
	return STEW;
}

Stew::~Stew(void)
{
}
