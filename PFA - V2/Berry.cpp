#include "Berry.h"
#include "Player.h"

Berry::Berry()
: AEntity(0, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_value = 5;
}

void Berry::doAction(AEntity *other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->eat(_value);
}

void Berry::getAction(AEntity *other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->addEntityInInventory(this);
}

void Berry::loadAnimation(std::string const &, float speed)
{

}

void Berry::update(Map &map)
{

}

void Berry::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Berry::draw(sf::RenderTexture *)
{

}

Type Berry::getType() const
{
	return BERRY;
}

Berry::~Berry()
{

}