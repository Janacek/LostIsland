#pragma once

#include "AComponent.h"
#include "Singleton.h"
#include "FontManager.h"

class ClickableButton : public AComponent
{
public:
	ClickableButton();
	ClickableButton(sf::Vector2f const &,
		sf::Vector2f const &,
		std::string const &);
	~ClickableButton();
	void draw() const;
	void update();

	sf::Vector2f const &getSize() const;
	void setSize(sf::Vector2f const &);

	std::string const &getText() const;
	void setText(std::string const &);

private:
	sf::Vector2f	_size;
	std::string		_text;
	sf::Text		*_drawableText;
	// function;
};