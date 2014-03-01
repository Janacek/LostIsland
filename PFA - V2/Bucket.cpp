#include "Bucket.h"

Bucket::Bucket()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Bucket::doAction(AEntity *other)
{
	// do action
}

void Bucket::getAction(AEntity *other)
{

}

void Bucket::loadAnimation(std::string const &, float)
{

}

void Bucket::update(Map &)
{

}

void Bucket::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Bucket::draw(sf::RenderTexture *)
{

}

Type Bucket::getType() const
{
	return BUCKET;
}

Bucket::~Bucket(void)
{
}
