#include "Meat.h"
#include "Player.h"

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
	_value = 15;
}

void Meat::doAction(AEntity* other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->eat(_value);
	}
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
