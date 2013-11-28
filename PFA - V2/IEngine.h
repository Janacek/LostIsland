#include <list>
#include "Map.h"
#include "IEntity.h"


class Game;

class IEngine
{
public:
   void init(Map * map);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);

   Game** game;

protected:
private:
   bool _isRunning;


};
