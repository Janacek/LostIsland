#pragma once

#include <SFGUI/SFGUI.hpp>
#include <vector>
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
	void createTabs(std::vector<Player *>&);
	void close();
	void createCompartment(Player *);
	void chooseNumber(GameScreen *);
	Compartment *dropRessource();
	void mouseLeftPress(int index);
	void mouseLeftRelease(int index);
	void addToInventory(Player *, IEntity *);
	const sf::Image&fillImage(Player *player, int index);
	~InventoryWindow();

	sfg::Desktop _desktop;
//private:
	void createWindow();
	void createNumberWindow();
	void valideNumber();
	void onTextChange();

	//attributs
	std::vector<Player *> _players;
	std::vector<sfg::Image::Ptr> _tableImages;
	int					_dropNbr;
	GestionClick		_gestionClick;
	sf::Image			_img;
	sf::Image			_test;
	sfg::Notebook::Ptr		_noteBook1;
	sfg::Notebook::Ptr		_noteBook2;
	sfg::Notebook::Ptr		_noteBook3;
	sfg::Window::Ptr	_inventoryWindow;
	sfg::Window::Ptr	_numberWindow;
	sfg::Entry::Ptr		_entry;
	sfg::Label::Ptr		_label;
	sfg::Button::Ptr	_closeButton;
	GameScreen			*_gameScreen; //moche ...
};

