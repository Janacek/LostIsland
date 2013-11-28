#include <list>
#include <stack>
#include "IENtity.h"
#include "IEngine.h"
#include "IScreen.h"

class GraphicEngine
{
public:
   void init(Map * map);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);
   IScreen* GetCurrentState__(void);
   void PushState(IScreen* state);
   void SetState(IScreen* state);
   void PopState(void);

protected:
private:
   std::list<IEntity *> _entities;
   bool _isRunning;
   IScreen _startScreen;
   IScreen _optionScreen;
   IScreen _gameScreen;
   std::stack<IScreen *> _states;


};

#endif