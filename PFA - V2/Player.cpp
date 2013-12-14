#include "Player.h"


Player::Player()
{
	this->_name = "Georgette";
}

void Player::doAction(IEntity* other)
{
}

void Player::getAction(IEntity* other)
{
}

void Player::Animate(std::string const & string_anim)
{
}

void Player::setName(std::string const &name)
{
	this->_name = name;
}

std::string const &Player::getName() const
{
	return this->_name;
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