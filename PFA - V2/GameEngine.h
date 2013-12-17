#pragma once

#include <stack>
#include "IEntity.h"
#include "IEngine.h"
#include "GameEvents.h"
#include "KeyboardControler.h"

class GameEngine : public IEngine
{
public:
	GameEngine(Map *&, std::stack<IScreen *>&);
	~GameEngine();
	bool getIsRunning() const;
	void init();
	void update(std::list<IEntity *> players, std::list<IEntity *> entities);

protected:
private:
	bool _isRunning;
	GameEvents				*_gameEvents;	
	sf::Clock				*_cl;
	KeyboardControler		_controler;
	Map						*&_map;
	std::stack<IScreen *>	&_states;

};

