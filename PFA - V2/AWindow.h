#pragma once

#include				<SFML/Window.hpp>
#include				<SFML/Graphics.hpp>
#include				<iostream>
#include				<vector>

#include				"Compartment.h"

enum Screens
{
	INVENTORY,
	STUFF,
	CRAFTING,
	GAMESCREEN,
	NONE
};
typedef struct	s_action	
{
	s_action() : _screen(NONE), _compartment(NULL){};
	Screens		_screen;
	Compartment *_compartment;
}				s_action;

class					AWindow
{
public:
	AWindow(std::string const &title, float sizeX, float sizeY, float posX = 0, float posY = 0);

	virtual void draw();
	virtual bool close() = 0;
	virtual bool clickInWindow(sf::Vector2i &);
	virtual void swapCompartment(s_action &, s_action &) = 0;
	virtual void addCompartment(s_action &, s_action &) = 0;
	virtual s_action clickInCompartment(sf::Vector2i &) = 0;
	~AWindow(void);

	std::vector<Compartment *> _compartments;
protected:
	void checkClose();
	sf::RectangleShape	_window;
	sf::RectangleShape	_banner;
	bool				_close;
	sf::RectangleShape	_closeButton;
	sf::Text			_title;
	sf::Font			*_font;
};
