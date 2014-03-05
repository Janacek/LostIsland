#include "Meat.h"

std::string &Meat::serialize() const
{
	std::string toto;
	return (toto);
}

void Meat::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Meat::Meat(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Meat::doAction(AEntity* other)
{
	//De la Meat sauvage apparait
}

void Meat::getAction(AEntity* other)
{

}

void Meat::loadAnimation(std::string const & string_anim, float speed)
{

}
void Meat::update(Map &map)
{

}

void Meat::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Meat::draw(sf::RenderTexture *)
{

}

Type Meat::getType() const
{
	return MEAT;
}

Meat::~Meat(void)
{
}
