#pragma once

#include "IScreen.h"

class GameScreen : public IScreen
{
public:
	GameScreen();
   void draw(std::list<IEntity *> entities);
   void initialize(void);
   IScreen * getNextState(void);
   void release(void);
   bool isRunning(void) const;
   void update(void);

protected:
private:
	bool _isRunning;
   IScreen * _next;
   sf::Text * _statisticText;
};