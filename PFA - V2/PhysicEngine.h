#include "IEngine.h"
#include "Collision.h"
#include "PathFinding.h"

class PhysicEngine
{
public:
   void init(Map * map);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);

protected:
private:
   bool _isRunning;
   Pathfinding _pathFinding;
   Collision _collision;


};