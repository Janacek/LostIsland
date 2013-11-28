#pragma once

#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
   void init(Map * map);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);

protected:
private:
   bool _isRunning;
   PathFinding _pathFinding;
};