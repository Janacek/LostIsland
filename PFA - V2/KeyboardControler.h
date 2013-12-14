#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>


class KeyboardControler
{
public:
	KeyboardControler();
	~KeyboardControler();
	void handlePlayerInput(sf::Keyboard::Key &k, bool isPressed);
	void handlePlayerInput(sf::Mouse::Button &k, bool isPressed);

protected:
private:

};
