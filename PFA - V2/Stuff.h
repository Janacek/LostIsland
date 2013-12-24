#pragma once

#include "AWindow.h"

class			Stuff : public AWindow
{
public:
	Stuff(std::string const &title = "Stuff");
	void update();
	s_action clickInCompartment(sf::Vector2i&);
	void swapCompartment(s_action &, s_action &);
	 void addCompartment(s_action &, s_action &);
	bool close();
	~Stuff(void);
};

