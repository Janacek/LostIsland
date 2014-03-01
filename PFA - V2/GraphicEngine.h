#pragma once

#include <list>
#include <vector>
#include <list>
#include "AEntity.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "IEngine.h"
#include "IScreen.h"
#include "KeyboardControler.h"

class GraphicEngine : public IEngine
{
public:
	GraphicEngine(std::list<IScreen *> &);

	void run();
	void draw();

	void init();
	bool getIsRunning() const;
	void update();

	IScreen* GetCurrentState(void) 
	{
		return (!_states.empty()) ? _states.front() : NULL;
	}

protected:
private:
	bool					_isRunning;
	StartScreen				*_startScreen;
	GameScreen				*_gameScreen;

	std::list<IScreen *>	&_states;
	KeyboardControler		_controler;

};