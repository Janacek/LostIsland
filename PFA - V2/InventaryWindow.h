#pragma once

#include <vector>
#include "AWindow.h"
#include "Player.h"
#include "Onglet.h"

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
	s_action clickInCompartment(sf::Vector2i&);
	 void swapCompartment(s_action &, s_action &);
	 void addCompartment(s_action &, s_action &);
	// private:
	//sf::RectangleShape _inventaryWindow;
	std::vector<Player *>			_players;
	std::vector<Onglet *>			_onglets;
};

