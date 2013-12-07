#include "Player.h"

void Player::doAction(IEntity* other)
{
}

void Player::getAction(IEntity* other)
{
}

void Player::Animate(std::string const & string_anim)
{
}

int Player::getDamage(void) const
{
	return this->_damages;
}

Type Player::getType() const
{
	return PLAYER;
}

/*sf::Rect & Player::getCollisionBox(void)
{
}
*/