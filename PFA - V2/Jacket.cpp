#include "Jacket.h"

Jacket::Jacket()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Jacket::doAction(AEntity *other)
{
	// do action
}

void Jacket::getAction(AEntity *other)
{

}

void Jacket::loadAnimation(std::string const &, float)
{

}

void Jacket::update(Map &)
{

}

void Jacket::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Jacket::draw(sf::RenderTexture *)
{

}

Type Jacket::getType() const
{
	return JACKET;
}

Jacket::~Jacket(void)
{
}
