#include			"AComponent.h"

AComponent::AComponent()
	: _position(sf::Vector2f(0, 0))
{
}

AComponent::~AComponent()
{
}

AComponent::AComponent(sf::Vector2f const &position)
	: _position(position)
{
}

sf::Vector2f const &AComponent::getPosition() const
{
	return _position;
}

void AComponent::setPosition(sf::Vector2f const &position)
{
	_position = position;
}