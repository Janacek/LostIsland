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
	void setCompartment(Compartment *, int nbr = 0);
	Type getType() const;
	bool isEmpty() const;
	int getNbrLabelRessource() const;
	void updateLabel();
	std::list<AEntity *> getEntities();
	~CustomToggleButton();

	sfg::ToggleButton::Ptr	_button;
	sfg::Label::Ptr			_label;
	sfg::Box::Ptr			_box;
	
private:
	void					setLabelText(Compartment *);
	Player					*_player;
	Compartment				*_ressources;
	sfg::Image::Ptr			_img;
	int						_nbrRessources; //c'est pas vraiment le nbr de ressoures
};

