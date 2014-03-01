#include "Fabric.h"

Fabric::Fabric()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Fabric::doAction(AEntity *other)
{
	// do action
}

void Fabric::getAction(AEntity *other)
{

}

void Fabric::loadAnimation(std::string const &, float)
{

}

void Fabric::update(Map &)
{

}

void Fabric::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Fabric::draw(sf::RenderTexture *)
{

}

Type Fabric::getType() const
{
	return FABRIC;
}

Fabric::~Fabric(void)
{
}
