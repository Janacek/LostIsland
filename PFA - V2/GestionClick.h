#pragma once

#include "IScreen.h"
#include "Compartment.h"
#include "Player.h"

class		GestionClick
{
public:
	GestionClick();
	~GestionClick();
	void leftPress(int index, Player *p, sfg::Image::Ptr);
	void dump(int index, Player *p);
	void clearLastCompartment();
	void cantDrop();
	void reset();
	void leftRelease(int index, Player *p, sfg::Image::Ptr);
	s_action canDrop();
	void drop();
	
private:
	void swap();

	struct s_action			_leftClickPressed;
	struct s_action			_leftClickReleased;
	struct s_action			_rightClickPressed;
	struct s_action			_rightClickReleased;
	Compartment				*_lastCompartment;
	bool					_canDrop;
};

