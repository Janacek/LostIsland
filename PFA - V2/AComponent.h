#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class AComponent
{
public:
	AComponent();
	virtual ~AComponent();
	AComponent(sf::Vector2f const &);

	sf::Vector2f const &getPosition() const;
	void				setPosition(sf::Vector2f const &);

	virtual void draw() const = 0;
	virtual void update() = 0;

protected:
	sf::Vector2f		_position;
};