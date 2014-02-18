#pragma once

#include <SFGUI/SFGUI.hpp>
#include "CustomToggleButton.h"

class Crafting
{
public:
	enum Distance
	{
		NEARTABLE,
		FARTABLE
	};
public:
	Crafting();
	void createWindow();
	void createTables();
	void update();
	void chooseDistance(Crafting::Distance);
	bool isNearTable() const;
	void Show(bool show = true);
	void draw();
	~Crafting();
private:
	void								mouseLeftPress();
	void								craft();

	bool								_isNearTable;
	sfg::Window::Ptr					_craftingWindow;
	std::vector<sfg::ToggleButton::Ptr> _tableButton;
	sfg::Table::Ptr						_smallTable;
	sfg::Table::Ptr						_largeTable;
	sfg::Box::Ptr						_boxButtons;
	sfg::Box::Ptr						_mainBox;
};

