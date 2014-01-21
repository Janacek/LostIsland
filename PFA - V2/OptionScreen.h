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

	// Music Stuff
	sfg::Label::Ptr		_musicLabel;
	sfg::Scale::Ptr		_musicScale;
	sfg::Adjustment::Ptr _musicAdjustment;

	// SFX Stuff
	sfg::Label::Ptr		_sfxLabel;
	sfg::Scale::Ptr		_sfxScale;
	sfg::Adjustment::Ptr _sfxAdjustment;

public:
	void				musicAdjustmentChange(void);
	void				sfxAdjustmentChange(void);
};