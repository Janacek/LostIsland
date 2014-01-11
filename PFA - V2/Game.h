#pragma once

#include <stack>
#include "Singleton.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "PhysicEngine.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void launch(void);
	void init();

protected:
private:
	GraphicEngine			*_graphicEngine;
	GameEngine				*_gameEngine;
	PhysicEngine			*_physicEngine;
	sf::Clock				_cl;
	std::stack<IScreen *>	_states;
	IScreen* GetCurrentState(void) 
	{
		return (!_states.empty()) ? _states.top() : NULL;
	}

};

