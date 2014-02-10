#pragma once

#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "IEngine.h"
#include "IEntity.h"
#include "Compartment.h"

enum Screens
{
	INVENTORY,
	STUFF,
	CRAFTING,
	GAMESCREEN,
	NONE,
	WINDOW
};
typedef struct	s_action
{
	s_action(bool windows = false) : _compartment(NULL)
	{
		if (windows)
			_screen = WINDOW;
		else
		{
			_screen = NONE;
		}
	}
	void reset()
	{
		_screen = NONE;
		_compartment = NULL;
		_img = NULL;
	}

	Screens		_screen;
	Compartment *_compartment;
	sfg::Image::Ptr _img;
}				s_action;

enum stateName
{
	GAME,
	MENU,
	OPTIONS,
};

class IScreen
{
public:
	virtual ~IScreen() {};
	virtual void draw() = 0;
	virtual void initialize(void) = 0;
	virtual IScreen * getNextState(void) = 0;
	virtual void release(void) = 0;
	virtual  bool isRunning(void) const = 0;
	virtual void update(void) = 0;
	virtual void events(sf::Event &) = 0;
	virtual stateName getStateName() const = 0;

protected:
private:

};