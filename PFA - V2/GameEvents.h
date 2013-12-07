#pragma once

#include <list>
#include "Map.h"
#include "IEntity.h"

class GameEvents
{
public:
	GameEvents();
	void init();
   void update(std::list<IEntity *> players, std::list<IEntity *> entities, Map * map);

protected:
private:
	sf::Time	_timeElapsed;

};
