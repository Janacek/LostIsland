#include "Stew.h"
#include "Player.h"

std::string &Stew::serialize() const
{
	std::string toto;
	return (toto);
}

void Stew::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Stew::Stew()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_waterValue = 30;
	_eatValue = 30;
}

void Stew::doAction(AEntity *other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->drink(_waterValue);
		player->eat(_eatValue);
	}
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
