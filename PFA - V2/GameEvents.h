#include <list>
#include "Map.h"
#include "IEntity.h"

class GameEvents
{
public:
   void update(std::list<IEntity *> players, std::list<IEntity *> entities, Map * map);

protected:
private:

};
