#include "Flint.h"
#include "Player.h"

std::string &Flint::serialize() const
{
	std::string toto;
	return (toto);
}

void Flint::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Flint::Flint()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Flint::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Flint);
	}
}

void Flint::getAction(AEntity *other)
{

}

void Flint::loadAnimation(std::string const &, float)
{

}

void Flint::update(Map &)
{

}

void Flint::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Flint::draw(sf::RenderTexture *)
{

}

Type Flint::getType() const
{
	return SILEX;
}

Flint::~Flint(void)
{
}
