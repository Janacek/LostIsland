#pragma once

#include <list>
#include "IScreen.h"
#include "Map.h"
#include "IEntity.h"

class IEngine
{
	public:
   virtual void init() = 0;
   virtual void update(std::list<IEntity *> players, std::list<IEntity *> entities) = 0;
};
