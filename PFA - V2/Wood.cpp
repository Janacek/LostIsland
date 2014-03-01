#include "Wood.h"
#include "Player.h"

//Le Wood apparait lorsque l'on coupe un arbre
Wood::Wood(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Wood::doAction(AEntity* other)
{
	//Le wood ne fait rien
}

void Wood::getAction(AEntity* other)
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

void Wood::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Wood::draw(sf::RenderTexture *)
{

}

Type Wood::getType() const
{
	return WOOD;
}

Wood::~Wood(void)
{
}
