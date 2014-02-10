#pragma once

#include <SFGUI/SFGUI.hpp>
#include <vector>

#include "IEntity.h"

class GameScreen;

class RessourcesWindow
{
public:
	RessourcesWindow(GameScreen *);
	~RessourcesWindow();
	void update();
	void Show(bool show = true);
	void updateView(std::vector<IEntity *> &);
	void draw();

private:
	void createWindow(GameScreen *);
	void createCompartment();
	void selectRessource(int);
	void clickOnGetButton(GameScreen *);
	sfg::Window::Ptr _ressourcesWindow;
	std::vector<IEntity *> _content;
	std::vector<sfg::Image::Ptr> _tableImages;
	std::vector<sfg::ToggleButton::Ptr> _tableButtons;

	sf::Image		_img;
	sfg::Button::Ptr _getButton;
};

