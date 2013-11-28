#pragma once

#include <list>
#include <stack>
#include "IEntity.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "IEngine.h"
#include "IScreen.h"

class GraphicEngine : public IEngine
{
public:
   void init(Map *);
   void update(std::list<IEntity *> players, std::list<IEntity *> entities);
   IScreen* GetCurrentState(void) {return (!_states.empty()) ? _states.top() : NULL;}
   void PushState(IScreen *state);
   void SetState(IScreen *state);
   void PopState(void);

protected:
private:
   std::list<IEntity *> _entities;
   bool _isRunning;
 
   StartScreen *_startScreen;
   GameScreen  *_gameScreen;
   //TODO OptionScreen

   std::stack<IScreen *> _states;


};