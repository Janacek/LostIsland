#include <list>
#include "IEngine.h"

class GraphicEngine;

class IScreen
{
public:
   void draw(std::list<IEntity *> entities);
   void initialize(void);
   IScreen * getNextState(void);
   void release(void);
   bool isRunning(void);
   void update(void);

   GraphicEngine** graphicEngine;

protected:
private:

};