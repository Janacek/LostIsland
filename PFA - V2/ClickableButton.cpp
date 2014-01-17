#include			"ClickableButton.h"

#include <iostream>

ClickableButton::ClickableButton()
	: AComponent(), _size(sf::Vector2f(100, 100)), _text("Button")
{
	_drawableText = new sf::Text(_text, (*FontManager::getInstance().getFont(SANSATION)));

	_drawableText->setPosition(_position.x + 10, _position.y + 10);
}

ClickableButton::ClickableButton(sf::Vector2f const &position,
								 sf::Vector2f const &size,
								 std::string const &text)
								 : AComponent(position), _size(size), _text(text)
{
	_drawableText = new sf::Text(_text, (*FontManager::getInstance().getFont(SANSATION)));

	sf::Rect<float> globalBounds = _drawableText->getGlobalBounds();


	int heightPos = (_size.y / 2 - globalBounds.height / 2);

	_drawableText->setPosition(_position.x + (_size.x / 2 - globalBounds.width / 2),
		_position.y + heightPos);
}

ClickableButton::~ClickableButton()
{
	if (_drawableText)
	{
		delete _drawableText;
		_drawableText = NULL;
	}
}

#include <iostream>

void ClickableButton::draw() const
{
	sf::RectangleShape rect(_size);

	rect.setOutlineColor(sf::Color::Red);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(2.f);
	rect.setPosition(_position);

	Singleton::getInstance()._window->draw(rect);
	Singleton::getInstance()._window->draw(*_drawableText);
}

void ClickableButton::update()
{
}

sf::Vector2f const &ClickableButton::getSize() const
{
	return _size;
}

void ClickableButton::setSize(sf::Vector2f const &size)
{
	_size = size;
}

std::string const &ClickableButton::getText() const
{
	return _text;
}

void ClickableButton::setText(std::string const &text)
{
	_text = text;
}