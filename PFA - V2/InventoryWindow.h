#pragma once

#include <SFGUI/SFGUI.hpp>
#include <vector>
#include "CustomToggleButton.h"
#include "GestionClick.h"
#include "Player.h"

class GameScreen;

class InventoryWindow
{
public:
	InventoryWindow();
	void init();
	void update();
	void draw();
	void createZones(std::vector<Player *>&);
	void close();
	void createCompartment(Player *);
	void chooseNumber(GameScreen *);
	Compartment *dropRessource();
	void mouseLeftPress(CustomToggleButton *);
	void showBox(std::vector<Player *>&);
	void addToInventory(Player *, IEntity *);
	void fillImage(Player *player, int index, sfg::ToggleButton::Ptr);
	~InventoryWindow();

	
//private:
	void createWindow();
	void createToolbar();
	void createNumberWindow();
	void valideNumber();
	void useClick();
	void onTextChange();

	//attributs
	std::vector<Player *> _players;
	std::vector<sfg::Box::Ptr>	_tableBox;
	std::vector<sfg::Image::Ptr> _tableImages;
	std::vector<sfg::Table::Ptr> _tables;
	std::vector<CustomToggleButton *> _tableButtons;
	sfg::Label::Ptr			_emptyLabel;
	sfg::Box::Ptr			_toolbar;
	sfg::Box::Ptr			_mainBox;
	sfg::ScrolledWindow::Ptr	_scroll;
	sfg::Box::Ptr			_inventoryBox;
	GestionClick		_gestionClick;
	sf::Image			_img;
	sfg::Window::Ptr	_inventoryWindow;
	CustomToggleButton	*_selectedRessource;
	GameScreen			*_gameScreen; //moche ...
};

