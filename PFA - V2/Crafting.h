#pragma once

#include		"AWindow.h"
#include		<vector>

class			Crafting : public AWindow
{
public:
	Crafting(std::string const &title = "Crafting");
	bool close();
	void update();
	~Crafting(void);
};

