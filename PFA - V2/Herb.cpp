#include "Herb.h"

Herb::Herb()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Herb::doAction(AEntity *other)
{
	// do action
}

void Herb::getAction(AEntity *other)
{

}

void Herb::loadAnimation(std::string const &, float)
{

}

void Herb::update(Map &)
{

}

void Herb::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Herb::draw(sf::RenderTexture *)
{

}

Type Herb::getType() const
{
	return HERB;
}

Herb::~Herb(void)
{
}
