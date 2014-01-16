#pragma once

#include "IScreen.h"
#include "StartScreen.h"

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

private:
	bool				_isRunning;
	IScreen				*_next;
};