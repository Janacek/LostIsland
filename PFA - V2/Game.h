
#include "IEngine.h"

class Game
{
public:
   void launch(void);

protected:
private:
   IEngine _graphicEngine;
   IEngine _gameEngine;
   IEngine _physicEngine;


};

