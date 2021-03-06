#pragma once

#include <SFGUI/SFGUI.hpp>
#include <vector>
#include "CustomToggleButton.h"
#include "Player.h"
#include "Crafting.h"

class GameScreen;
class Stuff;

class InventoryWindow
{
public:
	InventoryWindow();
	void init();
	void update();
	void Show(bool show = true);
	void draw();
	void createZones(std::vector<Player *>&);
	void close();
	void createCompartment(Player *);
	Player *getFirstPlayerSelected();
	std::vector<Player *> &getPlayers();
	void updateView();
	void chooseNumber(GameScreen *);
	Compartment *dropRessource();
	void setCraftingClass(Crafting *);
	void mouseLeftPress(CustomToggleButton *);
	void showBox(std::vector<Player *>&);
	void addToInventory(Player *, Compartment *, int pos);
	void fillImage(Player *player, int index, sfg::ToggleButton::Ptr);
	void updateLabel(Player *, int compt);
	~InventoryWindow();
	
private:
	void createWindow();
	void createToolbar();
	void createNumberWindow();
	void valideNumber();
	void useClick();
	void craftClick();
	void onTextChange();
	void checkScrollEvent();
	void mouseEnter(std::string const&);
	void mouseLeave(std::string const&);
	void dropClick();


	//attributs
	bool				_isInInventoryScroll;
	bool				_isInSpinButton;
	std::vector<Player *> _players;
	std::vector<sfg::Box::Ptr>	_tableBox;
	std::vector<sfg::Image::Ptr> _tableImages;
	std::vector<sfg::Table::Ptr> _tables;
	std::vector<CustomToggleButton *> _tableButtons;
	sfg::Label::Ptr			_emptyLabel;
	sfg::SpinButton::Ptr	_spinButton;
	sfg::Box::Ptr			_toolbar;
	sfg::Box::Ptr			_mainBox;
	sfg::ScrolledWindow::Ptr	_scroll;
	sfg::Adjustment::Ptr		_adjustment;
	sfg::Box::Ptr			_inventoryBox;
	sf::Image			_img;
	Crafting			*_crafting;
	sfg::Window::Ptr	_inventoryWindow;
	CustomToggleButton	*_selectedRessource;
	GameScreen			*_gameScreen; 
};

