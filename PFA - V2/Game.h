#pragma once

#include <list>
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
	std::list<IScreen *>	_states;
	IScreen* GetCurrentState(void) 
	{
		return (!_states.empty()) ? _states.front() : NULL;
	}

};

