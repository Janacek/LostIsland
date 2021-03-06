#include "Fabric.h"
#include "Player.h"

std::string &Fabric::serialize() const
{
	std::string toto;
	return (toto);
}

void Fabric::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Fabric::Fabric()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Fabric::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Fabric);
	}
}

void Fabric::getAction(AEntity *other)
{

}

void Fabric::loadAnimation(std::string const &, float)
{

}

void Fabric::update(Map &)
{

}

void Fabric::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Fabric::draw(sf::RenderTexture *)
{

}

Type Fabric::getType() const
{
	return FABRIC;
}

Fabric::~Fabric(void)
{
}
