#pragma once

#include "Compartment.h"
#include "Player.h"
#include "AWindow.h"
#include "Onglet.h"
#include <vector>


class InventaryWindow : public AWindow
{
public:
	InventaryWindow(std::vector<Player *> &, std::string const &title = "Inventory");
	~InventaryWindow(void);
	void draw();
	void update();
	bool close();
	void addCompartment();
	void createOnglets();
	void changeCompartments(Onglet *);
	// private:
	//sf::RectangleShape _inventaryWindow;
	std::vector<Player *>			_players;
	std::vector<Onglet *>			_onglets;
};

