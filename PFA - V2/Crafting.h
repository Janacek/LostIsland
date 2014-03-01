#pragma once

#include <SFGUI/SFGUI.hpp>
#include "CustomToggleButton.h"
#include "DatabaseManager.h"
#include "EntityFactory.h"

class Crafting
{
public:

public:
	Crafting();
	void createWindow();
	void createTables();
	void update();
	void addInTable(CustomToggleButton *, int);
	void Show(bool show = true);
	void draw();
	~Crafting();
private:
	void								mouseLeftPress(CustomToggleButton *);
	void								craft();
	void								remove();

	DatabaseManager						_databaseManager;
	EntityFactory						_entityFactory;
	sfg::Window::Ptr					_craftingWindow;
	std::vector<CustomToggleButton *> _tableButton;
	sfg::Table::Ptr						_largeTable;
	sfg::Box::Ptr						_boxButtons;
	sfg::Box::Ptr						_mainBox;
	CustomToggleButton					*_selectedRessource;
};

