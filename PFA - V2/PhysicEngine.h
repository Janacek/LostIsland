#pragma once

#include <stack>
#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
	PhysicEngine(Map *&, std::stack<IScreen *>&);
   void init();
   void update(std::vector<IEntity *> &players, std::list<IEntity *> &entities);

protected:
private:
   bool _isRunning;
   //PathFinding _pathFinding;
   Map *&_map;
   std::stack<IScreen *> &_states;
};