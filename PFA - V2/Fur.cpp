#include "Fur.h"

std::string &Fur::serialize() const
{
	std::string toto;
	return (toto);
}

void Fur::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Fur::Fur(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Fur::doAction(AEntity* other)
{

}

void Fur::getAction(AEntity* other)
{

}

void Fur::loadAnimation(std::string const & string_anim, float speed)
{

}
void Fur::update(Map &map)
{

}

void Fur::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Fur::draw(sf::RenderTexture *)
{

}

Type Fur::getType() const
{
	return FUR;
}

Fur::~Fur(void)
{
}
