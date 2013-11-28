#include <list>
#include "IEvents.h"
#include "IEntity.h"
#include "IEngine.h"
#include "KeyboardControler.h"

class GameEngine
{
public:
   void init(Map * map);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);

protected:
private:
   bool _isRunning;
   KeyboardControler _controler;
   IEvent _events;


};

