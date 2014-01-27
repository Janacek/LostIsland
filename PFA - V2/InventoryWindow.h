#pragma once

#include <SFGUI/SFGUI.hpp>
#include <vector>
#include "Player.h"

class InventoryWindow
{
public:
	InventoryWindow();
	void init();
	void update();
	void draw();
	void createTabs(std::vector<Player *>&);
	void createCompartment(Player *);
	~InventoryWindow();

	sfg::Desktop _desktop;
//private:
	void createWindow();

	//attributs
	sf::Image			_img;
	sfg::Notebook::Ptr _noteBook;
	sfg::Window::Ptr _inventoryWindow;
	sfg::Window::Ptr _numberWindow;
	
	sfg::Button::Ptr _button;
	sfg::Box::Ptr		_box;
};

