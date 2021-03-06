#include "Sword.h"
#include "Player.h"

std::string &Sword::serialize() const
{
	std::string toto;
	return (toto);
}

void Sword::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Sword::Sword()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Sword::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Sword);
	}
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
