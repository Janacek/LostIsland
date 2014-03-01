#include "Infusion.h"

Infusion::Infusion()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Infusion::doAction(AEntity *other)
{
	// do action
}

void Infusion::getAction(AEntity *other)
{

}

void Infusion::loadAnimation(std::string const &, float)
{

}

void Infusion::update(Map &)
{

}

void Infusion::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Infusion::draw(sf::RenderTexture *)
{

}

Type Infusion::getType() const
{
	return INFUSION;
}

Infusion::~Infusion(void)
{
}
