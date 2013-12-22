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
	GraphicEngine(Map *&, std::stack<IScreen *> &, std::vector<IEntity *> &, std::list<IEntity *> &);

	void run();
	void draw(std::vector<IEntity *> &players, std::list<IEntity *> &entities);

	void init();
	bool getIsRunning() const;
	void update(std::vector<IEntity *> &players, std::list<IEntity *> &entities);

	IScreen* GetCurrentState(void) 
	{
		return (!_states.empty()) ? _states.top() : NULL;
	}

protected:
private:
	bool					_isRunning;
	Map						*_map;
	StartScreen				*_startScreen;
	GameScreen				*_gameScreen;
	//TODO OptionScreen

	std::stack<IScreen *>	&
		_states;
	std::vector<IEntity *>	&_players;
	std::list<IEntity *>	&_entities;
	KeyboardControler		_controler;

};