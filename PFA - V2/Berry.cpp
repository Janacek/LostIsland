#include "Berry.h"
#include "Player.h"

Berry::Berry()
{
	_pos = sf::Vector2f(0, 0);
	_id = IEntityId++;
	_value = 5;
}

void Berry::doAction(IEntity *other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->eat(_value);
}

void Berry::getAction(IEntity *other)
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

void Berry::setPosition(sf::Vector2f &pos)
{
	_pos = pos;
}

int Berry::getDamage() const
{
	return 0;
}

Type Berry::getType() const
{
	return BERRY;
}

sf::Vector2f Berry::getPosition() const
{
	return _pos;
}

void Berry::setPath(std::list<std::pair<float, float>> &path)
{
	_path = path;
}

Berry::~Berry()
{

}