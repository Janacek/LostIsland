#include "Infusion.h"
#include "Player.h"
#include "Water.h"

std::string &Infusion::serialize() const
{
	std::string toto;
	return (toto);
}

void Infusion::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Infusion::Infusion()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Infusion::doAction(AEntity *other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->drink(new Water);
		player->_isSick = false;
	}
}

void Infusion::getAction(AEntity *other)
{

}

void Infusion::loadAnimation(std::string const &, float)
{

}

void Infusion::update(Map &)
{

}

void Infusion::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Infusion::draw(sf::RenderTexture *)
{

}

Type Infusion::getType() const
{
	return INFUSION;
}

Infusion::~Infusion(void)
{
}
