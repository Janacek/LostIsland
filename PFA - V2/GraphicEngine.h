#pragma once

#include <list>
#include <stack>
#include "IEntity.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "IEngine.h"
#include "IScreen.h"

class GraphicEngine : public IEngine
{
public:
	GraphicEngine(Map *&, std::stack<IScreen *>&);
	~GraphicEngine();
	void init();
	bool getIsRunning() const;
	void update(std::list<IEntity *> players, std::list<IEntity *> entities); //pas utilisé
	IScreen* GetCurrentState(void) {return (!_states.empty()) ? _states.top() : NULL;}
	void PushState(IScreen *state);//gameEngine
	void SetState(IScreen *state);// gameEngine
	void PopState(void);// gameEngine

protected:
private:
	std::list<IEntity *> _entities;
	bool _isRunning;
	Map			*&_map;
	std::stack<IScreen *> &_states;
	StartScreen *_startScreen;
	GameScreen  *_gameScreen;
	//TODO OptionScreen
	
};