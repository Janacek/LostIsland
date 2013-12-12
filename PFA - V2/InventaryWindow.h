#pragma once

#include "Compartment.h"
#include <vector>

class InventaryWindow
{
public:
	InventaryWindow(void);
	~InventaryWindow(void);
	void draw();
	void update();
	void addCompartment();

// private:
	sf::RectangleShape _inventaryWindow;
	std::vector<Compartment *> _compartments;
};

