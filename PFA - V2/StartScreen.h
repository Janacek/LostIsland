#pragma once
#include "IScreen.h"

class StartScreen : public IScreen
{
public:
   void draw(std::list<IEntity *> entities);
   void initialize(void);
   IScreen * getNextState(void);
   void release(void);
   bool isRunning(void) const;
   void update(void);

protected:
private:
	bool _isRunning;
   std::vector<sf::Text *> _entries;
   IScreen * _next;


};