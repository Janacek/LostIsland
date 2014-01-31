#include "Water.h"
#include "Player.h"


Water::Water(void)
{
	_pos = sf::Vector2f(0,0);
}

/// <summary>
/// ON FAIT L'ACTION. Ici on appelle la methode drink du player
/// </summary>
/// <param name="other">The other.</param>
void Water::doAction(IEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);
	
	player->drink(this);
}

void Water::draw()
{
}

void Water::setPosition(sf::Vector2f &pos)
{
	_pos = pos;
}

sf::Vector2f  Water::getPosition() const
{
	return _pos;
}

void Water::setPath(std::list<std::pair<float, float> >&path)
{
	_path = path;
}

void Water::update()
{

}
/// <summary>
///GET subit l'action.
/// Appelle la méthode void getObject(IEntity *other).
/// </summary>
/// <param name="other">The other.</param>
void Water::getAction(IEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->addEntityInInventory(this);
}

void Water::loadAnimation(std::string const & string_anim, float speed)
{

}

int Water::getDamage() const
{
	return 0;
}

Type Water::getType() const
{
	return WATER;
}


Water::~Water(void)
{
}
