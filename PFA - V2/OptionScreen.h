#pragma once

#include "IScreen.h"
#include "StartScreen.h"
#include "ClickableButton.h"

class OptionScreen : public IScreen
{
public:
	OptionScreen();
	~OptionScreen();

	void draw();
	void initialize(void);
	IScreen * getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);
	stateName getStateName() const;
	void events(sf::Event &);

private:
	bool				_isRunning;
	IScreen				*_next;

	sfg::Window::Ptr	_window;
	sfg::Desktop		_desktop;
	sfg::Button::Ptr	_button;

public:
	void				onButtonClick(void);
};