#include "Wood.h"
#include "Player.h"

//Le Wood apparait lorsque l'on coupe un arbre
Wood::Wood(void)
{
	_pos = sf::Vector2f(0, 0);
}

void Wood::doAction(IEntity* other)
{
	//Le wood ne fait rien
}

void Wood::getAction(IEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->addEntityInInventory(this);
}

void Wood::loadAnimation(std::string const & string_anim, float speed)
{

}

void Wood::update(Map &map)
{

}

void Wood::draw()
{

}

void Wood::setPosition(sf::Vector2f &pos)
{
	_pos = pos;
}

int Wood::getDamage() const
{
	return 0;
}

Type Wood::getType() const
{
	return WOOD;
}

sf::Vector2f  Wood::getPosition() const
{
	return _pos;
}

void Wood::setPath(std::list<std::pair<float, float> > &path)
{
	_path = path;
}

Wood::~Wood(void)
{
}
