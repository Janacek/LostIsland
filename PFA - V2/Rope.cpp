#include "Rope.h"
#include "Player.h"

std::string &Rope::serialize() const
{
	std::string toto;
	return (toto);
}

void Rope::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Rope::Rope()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Rope::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Rope);
	}
}

void Rope::getAction(AEntity *other)
{

}

void Rope::loadAnimation(std::string const &, float)
{

}

void Rope::update(Map &)
{

}

void Rope::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Rope::draw(sf::RenderTexture *)
{

}

Type Rope::getType() const
{
	return ROPE;
}

Rope::~Rope(void)
{
}
