#pragma once

#include "AWindow.h"

class			Stuff : public AWindow
{
public:
	Stuff(std::string const &title = "Stuff");
	void update();
	s_action clickInCompartment();
	bool close();
	~Stuff(void);
};

