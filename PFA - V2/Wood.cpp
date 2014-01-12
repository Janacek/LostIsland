#include "Wood.h"
#include "Player.h"

//Le Wood apparait lorsque l'on coupe un arbre
Wood::Wood(void)
{
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

void Wood::Animate(std::string const & string_anim)
{

}

void Wood::draw()
{

}

void Wood::setPosition(sf::Vector2f &pos)
{

}

int Wood::getDamage() const
{
	return 0;
}

Type Wood::getType() const
{
	return WOOD;
}

Wood::~Wood(void)
{
}
