#include "Sword.h"

Sword::Sword()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Sword::doAction(AEntity *other)
{
	// do action
}

void Sword::getAction(AEntity *other)
{

}

void Sword::loadAnimation(std::string const &, float)
{

}

void Sword::update(Map &)
{

}

void Sword::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Sword::draw(sf::RenderTexture *)
{

}

Type Sword::getType() const
{
	return SWORD;
}

Sword::~Sword(void)
{
}
