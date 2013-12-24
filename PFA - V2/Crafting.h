#pragma once

#include		<vector>
#include		 "AWindow.h"


class			Crafting : public AWindow
{
public:
	Crafting(std::string const &title = "Crafting");
	bool close();
	void update();
	s_action clickInCompartment(sf::Vector2i &);
	void swapCompartment(s_action &, s_action &);
	void addCompartment(s_action &, s_action &);
	~Crafting(void);
};

