#include "Jacket.h"
#include "Player.h"

std::string &Jacket::serialize() const
{
	std::string toto;
	return (toto);
}

void Jacket::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Jacket::Jacket()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Jacket::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Jacket);
	}
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
