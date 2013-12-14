#pragma once

#include		"AWindow.h"

class			Stuff : public AWindow
{
public:
	Stuff(std::string const &title = "Stuff");
	void update();
	bool close();
	~Stuff(void);
};

