#include "Water.h"


Water::Water(void)
{
}

/// <summary>
/// ON FAIT L'ACTION. Ici on appelle la methode drink du player
/// </summary>
/// <param name="other">The other.</param>
void Water::doAction(IEntity* other)
{
	//dynamic  cast en player
	//player->drink(this);
}

/// <summary>
///GET subit l'action.
/// Appelle la méthode void getObject(IEntity *other).
/// </summary>
/// <param name="other">The other.</param>
void Water::getAction(IEntity* other)
{
	//dynamic cast
	//other->getObject(this);
	// ici player va getObject et le stock dans l'inventaire
}

void Water::Animate(std::string const & string_anim)
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
