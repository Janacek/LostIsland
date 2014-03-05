#pragma once

#include <SFGUI/SFGUI.hpp>
#include "Player.h"

class CustomToggleButton
{
public:
	CustomToggleButton(Player *, Compartment *);
	Player *getPlayer();
	void empty();
	Compartment *getCompartment();
	void setCompartment(Compartment *);
	Type getType() const;
	bool isEmpty() const;
	std::list<AEntity *> getEntities();
	~CustomToggleButton();

	sfg::ToggleButton::Ptr	_button;
	
private:
	Player *_player;
	Compartment *_ressources;
	sfg::Image::Ptr _img;
};

