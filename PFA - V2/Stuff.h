#pragma once

#include "InventoryWindow.h"

class Stuff
{
public:
	Stuff();
	void Show(bool show = true);
	void createZones(std::vector<Player *>& players);
	void showBox(std::vector<Player *>&);
	void checkScrollEvent();
	~Stuff();
private:
	void createWindow();
	void createCompartment(Player *);
	void createToolbar();
	void deleteClick();
	void mousePos(bool);
	void mouseLeftPress(CustomToggleButton *);

	bool								_isInStuffScroll;
	std::vector<Player *>				 _players;
	std::vector<CustomToggleButton *>	_tableButtons;
	std::vector<sfg::Table::Ptr>		_tables;
	std::vector<sfg::Box::Ptr>			_tableBox;
	sfg::Window::Ptr					_stuffWindow;
	sfg::Box::Ptr						_mainBox;
	sfg::ScrolledWindow::Ptr			_scroll;
	sfg::Box::Ptr						_toolbar;
	sfg::Box::Ptr						_stuffBox;
	CustomToggleButton					*_selectedRessource;
};

