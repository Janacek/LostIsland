#pragma once
#include <list>
#include "IEntity.h"
#include "IEngine.h"
#include "GameEvents.h"
#include "KeyboardControler.h"

class GameEngine
{
public:
	GameEngine();
	bool getIsRunning() const;
	void init(Map * map);
	void update(std::list<IEntity *> players, std::list<IEntity *> entities);

protected:
private:
	bool _isRunning;
	GameEvents				*_gameEvents;	
	sf::Clock				*_cl;
	KeyboardControler _controler;
	Map						*_map;

};

