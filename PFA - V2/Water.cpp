#include "Water.h"
#include "Player.h"


Water::Water(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

/// <summary>
/// ON FAIT L'ACTION. Ici on appelle la methode drink du player
/// </summary>
/// <param name="other">The other.</param>
void Water::doAction(AEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);
	
	player->drink(this);
}

void Water::draw(sf::RenderTexture *, sf::Shader &)
{
}

void Water::draw(sf::RenderTexture *)
{
}

void Water::update(Map &map)
{

}
/// <summary>
///GET subit l'action.
/// Appelle la méthode void getObject(AEntity *other).
/// </summary>
/// <param name="other">The other.</param>
void Water::getAction(AEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->addEntityInInventory(this);
}

void Water::loadAnimation(std::string const & string_anim, float speed)
{

}

Type Water::getType() const
{
	return WATER;
}


Water::~Water(void)
{
}
