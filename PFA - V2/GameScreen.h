#include "IScreen.h"

class GameScreen
{
public:
   void draw(std::list<IEntity *> entities);
   void initialize(void);
   IScreen * getNextState(void);
   void release(void);
   bool isRunning(void);
   void update(void);

protected:
private:
   IScreen * _next;
   sf::Text * _statisticText;
   int Attribut_3;


};

#endif