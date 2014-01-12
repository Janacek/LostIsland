#pragma once

#include <list>
#include <vector>
#include <stack>
#include "IEntity.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "IEngine.h"
#include "IScreen.h"
#include "KeyboardControler.h"

class GraphicEngine : public IEngine
{
public:
	GraphicEngine(std::stack<IScreen *> &);

	void run();
	void draw();

	void init();
	bool getIsRunning() const;
	void update();

	IScreen* GetCurrentState(void) 
	{
		return (!_states.empty()) ? _states.top() : NULL;
	}

protected:
private:
	bool					_isRunning;
	StartScreen				*_startScreen;
	GameScreen				*_gameScreen;
	//TODO OptionScreen

	std::stack<IScreen *>	&
		_states;
	KeyboardControler		_controler;

};