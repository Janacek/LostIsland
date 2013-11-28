#include "IScreen.h"

class StartScreen
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
   std::vector<sf::Text *> _entries;
   IScreen * _next;


};