#pragma once

#include <SFGUI/SFGUI.hpp>
#include "CustomToggleButton.h"
#include "DatabaseManager.h"
#include "EntityFactory.h"
#include "Player.h"

class InventoryWindow;

class Crafting
{
public:

public:
	Crafting();
	void setInventoryClass(InventoryWindow *);
	void update();
	void addInTable(CustomToggleButton *, int);
	void createChooseWindowContent();
	void Show(bool show = true);
	void draw();
	~Crafting();
private:
	void								createChooseWindow();
	void								createWindow();
	void								createTables();
	void								updateContent();
	void								updateImgResult();
	void								validCraft(Player *);
	void								mouseLeftPress(CustomToggleButton *);
	void								craft();
	void								remove();

	DatabaseManager						_databaseManager;
	sfg::Image::Ptr						_imgResult;
	EntityFactory						_entityFactory;
	sfg::Window::Ptr					_craftingWindow;
	std::vector<AEntity	*>				_content;
	std::vector<CustomToggleButton *> _tableButton;
	sfg::Table::Ptr						_largeTable;
	sfg::Box::Ptr						_boxButtons;
	sfg::Box::Ptr						_mainBox;
	CustomToggleButton					*_selectedRessource;
	InventoryWindow						*_inventoryWindow;
	sfg::Window::Ptr					_choosePlayerWindow;
	AEntity								*_objectCraft;
};

