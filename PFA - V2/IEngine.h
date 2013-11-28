#pragma once

#include <list>
#include "Map.h"
#include "IEntity.h"

class IEngine
{
public:
   virtual void init(Map * map) = 0;
   virtual void update(std::list<IEntity *> players, std::list<IEntity *> entities) = 0;
};
