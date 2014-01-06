#pragma once

#include <list>
#include "Map.h"
#include "IEntity.h"

class GameEvents
{
public:
	GameEvents();
	void init();
   void update(std::vector<IEntity *> &players, std::list<IEntity *> &entities);

protected:
private:
	sf::Time	_timeElapsed;

};
