#pragma once

#include		<vector>
#include		 "AWindow.h"


class			Crafting : public AWindow
{
public:
	Crafting(std::string const &title = "Crafting");
	bool close();
	void update();
	s_action clickInCompartment();
	~Crafting(void);
};

